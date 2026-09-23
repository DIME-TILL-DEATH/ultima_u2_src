/*
 * matrix2f.h
 * target a cortex-m4f (using vsqrt instr)
 *
 *  Created on: 06.07.2012
 *      Author: klen
 */

#ifndef __MATRIX2F_H__
#define __MATRIX2F_H__

#include "vdt/vdt.h"

inline float machine_eps()
{
	float val = 1.0f;
    	do
	{
		 val /= 2.0f;
	}
    	while ((1.0f + val/2.0f) != 1.0f);
	return val ;
	 
}

namespace matrix2f
{

class matrix ;
class quat ;

// vector class --------------------------------------------------
class vector
{
        friend class matrix ;
	friend class quat ;
	private:

	public :

	typedef float val_type  ;

	union
	{
	   struct { float a,    b;     } /*__attribute__ ((packed))*/ ;
           struct { float x,    y;     } /*__attribute__ ((packed))*/ ;    // XY-coord
           struct { float s,    v;     } /*__attribute__ ((packed))*/ ;    // mechanical  s(t),v(t)=ds/dt
           struct { float cos,  sin;   } /*__attribute__ ((packed))*/ ;    // quadrature
           struct { float d,    q;     } /*__attribute__ ((packed))*/ ;    // qd frame


           struct { union {float Ro; float Mag; }; float  Phi;   } /*__attribute__ ((packed))*/ ;    // polar
                                                                       // magnitude-phase

           struct { float alfa, beta;  } /*__attribute__ ((packed))*/ ;    // alfa-beta frame

           struct { float Theta,Omega; } /*__attribute__ ((packed))*/ ;    // angle-angular rate vector
           struct { float U,    I;     } /*__attribute__ ((packed))*/ ;    // voltage-current vector
           struct { float Kp,   Ki;    } /*__attribute__ ((packed))*/ ;    // PI val-base params vector
           struct { float Pb,   Ti;    } /*__attribute__ ((packed))*/ ;    // PI time-base params vector
           struct { float Min,  Max;   } /*__attribute__ ((packed))*/ ;    // Min/Max vector
           float p[2] ;                               // array storage access
	} /*_attribute__ ((packed))*/ ;

			inline __attribute__((always_inline)) vector ():x(0),y(0) {}

			inline __attribute__((always_inline)) vector (float val)
			    {
			      a = b = val ;
			    }

			// set constructor
			inline __attribute__((always_inline)) vector( const float x , const float y  )
			{
				this->x = x; this->y = y;
			}
			// vectors set constructor
			inline __attribute__((always_inline)) vector( const vector& v )
			{
				x = v.x; y = v.y;
			}

			   // operators
			   inline vector& __attribute__((always_inline)) operator = (const vector& src)
			   	   {
				   	   x = src.x; y = src.y;
				   	   return *this ;
			   	   }


			   // Unary operators
			   vector __attribute__((always_inline)) operator + () const { return *this; }
			   vector __attribute__((always_inline)) operator - () const
			   	   	   {
				   	   	   vector tmp ;
				   	   	   tmp.x = -this->x ;
				   	   	   tmp.y = -this->y ;
				   	   	   return tmp ;

			   	   	   }



			   // Combined assignment - calculation operators
			   vector& __attribute__((always_inline)) operator += (const vector& src)
					{
					   x += src.x; y += src.y;
					   return *this ;
					}

	                   vector& __attribute__((always_inline)) operator += (const float& src)
	                                {
	                                   x += src; y += src;
	                                   return *this ;
	                                }

			   vector& __attribute__((always_inline)) operator -= (const vector& src)
					{
				   	   x -= src.x; y -= src.y;
				   	   return *this ;
					}
			   vector& __attribute__((always_inline)) operator -= (const float& src)
			                {
			                   x -= src; y -= src;
			                   return *this ;
			                }

			   vector& __attribute__((always_inline)) operator *= (const float& c)
					{
			   	   	   x *= c; y *= c;
			   	   	   return *this ;
					}

			   vector& __attribute__((always_inline)) operator *= (const vector& v)
					{
			   	   	   vector tmp(*this);
					   x = tmp.x*v.x-tmp.y*v.y ;
					   y = tmp.x*v.y+tmp.y*v.x ;
			   	   	   return *this ;
					}

			   vector& __attribute__((always_inline)) operator /= (const float& c)
					{
			   	   	   *this *= 1.0f/c ;
			   	   	   return *this ;
					}

