/*
 * fir.h
 *
 *  Created on: 16 mach. 2018 г.
 *      Author: klen
 *
 *      FIR filter
 *
 */

#ifndef __FIR_H__
#define __FIR_H__

// #include "vdt/vdt.h" // необходимо для расчета импульсной х-ки

namespace kgp_dsp
{

  inline int32_t dsp_convert_int32_q31_impulse( int32_t* impulse , size_t len )
     {
        int32_t max_abs = 0 ;
        for ( size_t i = 0 ; i < len ; i++  )
           __builtin_abs(impulse[i]) > max_abs ? max_abs = __builtin_abs(impulse[i]) : max_abs ;

        for ( size_t i = 0 ; i < len ; i++  )
          {
            int64_t tmp = (int64_t)impulse[i] * (int64_t)0x7fffffff / (int64_t)max_abs;
            impulse[i] = tmp ;
          }

        return max_abs ;
     }

  template <typename T > class fir_t
    {
       public:
          typedef T value_type  ;

          inline  fir_t(const T* taps, T* samples, const size_t size ): taps(taps), samples(samples), size(size), size_sub_1(size-1), pos(0) {} ;

          inline ~fir_t() {} ;

          inline void mla( T& acc , const T x, const T t) { acc += x * t ; }

          inline void pass( T& acc , const T* x, const T* t, size_t len);



          inline T update(const T& sample)
             {
               /* запись входного отсчета
                  в обратном порядке порядке

                 FS - проход переднего куска
                 SS - проход заднешго куска

                   SS *
                    * *
                  * * *
                  * * *  FS *
                  * * *   * *
                  * * * * * *
                        ^
                   dir<-|
                       pos
               */


               // запись входного отсчета в FIFO
               *(samples + pos) = sample ;

               const T*  t = taps ;
               T  y = 0 ;

               // FS - проход переднего куска
               const T* x = samples + pos ;


              //pass( y , x, t, size - pos) ;

               while ( x != samples + size )
               	 mla ( y , *(x++) , *(t++) ) ;

               // SS - проход задненго куска
               x = samples ;

               while ( x != samples + pos )
                  mla ( y , *(x++) , *(t++) ) ;
//              pass( y , x, t, pos) ;

               // обновление указателя вершины FIFO
               if ( --pos == (size_t)-1 ) pos = size_sub_1 ;

               return y ;
             }

       private:

          const T*      taps        ;
          T*            samples     ;
          const size_t  size        ;
          const size_t  size_sub_1  ;
          size_t        pos         ;
    };




  typedef fir_t<float>    ffir_t ;
  typedef fir_t<int32_t>  ifir_t ;

  template<>
  inline void ifir_t::mla( int32_t& acc , const int32_t x, const int32_t t) {  acc = smmla (  x , t , acc ); }

  /*
  template<>
  __attribute__ ((always_inline)) inline void ifir_t::pass( int32_t& acc , const int32_t* px, const int32_t* pt, size_t len)
     {
       asm volatile
       	   (
               "cbz %[len], .end%=              \n"
               ".loop%=:                        \n"
       	       "ldr r8, [%[px]],  #4            \n"
       	       "ldr r9, [%[pt]],  #4            \n"
               "smmla %[ac], r8, r9, %[ac]      \n"
    	       "subs %[len], %[len], #1         \n"
               "bne  .loop%=                    \n"
       	       ".end%=:                         \n"

       	       : [ac]  "=r" (acc)    // запись по ссылке
       	       :       "0"  (acc),   // чтение по ссылке
		 [px]  "r"  (px),
       		 [pt]  "r"  (pt),
       		 [len] "l"  (len)
      	       : "r8", "r9"
       	   );
     }
 */


};

using namespace kgp_dsp ;

#endif /* __FFT_H__ */
