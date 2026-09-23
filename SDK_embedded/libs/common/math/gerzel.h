/*
 * gerzel.h
 *
 *  Created on: 26 марта 2014 г.
 *      Author: klen
 *
 *
 *  2018 г.  update
 *
 */

#ifndef __GERZEL_H__
#define __GERZEL_H__

#include "math/matrix2f.h"

template <const float* X_n, const size_t N, float Fs>
class goertzel_t
{

   public:
       goertzel_t()
        {

        }
       float update( float x , float f )
        {
	  float k = N * f / Fs ;

	  W.cos =  fast_cosf(vdt::details::VDT_2_PI_F*k/N) ;
	  W.sin = -fast_sinf(vdt::details::VDT_2_PI_F*k/N) ;



        }

       inline float f(  )
   private:
       matrix2f::vector W ;
} ;


#if 0

#include "math/matrix2f.h"

class TSlideDFT
{
  public:

  typedef matrix2f::vector signal_t ;

  TSlideDFT(size_t N, size_t K)
      {
        this->N = N ;
        this->K = K ;
        Xn  = new signal_t [N] ;
        Wk  = new signal_t [K] ;
        Skn = new signal_t [K] ;

        for ( size_t k = 0 ; k < K ; k++  )
          {
            Wk[k] = signal_t( fast_cosf(vdt::details::VDT_2_PI_F*k/N) , -fast_sinf(vdt::details::VDT_2_PI_F*k/N) );
          }

        n = 0 ;
      }
    ~TSlideDFT()
      {
        delete [] Xn ;
        delete [] Wk ;
        delete [] Skn ;
      }

    size_t N ;
    size_t K ;
    signal_t* Skn ; // спектральный отсчет
    signal_t* Wk ; // фазовращающий множитель
    signal_t* Xn ;
    size_t n ;

    inline void Update( signal_t& xn )
    {
      signal_t dxn = xn - Xn[n] ;
      for ( size_t k = 0 ; k < K ; k++  )
            Skn[k] = Wk[k] * ( Skn[k] + dxn ) ;

      Xn[n++] = xn ;
      if ( n == N ) n = 0 ;
    }

    inline float Power( size_t k ) { return  Skn[k].x*Skn[k].x + Skn[k].y*Skn[k].y; }
    inline float Amp( size_t k ) { return  vsqrt(Power(k)); }
} ;

class TStableSlideDFT
{
  public:

  typedef matrix2f::vector signal_t ;

  TStableSlideDFT(size_t N, size_t K, signal_t::val_type alfa )
      {
        this->N = N ;
        this->K = K ;
        this->nalfa = fast_powf(alfa , N) ;
        Xn  = new signal_t [N] ;
        Wk  = new signal_t [K] ;
        Skn = new signal_t [K] ;

        for ( size_t k = 0 ; k < K ; k++  )
          {
            Wk[k] = alfa * signal_t( fast_cosf(vdt::details::VDT_2_PI_F*k/N) , -fast_sinf(vdt::details::VDT_2_PI_F*k/N) );
          }

        n = 0 ;
      }
    ~TStableSlideDFT()
      {
        delete [] Xn ;
        delete [] Wk ;
        delete [] Skn ;
      }

    signal_t::val_type  nalfa ; //  alfa^N
    size_t N ;
    size_t K ;
    signal_t* Skn ; // спектральный отсчет
    signal_t* Wk ; // фазовращающий множитель
    signal_t* Xn ;
    size_t n ;

    inline void Update( signal_t& xn )
    {
      signal_t dxn = xn - nalfa * Xn[n] ;
      for ( size_t k = 0 ; k < K ; k++  )
            Skn[k] = Wk[k] * ( Skn[k] + dxn ) ;

      Xn[n++] = xn ;
      if ( n == N ) n = 0 ;
    }

    inline float Power( size_t k ) { return  (Skn[k].x*Skn[k].x + Skn[k].y*Skn[k].y); }
    inline float Amp( size_t k ) { return  vsqrt(Power(k)); }
} ;

#endif

#include <stdint.h>
#include <limits.h>

class THalfStableSlideDFT
{
  public:

  union  complex_t
    {
      inline complex_t () : i(0), q(0) {}
      inline complex_t ( int16_t i, int16_t q ) : i(i), q(q)  {}
      struct {
	int16_t i ;
	int16_t q ;
      };
      uint32_t val ;
    } ;


