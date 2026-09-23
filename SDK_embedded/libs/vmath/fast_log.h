union ADVFLOAT
{
  float x;
  struct
  {
    unsigned int mant : 23; /* Mantissa without leading one */
    unsigned int exp  : 8;  /* Exponential part */
    unsigned int sign : 1;  /* Indicator of the negative number */
  };
};



inline float fast_log2f( float x )
{
  const float LOG2E = 1.44269504088896340736f ;

  ADVFLOAT ax;
  int exp;

  ax.x = x;
  exp = ax.exp - 127;
  ax.sign = 0;
  ax.exp = 127;

  return (ax.x - 1.0f) * LOG2E + exp;
}

inline float fast_logf(float x)
{
  const float M_E   = 2.7182818284590452354f  ;
  return fast_log2f(x) / fast_log2f(M_E)    ;
}

inline float fast_log10f(float x)
{
  return fast_log2f(x) / fast_log2f(10.0f)    ;
}
