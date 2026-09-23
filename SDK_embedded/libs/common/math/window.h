#ifndef __WINDOW_H__
#define __WINDOW_H__

namespace kgp_math
{

   class window
      {
        private:
	       static constexpr float Q = 0.5f;
	       static constexpr float Pi= 3.14159265358979323846f ;


        public:
	        static float Rectangle(float n, float frameSize)
                   {
                     return 1;
                   }

                static float Gausse(float n, float frameSize)
                   {   
                     auto a = (frameSize - 1)/2;
                     auto t = (n - a)/(Q*a);
                     t = t*t;
                     return vdt::fast_expf(-t/2);
                   }

                static float Hamming(float n, float frameSize)
                   {
                     return 0.54 - 0.46*vdt::fast_cosf((vdt::details::VDT_2PI_F*n)/(frameSize - 1));
                   }

                static float Hann(float n, float frameSize)
                   {
                     return 0.5*(1 - vdt::fast_cosf((vdt::details::VDT_2PI_F*n)/(frameSize - 1)));
                   }

                static float BlackmannHarris(float n, float frameSize)
                   {
                     return 0.35875 - (0.48829*vdt::fast_cos((vdt::details::VDT_2PI_F*n)/(frameSize - 1))) +
                            (0.14128*vdt::fast_cosf((2*vdt::details::VDT_2PI_F*n)/(frameSize - 1))) - (0.01168*vdt::fast_cosf((2*vdt::details::VDT_2PI_F*n)/(frameSize - 1)));
                   }
      };

}; // namespace kgp_math

#endif 
