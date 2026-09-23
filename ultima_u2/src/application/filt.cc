#include "appdefs.h"
#include "filt.h"

float eq_coef[5][5];

float eq_1_buf[5];
float eq_1_coef[5];
float eq_2_buf[5];
float eq_2_coef[5];
float eq_3_buf[5];
float eq_3_coef[5];
float eq_4_buf[5];
float eq_4_coef[5];
float eq_5_buf[5];
float eq_5_coef[5];
float pres_buf[5];

float filt_cos[5];
float filt_sin[5];
float filt_alpha[5];

const float freq[5] = {120.0f,360.0f,800.0f,2000.0f,6000.0f};
float freq1[5];
volatile float filt_q;
float w0 = 2.0f*FILT_PI/48000.0f;