			   /*/conjuction
			   vector& __attribute__((always_inline)) operator != (const vector& src)
					{
					   x = src.x; y = -src.y;
					   return *this ;
					}
					*/

			   float __attribute__((always_inline)) operator ^ (const vector& v)
			                {
			                   return x*v.x + y*v.y ;
			                }

			   // Miscellaneous -methods
			   inline void __attribute__((always_inline)) null () { x = y =  0.0f; } ;
			   inline void __attribute__((always_inline)) identity () { x = y = 1.0f; } ;

			   inline float __attribute__((always_inline)) norma1 () const {  return vabsf(x) + vabsf(y) ; }
			   inline vector& __attribute__((always_inline)) normalize1 () {  (*this) *= 1.0f/(norma1()+VDT_EPSILON_F); return *this;}
			   inline float __attribute__((always_inline)) norma () const {  return vsqrtf(x*x + y*y) ; }
			   inline vector& __attribute__((always_inline)) normalize () {  (*this) *= 1.0f/(norma()+VDT_EPSILON_F); return *this; }
			   inline vector& __attribute__((always_inline)) normalize (vector::val_type val) {  (*this) *= val/(norma()+VDT_EPSILON_F); return *this; }

			   inline vector __attribute__((always_inline)) ort () const {  vector tmp(*this); return tmp.normalize(); }

			   inline vector __attribute__((always_inline)) conj () const {  return vector(x,-y); }
			   inline vector& __attribute__((always_inline)) conjze () { y=-y; return *this;}

			   inline float __attribute__((always_inline)) summ () const {  return x + y ; }

			   inline float __attribute__((always_inline)) power () const {  return x*x + y*y ; }
			   inline float __attribute__((always_inline)) abs () const {  return vsqrtf( power() ) ; }
			   inline float __attribute__((always_inline)) arg () const {  return fast_atan2f(y,x);}

			   inline vector __attribute__((always_inline)) exp () const { float s,c ; vdt::fast_sincosf(y,s,c); return vector( vdt::fast_expf(x)*c , vdt::fast_expf(x)*s ); }
			   inline vector& __attribute__((always_inline)) exponiate () { float s,c ; vdt::fast_sincosf(y,s,c); (*this) = exp(); return (*this); }

			   inline vector __attribute__((always_inline)) log () const { return vector( vdt::fast_logf(abs()) , arg()); }
			   inline vector& __attribute__((always_inline)) logiate () { (*this) = log(); return (*this); }

			   inline vector __attribute__((always_inline)) polar () const { return vector(abs(), arg()); }
			   inline vector& __attribute__((always_inline)) polarize () { return (*this) = polar(); }

			   inline vector __attribute__((always_inline)) cartesian () const { float sin,cos ; vdt::fast_sincosf(Phi,sin,cos); return vector(Ro*cos, Ro*sin); }
			   inline vector& __attribute__((always_inline)) cartesianite () { return (*this) = cartesian(); }

			   // угол между двумя векторами
			   inline float __attribute__((always_inline)) angle (const vector& v) const
			   {
			         return vdt::fast_atan2f( - x*v.y + y*v.x , x*v.x + y*v.y ) ;
			   }

			   inline vector __attribute__((always_inline)) rotate (const float angle)
			   {
			         float c , s;
			   	 vdt::fast_sincosf(angle,s,c);
			   	 vector tmp(c*x  -s*y , s*x  +c*y ) ;
			   	 return tmp ;
			   }

			   // ограничение
			   inline vector __attribute__((always_inline)) limits (const vector& min_limits ,const vector& max_limits) const
                           {
			     vector tmp ;
			     tmp.x = (x < min_limits.x) ? min_limits.x : ((x > max_limits.x) ? max_limits.x : x ) ;
			     tmp.y = (y < min_limits.y) ? min_limits.y : ((y > max_limits.y) ? max_limits.y : y ) ;
			     return tmp ;
                           }

			   inline vector& __attribute__((always_inline)) limitite (const vector& min_limits ,const vector& max_limits)
                           {
			     x = (x < min_limits.x) ? min_limits.x : ((x > max_limits.x) ? max_limits.x : x ) ;
			     y = (y < min_limits.y) ? min_limits.y : ((y > max_limits.y) ? max_limits.y : y ) ;
			     return *this ;
                           }

			   inline vector __attribute__((always_inline)) limits (const vector& limits) const
                           {
			     vector tmp ;
			     tmp.x = (x < limits.Min) ? limits.Min : ((x > limits.Max) ? limits.Max : x ) ;
			     tmp.y = (y < limits.Min) ? limits.Min : ((y > limits.Max) ? limits.Max : y ) ;
			     return tmp ;
                           }

