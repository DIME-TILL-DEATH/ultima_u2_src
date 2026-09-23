


#ifndef __SINCOS_H__
#define __SINCOS_H__

#include <stddef.h>

typedef struct
{
        float s;
        float c;
} sincos_point_t ;

const float M_PI = 3.14159265358979323846 ;
const size_t sin_cos_N = 1024*10 ;
const float pi2_inv = 0.5f/M_PI ;
const float pi2 = M_PI*2.0 ;
const float i_2_N_inv = pi2 / (float)sin_cos_N ;


extern sincos_point_t sincos_table[] ;


#ifdef __cplusplus
        extern "C" {
#endif

          inline void __attribute__((always_inline)) trig_params( const float arg, size_t& k, float& d_arg )
          {
            size_t n = arg * pi2_inv ;
            float main_arg = arg - n*pi2 ;
            k = sin_cos_N * main_arg * pi2_inv ;
            d_arg = main_arg - k*i_2_N_inv ;
          }
          //------------------------------------
          inline float __attribute__((always_inline)) vsin(const float arg)
          {
            size_t k ;
            float d_arg ;
            trig_params( arg, k, d_arg );
            return sincos_table[k].s + sincos_table[k].c*d_arg ;
          }
          //------------------------------------
          inline float __attribute__((always_inline)) vcos(const float arg)
          {
            size_t k ;
            float d_arg ;
            trig_params( arg, k, d_arg );
            return sincos_table[k].c - sincos_table[k].s*d_arg ;
          }
          //-------------------------------------
          inline void __attribute__((always_inline)) vsincos ( const float arg, float& sin, float& cos)
          {
            size_t k ;
            float d_arg ;
            trig_params( arg, k, d_arg );
            sin = sincos_table[k].s + sincos_table[k].c*d_arg ;
            cos = sincos_table[k].c - sincos_table[k].s*d_arg ;
          }
          //-------------------------------------
          inline float __attribute__((always_inline)) vtan ( const float arg)
          {
            size_t k ;
            float d_arg ;
            trig_params( arg, k, d_arg );
            return (sincos_table[k].s + sincos_table[k].c*d_arg) / ( sincos_table[k].c - sincos_table[k].s*d_arg ) ;
          }

#ifdef __cplusplus
        }
#endif

#endif /*__SINCOS_H__*/
