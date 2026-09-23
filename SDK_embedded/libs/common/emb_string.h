#ifndef __EMB_PRINTF_H__
#define __EMB_PRINTF_H__

#include "supc++.h"
#include "supstl.h"

#include <ctype.h>
#include <stdint.h>

namespace kgp
{

        inline emb_string& trim_left(emb_string& str)
                {
                  str.erase(str.begin(), find_if(str.begin(), str.end(),
                    [](char& ch)->bool { return !isspace(ch); }));
                  return str;
                }

        inline emb_string& trim_right(emb_string& str)
                {
                  str.erase(find_if(str.rbegin(), str.rend(),
                    [](char& ch)->bool { return !isspace(ch); }).base(), str.end());
                  return str;
                }

        inline emb_string& trim(emb_string& str)
        {
          str.erase(str.begin(), find_if(str.begin(), str.end(),
            [](char& ch)->bool { return !isspace(ch); }));

          str.erase(find_if(str.rbegin(), str.rend(),
            [](char& ch)->bool { return !isspace(ch); }).base(), str.end());
          return str;
        }

class emb_printf
{
   public:

      static inline void format(emb_string& dest, const char *s)
        {
           while (*s)
             {
                if (*s == '%' && *(++s) != '%')
                   throw_exeption_catcher("invalid format string: missing arguments");
                dest += *s++ ;
             }
        }

      template<typename T, typename... Args>
      static inline void format(emb_string& dest, const char *s, T value, Args... args)
        {
	   while (*s)
      	     {
                if (*s == '%' && *(++s) != '%')
                  {
        	    convert(dest, &s, value );
                    format(dest, s, args...); // продолжаем обработку аргументов, даже если *s == 0
                    return;
                  }
                dest += *s++ ;
             }
      	   throw_exeption_catcher("extra arguments provided to printf");
        }

      template<typename T, typename... Args>
      static void inline format(emb_string& dest, const emb_string& format, T value, Args... args)
        {
	   emb_printf::format(dest, format.c_str(), value, args...);
        }

      template<typename T, typename... Args>
      static inline void scatf(emb_string& out , const char *format, T value, Args... args)
        {
           emb_printf::format(out, format, value, args... );
        }

      template<typename T, typename... Args>
      static inline void scatf(emb_string& out , const emb_string& format, T value, Args... args)
        {
           emb_printf::format(out, format.c_str(), value, args... );
        }

      template<typename T, typename... Args>
      static inline void sprintf(emb_string& out , const char *format, T value, Args... args)
        {
           out.clear();
           emb_printf::format(out, format, value, args... );
        }

      template<typename T, typename... Args>
      static inline void sprintf(emb_string& out , const emb_string& format, T value, Args... args)
        {
           out.clear();
           emb_printf::format(out, format.c_str(), value, args... );
        }

   protected:

       //------------------------
       /* integer format:  %[-][*]n[X]
        *          * - space pad owerwrite '0'
        *          n - min digit pads, 0 - not out in zero val, [0...64]
        *          X - format
        *          	x or X - hexal
        *          	d - decimal
        *          	o - octal
        *          	b - binary
        *
        *
       */
       template <typename T>
       static inline void convert_integer(emb_string& dest, const char** s, T val, bool float_neg = false)
       {
	    bool negative ;
	    // default arg 'float_neg' is used for resolve problem with -0.0f and +0.0f
	    // in convert_float->convert_integer  where float arg is value as abs(X) < 1.0f
	    if ( float_neg )
	      {
		// 'convert_float->convert_integer' path on negative float args in 'convert_float'
		negative = true ;
	      }
	    else
	      {
		// path for all integer and for positive float args
		negative = val < 0 ;
	      }

	    // for signum types
	    if (negative)   val=-val ;
	    uint8_t placeholder = 0 ;
	    uint8_t base = 0 ;
	    char pad_symbol = '0'   ;
	    bool pad_signum = false ;
	    bool hex_upper = false ;
	    const char val2hex[]="0123456789abcdef";


		     if ((**s)=='-')
			{
			  pad_signum = true;
			  (*s)++ ;
			}

		     if ((**s)=='*')
			{
			  pad_symbol = ' ';
			  (*s)++ ;
			}

		     if (!isdigit(**s))  throw_exeption_catcher("invalid integer format for emb_printf::convert_unsigned");

	 	     placeholder = *((*s)++) -'0' ;

	             if (isdigit(**s))   placeholder = placeholder*10 + *((*s)++) -'0' ;

	             // base system
	             switch( *((*s)++) )
	               {
	                 case 'X' :
	                   hex_upper = true ;
	                   base = 16 ;
	                   break ;
	                 case 'x' :
	                   base = 16 ;
	                   break ;
	                 case 'd' :
	                   base = 10 ;
	                   break ;
	                 case 'o' :
	                   base=8 ;
	                   break ;
	                 case 'b' :
	                   base = 2 ;
	                   break ;
	                 default:
	                   // default format base 10
	                   base = 10 ;  (*s)-- ;
	               }

	         size_t len_befor = dest.length();

	         while (val)
	            {
	               T frac = val%base ;
	               dest += (char)( hex_upper ?  toupper(val2hex[frac]) : val2hex[frac] ) ;
	               val /= base;
	            }

	         if ( negative )
	           {
	             if ( pad_symbol == ' ' )
	               {
	        	 dest+='-';
	        	 if ( dest.length() <  (len_befor + placeholder) )
	        	    dest.resize( len_befor + placeholder , pad_symbol ) ;
	        	 if (pad_signum)  dest+=' ';
	               }
	             else
	               {
	        	 if ( dest.length() <  (len_befor + placeholder) )
	        	    dest.resize( len_befor + placeholder , pad_symbol ) ;
	        	 dest+='-';
	               }
	           }
	         else // positive
	           {

	                if ( dest.length() <  (len_befor + placeholder) )
                          dest.resize( len_befor + placeholder , pad_symbol ) ;

	                if (pad_signum) dest+=' ';
	           }

	         std::reverse( dest.begin() + len_befor , dest.end());

       }