			   inline vector& __attribute__((always_inline)) limitite (const vector& limits)
                           {
			     x = (x < limits.Min) ? limits.Min : ((x > limits.Max) ? limits.Max : x ) ;
			     y = (y < limits.Min) ? limits.Min : ((y > limits.Max) ? limits.Max : y ) ;
			     return *this ;
                           }



			   static inline vector __attribute__((always_inline)) get_null () { return vector(0,0); } ;
			   static inline vector __attribute__((always_inline)) get_one () { return vector(1,1); } ;






};

bool inline __attribute__((always_inline)) compare(vector& a, vector& b)
{
    return (a.power() < b.power());
}
// logical equal-to operator
inline bool __attribute__((always_inline))
operator == (const vector& a, const vector& b)
{
   return (a.x == b.x) &&  (a.y == b.y)  ;
}

// logical no-equal-to operator
inline bool __attribute__((always_inline))
operator != (const vector& v1, const vector& v2)
{
    return !(v1 == v2) ;
}

// binary addition operator
inline vector __attribute__((always_inline))
operator + (const vector& v1, const vector& v2)
{
   vector temp = v1;
   temp += v2;
   return temp;
}

// binary addition operator
inline vector __attribute__((always_inline))
operator + (const vector& v1, const float& c)
{
   vector temp = v1;
   temp += c;
   return temp;
}

// binary subtraction operator
inline vector __attribute__((always_inline))
operator - (const vector& v1, const vector& v2)
{
   vector temp(v1);
   temp -= v2;
   return temp;
}

// binary subtraction operator
inline vector __attribute__((always_inline))
operator - (const vector& v, const float& c)
{
   vector temp(v);
   temp -= c;
   return temp;
}

// binary subtraction operator
inline vector __attribute__((always_inline))
operator - (const float& c, const vector& v)
{
   vector temp(-v);
   temp += c;
   return temp;
}

// binary scalar multiplication operator
inline vector __attribute__((always_inline))
operator * (const vector& v, const float& c)
{
   vector tmp(v);
   return tmp*=c;
}

// binary scalar multiplication operator
inline vector __attribute__((always_inline))
operator * (const float& c, const vector& v)
{
	vector tmp(v);   
	return tmp*=c ;
}

inline vector __attribute__((always_inline))
operator * (const vector& v0, const vector& v1)
{
  vector tmp(v0); 
  return tmp*=v1 ;
}

// binary scalar division operator
inline vector __attribute__((always_inline))
operator / (const vector& v, const float& c)
{
	vector tmp(v) ;   
	return tmp/=c+VDT_MIN_F ;
}

// binary scalar division operator
inline vector __attribute__((always_inline))
operator / (const float& c , const vector& v)
{
	vector tmp(c/(v.x+VDT_MIN_F) , c/(v.y+VDT_MIN_F)) ;
	return tmp ;
}

// скалярное произведение
inline  float __attribute__((always_inline))
operator ^ (vector& v0 , vector& v1 )
{
 return v0.x*v1.x + v0.y*v1.y ;
}

/*
// unary conjuction --------------------------------------------
inline vector __attribute__((always_inline))
operator ! (const vector& src)
	{
		vector tmp (src.x , -src.y) ;
		return tmp ;
	}
*/

// matrix class --------------------------------------------------
class matrix
{
	friend class vector ;
	friend class quat ;
	private:



	public:

	        typedef vector vector_t;
		typedef quat   quat_t;

		typedef vector::val_type val_type  ;

		union
		{
	        struct { float 	m00, m01,
	                        m10, m11
	                        ; } ;
	        float p[4] ;

		};

		// zero fill constructor
		inline __attribute__((always_inline)) matrix()	{}
		// set constructor
		inline __attribute__((always_inline)) matrix( 	float m00 , float m01,
						                float m10 , float m11 )
		{
			this->m00 = m00; this->m01 = m01;
			this->m10 = m10; this->m11 = m11;
		}
		// vectors set constructor
		inline __attribute__((always_inline)) matrix( vector& x0 , vector& y0 )
		{
			m00 = x0.x; m01 = x0.y;
			m10 = y0.x; m11 = y0.y;
		}

		// matrix set constructor
		inline __attribute__((always_inline)) matrix( const matrix& m )
		{
			m00 = m.m00; m01 = m.m01;
			m10 = m.m10; m11 = m.m11;
		}


