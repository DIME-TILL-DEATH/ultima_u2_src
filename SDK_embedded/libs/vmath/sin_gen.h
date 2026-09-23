/*
 * sine_gen.h
 *
 *  Created on: 09.11.2012
 *      Author: klen
 */

#ifndef SINE_GEN_H_
#define SINE_GEN_H_

#include "arch.h"
#include "sincos.h"

/*      recursive sine generator
 *  X[n] = k*X[n-1]-X[n-2]
 *  k = 2*cos(2*Pi*freq/sample_rate)
 *  init:
 *      X[n-1]=0
 *      X[n-2]=-A*sin(2*Pi*freq/sample_rate)
 *
 *
 */

class sin_generator
    {
      private:
        float x0 ;
        float x1 ;
        float freq ;
        float sample_rate ;

        float k ;

      public:
        inline sin_generator() { x0=x1=freq=sample_rate=k=0.0f; }

        inline void init(const float freq , const float sample_rate, const float amp )
          {
            float s,c ;
            vsincos( 2.0f * M_PI  * freq / sample_rate, s,c ) ;
            x0 = 0.0f ;
            x1 = -amp * s ;
            k = 2.0f * c ;
            this->freq = freq ;
            this->sample_rate = sample_rate ;
          }

        inline float val()
        {
          return x0 ;
        }

        inline float sample()
          {
            float tmp = x0 ;
            x0 = k*x0 - x1 ;
            x1 = tmp ;
            return x0 ;
          }


};

#endif /* SINE_GEN_H_ */
