/*
 * pitch_filter.h
 *
 *  Created on: 27 марта 2014 г.
 *      Author: klen
 */

#ifndef PITCH_FILTER_H_
#define PITCH_FILTER_H_


#include "vdt/vdt.h"
#include "math/matrix2f.h"

typedef matrix2f::vector signal_t ;
#if 0
class gertzel_t
{
  public:

    typedef matrix2::vector signal_t ;

    gertzel_t(const size_t N, const size_t K): N(N), K(K)
      {

        Xin_n  = new signal_t [N] ;
        W_k    = new signal_t [K] ;
        S_kn   = new signal_t [K] ;


        for ( size_t k = 0 ; k < K ; k++  )
          {
            vdt::fast_sincosf(2.0f*vdt::details::M_PI*k/N , W_k[k].sin , W_k[k].cos ) ;
            W_k[k].sin*=-1 ;

            S_kn[k]= signal_t(0.0f, 0.0f) ;
          }

        n = 0 ;
      }
    ~gertzel_t()
      {

        delete [] Xin_n ;
        delete [] W_k ;
        delete [] S_kn ;

      }

    const size_t N ;
    const size_t K ;       // количество фильтров
    signal_t* S_kn ; // спектральный отсчет
    signal_t* W_k ; // фазовращающий множитель
    signal_t* Xin_n ;
    size_t n ;

    //float* Fi_k ; // фаза гармоники синтеза
    //float Shift ; // сдвиг спектра [0,6...1.4]

    inline float update( const signal_t& xin_n )
    {

      float xout_n = 0 ;

      for ( size_t k = 0 ; k < K ; k++  )
        {
          // спектральный анализ потока
          S_kn[k] = W_k[k] * ( S_kn[k] + xin_n - Xin_n[n] ) ;
/*
          // спектральный синтез сигнала
          size_t k_out = k * Shift ; // смещенный индекс частной составляющей
          float amp = 0.0f ;
          if ( k_out < K ) amp = Amp(k * Shift) ;
          xout_n += amp * vsin( Fi_k[k] ) ;

          Fi_k[k] += 2*M_PI/N * k ;
*/
        }

 //     xout_n /= N ;

      Xin_n[n++] = xin_n ;
      if ( n == N ) n = 0 ;

      return xout_n ;

    }

    inline float power( const size_t k ) const  { return  S_kn[k].x*S_kn[k].x + S_kn[k].y*S_kn[k].y; }
    inline float amp  ( const size_t k ) const  { return  vsqrt(power(k)); }
    inline float arg  ( const size_t k ) const  { return  vdt::fast_atan2f( S_kn[k].y , S_kn[k].x ); }

} ;
#endif

template <const size_t K, const size_t fh , const size_t fl, const size_t fs  >
class xgertzel_t
{
  public:

    typedef matrix2f::vector signal_t ;

    inline size_t count() const { return K; }
    inline size_t freq_high() const { return fh; }
    inline size_t freq_low() const { return fl; }
    inline float  z() const { return vdt::fast_logf(1.0f*fh/fl) / K ; }


    inline float freq(const size_t k) const { return fl * vdt::fast_expf(  z() * k );  }
    inline float pass_band(const size_t k) const { return z() / freq(k); }

    xgertzel_t()
      {
        // расчет сетки частот
        for ( size_t k = 0 ; k < K ; k++ )
          {
            n[k] = 0 ;
            S[k] = signal_t(0,0);

            float Nk = fs / pass_band(k) ;

            vdt::fast_sincosf(VDT_2PI_F / Nk , W[k].sin , W[k].cos ) ;

            W[k].sin =- W[k].sin ;

            N[k] = Nk ;
            X[k] = new signal_t[ N[k] ] ;
            for ( size_t n = 0 ; n < N[k] ; n++ )
              {
        	X[k][n] = 0 ;
              }
          }

      }
    ~xgertzel_t()
      {
        for ( size_t k = 0 ; k < K ; k++  )
           delete [] X[k] ;
      }


    size_t          N[K]    ;  // счетчики позиции [0 ... k-1] фильтров
    signal_t        S[K]    ;  // спектральные отсчеты [0 ... k-1] фильтров
    signal_t        W[K]    ;  // фазовращающие множители [0 ... k-1] фильтров
    signal_t*       X[K]    ;  // входные буфера [0 ... k-1] фильтров
    size_t          n[K]    ;  // счетчики позиции [0 ... k-1] фильтров

    inline signal_t update( const signal_t& x )
    {

      signal_t y = 0 ;

      for ( size_t k = 0 ; k < K ; k++  )
        {
          // спектральный анализ потока
          S[k] = W[k] * ( S[k] + x - X[k][n[k]] ) ;

          // обновление k-ого буффера
          X[k][n[k]] = x ;

          n[k]++ ;
          if ( n[k] == N[k] ) n[k] = 0 ;

          // синтез


        }

      return y ;

    }


} ;


#endif /* PITCH_FILTER_H_ */
