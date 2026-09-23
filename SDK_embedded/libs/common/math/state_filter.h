#ifndef __STATE_FILTER_H__
#define __STATE_FILTER_H__

#include "math/matrix2f.h"
#include "math/matrix3f.h"

template <typename T>
class state_filter_t
{
   // оценивающий на n шаге состояние системы
   public :

      typedef T matrix_t ;
      typedef typename T::vector_t vector_t ;

      ~state_filter_t() {} ;
      state_filter_t() {};

      inline void update(const vector_t& Xm , const vector_t& U)
        {
	   // 1. экстраполяция с предыдущего на текущий шаг X'[n]  = A*X[n-1]
	   // 2. учет управляющих воздействий               X'[n] += B*U[n]
	   // 3. коррекция по результатам измерений         X[n]   = X'[n] + K*(Xm[n]-X'[n])

	   X = A*X + B*U ;
	   X = X + K*(Xm-X) ;
        }

      vector_t X ; // вектор состояния
      matrix_t A ; // матрица перехода (модель системы)
      matrix_t K ; // матрица весов коррекции
      matrix_t B ; // матрица управления ( модель управления )
} ;

template <typename T>
class extrapolate_state_filter_t
{
   // предсказывающий на n+1 шаг состояние системы
   public :

      typedef T matrix_t ;
      typedef typename T::vector_t vector_t ;

      ~extrapolate_state_filter_t() {} ;
      extrapolate_state_filter_t() {};

      inline void update(const vector_t& Xm , const vector_t& U)
        {
	  // 1. коррекция по результатам измерений          X'[n]  = X[n] + K*(Xm[n]-X[n])
	  // 2. учет управляющих воздействий                X'[n] += B*U[n]
	  // 2. экстраполяция с текущего на следующий шаг   X[n+1] = A*X'[n]
	  X = A*(X + K*(Xm-X) + B*U) ;
        }

      vector_t X ; // вектор состояния
      matrix_t A ; // матрица перехода (модель системы)
      matrix_t K ; // матрица весов коррекции
      matrix_t B ; // матрица управления ( модель управления )
} ;

class abg_filter_t
{
  //  https://en.wikipedia.org/wiki/Alpha_beta_filter

  public:

    typedef typename  matrix3f::vector vector_t ;
    typedef typename  matrix3f::matrix matrix_t ;

    inline abg_filter_t( float T, float alfa, float beta, float gamma)
      {
         A =  matrix_t(
          1.0f,   T,      0.5f*T*T,
          0.0f,   1.0f,   T,
   	  0.0f,   0,      1.0f
         );

         K = matrix_t(
         alfa,             0.0f,     0.0f,
	 beta/T,           0.0f,     0.0f,
	 2.0f*gamma/(T*T), 0.0f,     0.0f);

      }

    ~abg_filter_t() {}

    inline void update(vector_t& Xm)
      {
         // прогноз
         X = A*X ;
         // коррекция
         X += K*(Xm-X);
      }

    inline void update(vector_t& Xm, vector_t& U)
      {
         // прогноз + управление
         X = A*X + U ;
         // коррекция
         X += K*(Xm-X);
      }

    vector_t X ; // [x,v,a]
    matrix_t A ;
    matrix_t K ;

};


#endif /*__STATE_FILTER_H__*/