       //------------------------
       /* float format:
        *    %[-][*]n.m
        *             '-' - signum pad
        *             '*' - space pad owerwrite '0'
        *             n - min digit pads, 0 - not out in zero val, [0...64]
        *             m - min digit pads, 0 - not out in zero val, [0...64]
        *
        *
        */
       template <typename T>
       static inline void convert_float (emb_string& dest, const char** s, T val)
          {
	     // Extract integer part
             int32_t ipart = val;

             // convert integer part to string
             convert_integer( dest, s, ipart, val < 0.0f ) ;

             // skip "." symbol
             dest+='.';
             (*s)++   ;

             // read frac pads
	     size_t frac_pads = 0 ;
             if (!isdigit(**s))  throw_exeption_catcher("invalid integer format for emb_printf::convert_unsigned");
             frac_pads = *((*s)++) -'0' ;
             if (isdigit(**s))   frac_pads = frac_pads*10 + *((*s)++) -'0' ;

             T frac = (val-ipart) < 0 ? -(val-ipart) : val-ipart ;

             while ( frac_pads-- )
                {
        	  frac = frac*((T)10) ;
                  uint32_t digit = (uint32_t)frac ;
                  frac = frac - (float)digit ;
                  dest+= char('0' + digit) ;
                }
            }


       //------------------------
       static void inline convert ( emb_string& dest, const char** s, const uint8_t       val )  { convert_integer( dest, s, val ) ; }
       static void inline convert ( emb_string& dest, const char** s, const uint16_t      val )  { convert_integer( dest, s, val ) ; }
       static void inline convert ( emb_string& dest, const char** s, const uint32_t      val )  { convert_integer( dest, s, val ) ; }
       static void inline convert ( emb_string& dest, const char** s, const uint64_t      val )  { convert_integer( dest, s, val ) ; }
       static void inline convert ( emb_string& dest, const char** s, const unsigned int  val )  { convert_integer( dest, s, val ) ; }

       //------------------------
       static void inline convert ( emb_string& dest, const char** s, const int8_t  val )  { convert_integer( dest, s, val ) ; }
       static void inline convert ( emb_string& dest, const char** s, const int16_t val )  { convert_integer( dest, s, val ) ; }
       static void inline convert ( emb_string& dest, const char** s, const int32_t val )  { convert_integer( dest, s, val ) ; }
       static void inline convert ( emb_string& dest, const char** s, const int64_t val )  { convert_integer( dest, s, val ) ; }
       static void inline convert ( emb_string& dest, const char** s, const int     val )  { convert_integer( dest, s, val ) ; }

       //------------------------
       static void inline convert ( emb_string& dest, const char** s, const float val )    { convert_float (dest, s, val); }
       static void inline convert ( emb_string& dest, const char** s, const double val )   { convert_float (dest, s, val); }

       //------------------------
       static void inline convert ( emb_string& dest, const char** s, const void* val )    { convert_integer( dest, s, (unsigned int)val ); }

       static void inline convert ( emb_string& dest, const char** s, const emb_string& val )  { (*s)++ ; dest += val ; }
       static void inline convert ( emb_string& dest, const char** s, const char* val)         { (*s)++ ; dest += emb_string(val) ; }
       static void inline convert ( emb_string& dest, const char** s, const char  val)         { (*s)++ ; dest.append(1,val) ;      }

       emb_printf() {} ;

   private:


};

} // kgp name space




#endif
