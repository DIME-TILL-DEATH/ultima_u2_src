#ifndef __SUPSTL_H__
#define __SUPSTL_H__

// KGP tools embedded SDK
// Chernov S.A. aka klen
// klen_s@mail.ru

#include <limits>
#include <algorithm>
#include <cstring>
#include <ext/malloc_allocator.h>

extern "C" void* malloc( size_t ) ;
extern "C" void  free( void* ) ;

//-------- KGP utils & support ------------
#include <string> //need for basic_string

namespace kgp
{
  //-------------------------------------------------------------------------------------
  typedef std::basic_string<char, std::char_traits<char>, __gnu_cxx::malloc_allocator<char> > emb_string;   /// A string of @c char

  class compare
     {
         public:
            inline bool operator() (const char lhs, const char rhs) const {return lhs < rhs ;}
            inline bool operator() (const int& lhs, const int& rhs) const {return lhs < rhs ;}
            inline bool operator() (const float& lhs, const float& rhs) const {return lhs < rhs ;}
            inline bool operator() (const double& lhs, const double& rhs) const {return lhs < rhs ;}
            inline bool operator() (const char* lhs, const char* rhs) const {return strcmp(lhs,rhs) < 0  ;}
            inline bool operator() (const emb_string& lhs, const emb_string& rhs) const {return lhs==rhs ;}
     };
}

using namespace std ;
using namespace __gnu_cxx ;
using namespace kgp ;


#endif /* __SUPSTL_H__ */