		   // operators
		   inline matrix& __attribute__((always_inline)) operator = (const matrix& m)
		   	   {
			   	   m00 = m.m00; m01 = m.m01;
			   	   m10 = m.m10; m11 = m.m11;
			   	   return *this ;
		   	   }


		   // Unary operators
		   inline matrix __attribute__((always_inline)) operator + () const  { return *this; }
		   inline matrix __attribute__((always_inline)) operator - () const
		   	   	   {
			   	   	   matrix tmp(  -this->m00 , -this->m01 ,
			   	   		        -this->m10 , -this->m11
			   	   	   	      ) ;
			   	   	   return tmp ;

		   	   	   }

		   // Combined assignment - calculation operators
		   inline matrix& __attribute__((always_inline)) operator += (const matrix& src)
				{
				   m00 += src.m00; m01 += src.m01;
				   m10 += src.m10; m11 += src.m11;
				   return *this ;
				}
		   inline matrix& __attribute__((always_inline)) operator -= (const matrix& m)
				{
			   	   m00 -= m.m00; m01 -= m.m01;
			   	   m10 -= m.m10; m11 -= m.m11;
			   	   return *this ;
				}
		   inline matrix& __attribute__((always_inline)) operator *= (const matrix& m)
				{
			   	   matrix tmp(*this) ;

			   	   m00 = tmp.m00*m.m00 + tmp.m01*m.m10 ;  m01 = tmp.m00*m.m01 + tmp.m01*m.m11;
			   	   m10 = tmp.m10*m.m00 + tmp.m11*m.m10 ;  m11 = tmp.m10*m.m01 + tmp.m11*m.m11;


			   	   return *this ;
				}
		   inline matrix& __attribute__((always_inline)) operator *= (const float& c)
				{
		   	   	   m00 *= c; m01 *= c;
		   	   	   m10 *= c; m11 *= c;
		   	   	   return *this ;
				}
		   inline matrix& __attribute__((always_inline)) operator /= (const float& c)
				{
		   	   	   float c_inv = VDT_EPSILON_F + 1.0f/c ;
		                   m00 *= c_inv; m01 *= c_inv;
		   	   	   m10 *= c_inv; m11 *= c_inv;
		   	   	   return *this ;
				}

		   inline float __attribute__((always_inline)) operator ()( const size_t a , const size_t b ) const
		   {
		     return p[ 2*a + b ] ;
		   }
	           inline float& __attribute__((always_inline)) operator ()( const size_t a , const size_t b )
	           {
	             return p[ 2*a + b ] ;
	           }

		   // Miscellaneous -methods
		   inline void __attribute__((always_inline)) null () { m00 = m01 = m10 = m11 =  0.0f; } ;
		   inline void __attribute__((always_inline)) one ()  { m00 = m01 = m10 = m11 =  1.0f; } ;
	           inline void __attribute__((always_inline)) identity ()  { m01 = m10 = 0.0f ; m00 = m11= 1.0f;} ;

		   // Utility methods
		   inline matrix __attribute__((always_inline)) solve (const matrix& b) const ;
		   inline vector __attribute__((always_inline)) solve (const vector& b) const ;

		   inline matrix __attribute__((always_inline)) adj () const { return matrix() ; }
		   inline float __attribute__((always_inline)) trace() const { return m00 + m11 ; }
		   inline __attribute__((always_inline)) matrix& inv ()
		   	   {
					matrix tmp(*this) ;
					float d_inv = VDT_EPSILON_F + 1.0f/det() ;
					m00 =  tmp.m11 ;     m01 =  -tmp.m10 ;
					m10 =  -tmp.m01 ;    m11 =  tmp.m00 ;
					(*this) *= d_inv ;
					return *this ;
		   	   }
		   inline float __attribute__((always_inline)) det () const
		   	   {
			   	   return m00*m11 - m01*m10  ;
		   	   }

		   inline matrix& __attribute__((always_inline))  transpose ()
			{
				matrix tmp ( 	m00 , m10,
						m01 , m11) ;
				*this=tmp ;
				return *this ;
			}

		   inline float __attribute__((always_inline))  norma1 () const {  return vabsf(m00) + vabsf(m01) + vabsf(m10) + vabsf(m11)  ; }
		   inline matrix& __attribute__((always_inline)) normalize1 () {  *this *= 1.0f/(norma1()+VDT_EPSILON_F) ; return *this;  }

