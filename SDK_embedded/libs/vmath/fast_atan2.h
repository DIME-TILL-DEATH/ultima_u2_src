#include "arch/fpu_support.h"
#include <math.h>

#define M_PI_4_FLOAT 0.78539816f
#define PI_FLOAT     3.14159265f
#define PIBY2_FLOAT  1.5707963f

inline float __attribute__((always_inline)) vfast_atan2f (float x , float y)
          {
            const float m = 0.28088f ;
            extern int __signbitf (float x);

            if ( vabs(x) > vabs(y))
              {
                return -x*y / (x*x + m*y*y) + (float)M_PI_4_FLOAT * __signbitf(x);
              }
            else
              {
                float tmp = x*y ;
                return -(float)M_PI_4_FLOAT*( __signbitf(tmp) + __signbitf(x)) + tmp / (y*y + m*x*x) ;
              }
          }


inline float __attribute__((always_inline)) fast_atan2f( float y, float x )
{
        if ( x == 0.0f )
        {
                if ( y > 0.0f ) return PIBY2_FLOAT;
                if ( y == 0.0f ) return 0.0f;
                return -PIBY2_FLOAT;
        }
        float atan;
        float z = y/x;
        if ( vabs( z ) < 1.0f )
        {
                atan = z/(1.0f + 0.28088f*z*z);
                if ( x < 0.0f )
                {
                        if ( y < 0.0f ) return atan - PI_FLOAT;
                        return atan + PI_FLOAT;
                }
        }
        else
        {
                atan = PIBY2_FLOAT - z/(z*z + 0.28088f);
                if ( y < 0.0f ) return atan - PI_FLOAT;
        }
        return atan;
}


float fast_asinf(float x)
{
  return  fast_atan2f ( x , vsqrt(1.0 -x*x) ) ;
}