  THalfStableSlideDFT( size_t K, size_t N ) : N(2<<N), K(K), mask((2<<N)-1)
      {
        Xn  = new int16_t [this->N] ;
        Wk  = new complex_t [K] ;
        Skn = new complex_t [K] ;

        int16_t alfa = __SHRT_MAX__ * fast_pow( 0.5f , 1.0f/this->N ); // alfa ^ 1024 = 0.5

        for ( size_t k = 0 ; k < K ; k++  )
          {
            Wk[k].i =    alfa * fast_cosf(vdt::details::VDT_2_PI_F*k/N) ;
            Wk[k].q =  - alfa * fast_sinf(vdt::details::VDT_2_PI_F*k/N) ;
          }


        n = 0 ;
      }
    ~THalfStableSlideDFT()
      {
        delete [] Xn ;
        delete [] Wk ;
        delete [] Skn ;
      }

    const size_t N ;
    const size_t K ;
    const size_t mask ;

    complex_t* Skn ; // спектральный отсчет
    complex_t* Wk ; // фазовращающий множитель
    int16_t* Xn ;
    size_t n ;

    inline void Update( int16_t xn )
    {
      /*
       *  Sn = W * ( Sn + xn - (xN >> 1) )
       *
       *  1. dxn = xn - (xN >> 1)
       *  2. Y = Sn + dxn
       *  3. Sn = W * Y
       */

      nop_rep(2);
      int16_t dxn = xn - (Xn[n] >> 1) ;
      nop_rep(2);
      complex_t Y ;
      for ( size_t k = 0 ; k < K ; k++  )
	{
	   nop_rep(2);
	   Y = complex_t ( Skn[k].i + dxn , Skn[k].q) ;

	   Skn[k].i = smusd  ( Y.val , Wk[k].val) ;
	   Skn[k].q = smuadx ( Y.val , Wk[k].val) ;
	   nop_rep(2);

	}

      nop_rep(2);
      Xn[n++] = xn ;
      n &= N-1 ;
      nop_rep(2);
    }

    //inline uint32_t  Power( size_t k ) { return  (Skn[k].i*Skn[k].i + Skn[k].q*Skn[k].q); }
    //inline uint32_t Amp( size_t k ) { return  vsqrt(Power(k)); }
} ;

class TWordStableSlideDFT
{
  public:

  struct  complex_t
    {
      inline complex_t () : i(0), q(0) {}
      inline complex_t ( int16_t i, int16_t q ) : i(i), q(q)  {}
      int16_t i ;
      int16_t q ;
    } ;


  TWordStableSlideDFT( size_t K, size_t N ) : N(2<<N), K(K), mask((2<<N)-1)
      {
        Xn  = new int32_t [this->N] ;
        Wk  = new complex_t [K] ;
        Skn = new complex_t [K] ;

        int16_t alfa = __INT_MAX__ * fast_pow( 0.5f , 1.0f/this->N ); // alfa ^ 1024 = 0.5

        for ( size_t k = 0 ; k < K ; k++  )
          {
            Wk[k].i =    alfa * fast_cosf(vdt::details::VDT_2_PI_F*k/N) ;
            Wk[k].q =  - alfa * fast_sinf(vdt::details::VDT_2_PI_F*k/N) ;
          }


        n = 0 ;
      }
    ~TWordStableSlideDFT()
      {
        delete [] Xn ;
        delete [] Wk ;
        delete [] Skn ;
      }

    const size_t N ;
    const size_t K ;
    const size_t mask ;

    complex_t* Skn ; // спектральный отсчет
    complex_t* Wk ; // фазовращающий множитель
    int32_t* Xn ;
    size_t n ;

    inline void Update( int32_t xn )
    {
      /*
       *  Sn = W * ( Sn + xn - (xN >> 1) )
       *
       *  1. dxn = xn - (xN >> 1)
       *  2. Y = Sn + dxn
       *  3. Sn = W * Y
       */


      int32_t dxn = xn - (Xn[n] >> 1) ;

      complex_t Y ;
      for ( size_t k = 0 ; k < K ; k++  )
	{

	   Y = complex_t ( Skn[k].i + dxn , Skn[k].q) ;

	   Skn[k].i = Wk[k].i*Y.i - Wk[k].q*Y.q ;
	   Skn[k].q = Wk[k].i*Y.q + Wk[k].q*Y.i ;


	}

      Xn[n++] = xn ;
      n &= mask ;
    }

    //inline uint32_t  Power( size_t k ) { return  (Skn[k].i*Skn[k].i + Skn[k].q*Skn[k].q); }
    //inline uint32_t Amp( size_t k ) { return  vsqrt(Power(k)); }
} ;


#endif /* __GERZEL_H__ */