		   inline float __attribute__((always_inline)) norma () const {  return vsqrtf( m00*m00 + m01*m01 +
							                                       m10*m10 + m11*m11 ) ; }
		   inline matrix& __attribute__((always_inline)) normalize () {  *this *= 1.0f/(norma() + VDT_EPSILON_F) ; return *this; }

		   inline float __attribute__((always_inline)) summ () {  return  m00 + m01 + m10 + m11 ; }

		   inline float __attribute__((always_inline)) cofact () const {return 0.0f ;}
		   inline float __attribute__((always_inline)) cond () const {return 0.0f ;}

		   static inline matrix __attribute__((always_inline)) get_null () { return matrix(0,0,0,0); } ;
		   static inline matrix __attribute__((always_inline)) get_one () { return matrix(1,1,1,1); } ;
		   static inline matrix __attribute__((always_inline)) get_idemtity () { return matrix(1,0,0,1); } ;

		   inline void __attribute__((always_inline)) rotate (const float angle)
		       {
		   	 float c , s;
		   	 vdt::fast_sincosf(angle,s,c);
		         m00 = c ;  m01 = -s ;
		   	 m10 = s ;  m11 = c ;
		       } ;

		   inline void __attribute__((always_inline)) park (const float angle)
		       {
		   	 float c , s;
		   	 vdt::fast_sincosf(angle,s,c);
		         m00 = c ;  m01 = s ;
		   	 m10 =-s ;  m11 = c ;
		       } ;

		   static inline matrix __attribute__((always_inline)) get_rotate (const float angle)
		       {
			 float c , s;
			 vdt::fast_sincosf(angle,s,c);
		         return matrix(c,s,-s,c);
		       } ;

		   static inline void __attribute__((always_inline)) get_rotate (const float angle, matrix& m)
		       {
			 float c , s;
			 vdt::fast_sincosf(angle,s,c);
			 m.m00 = c ;  m.m01 = s ;
			 m.m10 = -s ;  m.m11 = c ;
		       } ;

};

// unary inversion
inline matrix __attribute__((always_inline)) operator ! (const matrix& m)
		{
			matrix tmp ( m ) ;
			return tmp.inv()  ;
		}

// logical equal-to operator
inline bool __attribute__((always_inline))
operator == (const matrix& a, const matrix& b)
{
   return (a.m00 == b.m00) &&  (a.m01 == b.m01) &&
	  (a.m10 == b.m10) &&  (a.m11 == b.m11)  ;
}

// logical no-equal-to operator
inline bool __attribute__((always_inline))
operator != (const matrix& a, const matrix& b)
{
    return !(a == b) ;
}

// binary addition operator
inline matrix __attribute__((always_inline))
operator + (const matrix& m1, const matrix& m2)
{
   matrix temp = m1;
   temp += m2;
   return temp;
}

// binary subtraction operator
inline matrix __attribute__((always_inline))
operator - (const matrix& m1, const matrix& m2)
{
   matrix temp(m1);
   temp -= m2;
   return temp;
}


// binary scalar multiplication operator
inline vector __attribute__((always_inline))
operator * (const matrix& m, const vector& c)
{
   vector tmp;
   tmp.x = m.m00 * c.x + m.m01 * c.y  ;
   tmp.y = m.m10 * c.x + m.m11 * c.y  ;

   return tmp;
}


// binary scalar multiplication operator
inline matrix __attribute__((always_inline))
operator * (const matrix& m, const float& c)
{
   matrix temp(m);
   temp *= c;
   return temp;
}

// binary scalar multiplication operator
inline matrix __attribute__((always_inline))
operator * (const float& c, const matrix& m)
{
   return (m * c);
}

// binary matrix multiplication operator
inline matrix __attribute__((always_inline))
operator * (const matrix& m1, const matrix& m2)
{
   matrix temp = m1;
   temp *= m2;
   return temp;
}

// binary scalar division operator
inline matrix __attribute__((always_inline))
operator / (const matrix& m, const float& c)
{
    return (m * (VDT_EPSILON_F + 1.0f / c));
}

// binary scalar division operator
inline matrix __attribute__((always_inline))
operator / (const float& no, const matrix& m)
{
    return (!m * no);
}

// binary matrix division operator
inline matrix __attribute__((always_inline))
operator / (const matrix& m1, const matrix& m2)
{
    return (m1 * !m2);
}



// unary transpose --------------------------------------------
inline matrix __attribute__((always_inline))  operator ~ (const matrix& src)
	{
		matrix tmp ( 	src.m00 , src.m10,
				src.m01 , src.m11) ;
		return tmp ;
	}


}
#endif /* MATRIX2F_H_ */
