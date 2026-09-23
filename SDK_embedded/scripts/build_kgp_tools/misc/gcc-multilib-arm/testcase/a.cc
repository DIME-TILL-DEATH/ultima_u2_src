#include <vector>

volatile double* ptr = (volatile double*)0x123 ;

int main ()
{
  double arg = *ptr ;
SSS:
  arg = 1+arg / (arg + __builtin_sqrt(arg)) ;
  return (int) arg ;
}
