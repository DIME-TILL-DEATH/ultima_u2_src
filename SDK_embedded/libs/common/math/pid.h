#ifndef __PID_H__
#define __PID_H__

template <typename T>
class pid_control_t
{
   public:

      struct param_T_t
       {
	 T Ts ;
         T Pb ;
	 T Ti ;
	 T Td ;
       };

      struct param_K_t
       {
         T Kp ;
	 T Ki ;
	 T Kd ;
       };

      typedef T	value_t;

      inline pid_control_t()  { out=0; e[0] = e[1] = e[2] = T(0) ;  p = {0,0,0}; }

      inline pid_control_t(const param_T_t&  val)  { out=0; e[0] = e[1] = e[2] = T(0) ;  param(val) ; }
      inline pid_control_t(const param_K_t&  val)  { out=0; e[0] = e[1] = e[2] = T(0) ;  param(val) ; }

      inline void param( const param_T_t&  val )
        {

	   p.Kp=1.0f/val.Pb;
	   p.Ki=p.Kp*val.Ts/val.Ti;
	   p.Kd=p.Kp*val.Td/val.Ts;
        }

      inline void param( const param_K_t&  val )
        {
	   p = val ;
        }

      inline void set(const T& val)
        {
	  out = val ;
        }

      inline T update(const T& err, const T& min , const T& max)
        {
	   e[0] = err ;

	   out += p.Kp * ( e[0]-e[1] ) + p.Ki*e[0] + p.Kd*( e[0] - 2.0f*e[1] + e[2]) ;

	   e[2] = e[1] ;
	   e[1] = e[0] ;

	   void saturate ( T& in, const T& min, const T& max ) ;
	   saturate( out , min , max ) ;

	   return out ;
        }



      T e[3];  // input a last 3 sample series
      T out   ;

      param_K_t p ;
};

#endif /*__PID_H__*/

