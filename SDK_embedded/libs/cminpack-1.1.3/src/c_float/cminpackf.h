#ifndef __CMINPACK_H__
#define __CMINPACK_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Cmake will define cminpack_EXPORTS on Windows when it
configures to build a shared library. If you are going to use
another build system on windows or create the visual studio
projects by hand you need to define cminpack_EXPORTS when
building a DLL on windows.
*/
#if defined (__GNUC__)
#define CMINPACK_DECLSPEC_EXPORT  __declspec(__dllexport__)
#define CMINPACK_DECLSPEC_IMPORT  __declspec(__dllimport__)
#endif
#if defined (_MSC_VER) || defined (__BORLANDC__)
#define CMINPACK_DECLSPEC_EXPORT  __declspec(dllexport)
#define CMINPACK_DECLSPEC_IMPORT  __declspec(dllimport)
#endif
#ifdef __WATCOMC__
#define CMINPACK_DECLSPEC_EXPORT  __export
#define CMINPACK_DECLSPEC_IMPORT  __import
#endif
#ifdef __IBMC__
#define CMINPACK_DECLSPEC_EXPORT  _Export
#define CMINPACK_DECLSPEC_IMPORT  _Import
#endif

#if !defined(CMINPACK_NO_DLL) && (defined(__WIN32__) || defined(WIN32) || defined (_WIN32))
#if defined(cminpack_EXPORTS) || defined(CMINPACK_EXPORTS) || defined(CMINPACK_DLL_EXPORTS)
    #define  CMINPACK_EXPORT CMINPACK_DECLSPEC_EXPORT
  #else
    #define  CMINPACK_EXPORT CMINPACK_DECLSPEC_IMPORT
  #endif /* cminpack_EXPORTS */
#else /* defined (_WIN32) */
 #define CMINPACK_EXPORT
#endif

/* Declarations for minpack */

/* Function types: */
/* The first argument can be used to store extra function parameters, thus */
/* avoiding the use of global variables. */
/* the iflag parameter is input-only (with respect to the FORTRAN */
/*  version), the output iflag value is the return value of the function. */
/* If iflag=0, the function shoulkd just print the current values (see */
/* the nprint parameters below). */
  
/* for hybrd1 and hybrd: */
/*         calculate the functions at x and */
/*         return this vector in fvec. */
/* return a negative value to terminate hybrd1/hybrd */
typedef int (*minpack_func_nn)(void *p, int n, const float *x, float *fvec, int iflag );

/* for hybrj1 and hybrj */
/*         if iflag = 1 calculate the functions at x and */
/*         return this vector in fvec. do not alter fjac. */
/*         if iflag = 2 calculate the jacobian at x and */
/*         return this matrix in fjac. do not alter fvec. */
/* return a negative value to terminate hybrj1/hybrj */
typedef int (*minpack_funcder_nn)(void *p, int n, const float *x, float *fvec, float *fjac,
                                  int ldfjac, int iflag );

/* for lmdif1 and lmdif */
/*         calculate the functions at x and */
/*         return this vector in fvec. */
/* return a negative value to terminate lmdif1/lmdif */
typedef int (*minpack_func_mn)(void *p, int m, int n, const float *x, float *fvec,
                               int iflag );

/* for lmder1 and lmder */
/*         if iflag = 1 calculate the functions at x and */
/*         return this vector in fvec. do not alter fjac. */
/*         if iflag = 2 calculate the jacobian at x and */
/*         return this matrix in fjac. do not alter fvec. */
/* return a negative value to terminate lmder1/lmder */
typedef int (*minpack_funcder_mn)(void *p, int m, int n, const float *x, float *fvec,
                                  float *fjac, int ldfjac, int iflag );

/* for lmstr1 and lmstr */
/*         if iflag = 1 calculate the functions at x and */
/*         return this vector in fvec. */
/*         if iflag = i calculate the (i-1)-st row of the */
/*         jacobian at x and return this vector in fjrow. */
/* return a negative value to terminate lmstr1/lmstr */
typedef int (*minpack_funcderstr_mn)(void *p, int m, int n, const float *x, float *fvec,
                                     float *fjrow, int iflag );






/* MINPACK functions: */
/* the info parameter was removed from most functions: the return */
/* value of the function is used instead. */
/* The argument 'p' can be used to store extra function parameters, thus */
/* avoiding the use of global variables. You can also think of it as a */
/* 'this' pointer a la C++. */

/* find a zero of a system of N nonlinear functions in N variables by
   a modification of the Powell hybrid method (Jacobian calculated by
   a forward-difference approximation) */
int CMINPACK_EXPORT hybrd1 ( minpack_func_nn fcn, 
	       void *p, int n, float *x, float *fvec, float tol,
	       float *wa, int lwa );

/* find a zero of a system of N nonlinear functions in N variables by
   a modification of the Powell hybrid method (Jacobian calculated by
   a forward-difference approximation, more general). */
int CMINPACK_EXPORT hybrd ( minpack_func_nn fcn,
	      void *p, int n, float *x, float *fvec, float xtol, int maxfev,
	      int ml, int mu, float epsfcn, float *diag, int mode,
	      float factor, int nprint, int *nfev,
	      float *fjac, int ldfjac, float *r, int lr, float *qtf,
	      float *wa1, float *wa2, float *wa3, float *wa4);
  
/* find a zero of a system of N nonlinear functions in N variables by
   a modification of the Powell hybrid method (user-supplied Jacobian) */
int CMINPACK_EXPORT hybrj1 ( minpack_funcder_nn fcn, void *p, int n, float *x,
	       float *fvec, float *fjac, int ldfjac, float tol,
	       float *wa, int lwa );
          
/* find a zero of a system of N nonlinear functions in N variables by
   a modification of the Powell hybrid method (user-supplied Jacobian,
   more general) */
int CMINPACK_EXPORT hybrj ( minpack_funcder_nn fcn, void *p, int n, float *x,
	      float *fvec, float *fjac, int ldfjac, float xtol,
	      int maxfev, float *diag, int mode, float factor,
	      int nprint, int *nfev, int *njev, float *r,
	      int lr, float *qtf, float *wa1, float *wa2,
	      float *wa3, float *wa4 );

/* minimize the sum of the squares of nonlinear functions in N
   variables by a modification of the Levenberg-Marquardt algorithm
   (Jacobian calculated by a forward-difference approximation) */
int CMINPACK_EXPORT lmdif1 ( minpack_func_mn fcn,
	       void *p, int m, int n, float *x, float *fvec, float tol,
	       int *iwa, float *wa, int lwa );

/* minimize the sum of the squares of nonlinear functions in N
   variables by a modification of the Levenberg-Marquardt algorithm
   (Jacobian calculated by a forward-difference approximation, more
   general) */
int CMINPACK_EXPORT lmdif ( minpack_func_mn fcn,
	      void *p, int m, int n, float *x, float *fvec, float ftol,
	      float xtol, float gtol, int maxfev, float epsfcn,
	      float *diag, int mode, float factor, int nprint,
	      int *nfev, float *fjac, int ldfjac, int *ipvt,
	      float *qtf, float *wa1, float *wa2, float *wa3,
	      float *wa4 );

/* minimize the sum of the squares of nonlinear functions in N
   variables by a modification of the Levenberg-Marquardt algorithm
   (user-supplied Jacobian) */
int CMINPACK_EXPORT lmder1 ( minpack_funcder_mn fcn,
	       void *p, int m, int n, float *x, float *fvec, float *fjac,
	       int ldfjac, float tol, int *ipvt,
	       float *wa, int lwa );

/* minimize the sum of the squares of nonlinear functions in N
   variables by a modification of the Levenberg-Marquardt algorithm
   (user-supplied Jacobian, more general) */
int CMINPACK_EXPORT lmder ( minpack_funcder_mn fcn,
	      void *p, int m, int n, float *x, float *fvec, float *fjac,
	      int ldfjac, float ftol, float xtol, float gtol,
	      int maxfev, float *diag, int mode, float factor,
	      int nprint, int *nfev, int *njev, int *ipvt,
	      float *qtf, float *wa1, float *wa2, float *wa3,
	      float *wa4 );

/* minimize the sum of the squares of nonlinear functions in N
   variables by a modification of the Levenberg-Marquardt algorithm
   (user-supplied Jacobian, minimal storage) */
int CMINPACK_EXPORT lmstr1 ( minpack_funcderstr_mn fcn, void *p, int m, int n,
	       float *x, float *fvec, float *fjac, int ldfjac,
	       float tol, int *ipvt, float *wa, int lwa );

/* minimize the sum of the squares of nonlinear functions in N
   variables by a modification of the Levenberg-Marquardt algorithm
   (user-supplied Jacobian, minimal storage, more general) */
int CMINPACK_EXPORT lmstr (  minpack_funcderstr_mn fcn, void *p, int m,
	      int n, float *x, float *fvec, float *fjac,
	      int ldfjac, float ftol, float xtol, float gtol,
	      int maxfev, float *diag, int mode, float factor,
	      int nprint, int *nfev, int *njev, int *ipvt,
	      float *qtf, float *wa1, float *wa2, float *wa3,
	      float *wa4 );
 
void CMINPACK_EXPORT chkder ( int m, int n, const float *x, float *fvec, float *fjac,
	       int ldfjac, float *xp, float *fvecp, int mode,
	       float *err  );

float CMINPACK_EXPORT dpmpar ( int i );

float CMINPACK_EXPORT enorm ( int n, const float *x );

/* compute a forward-difference approximation to the m by n jacobian
   matrix associated with a specified problem of m functions in n
   variables. */
int CMINPACK_EXPORT fdjac2(minpack_func_mn fcn,
	     void *p, int m, int n, float *x, const float *fvec, float *fjac,
	     int ldfjac, float epsfcn, float *wa);

/* compute a forward-difference approximation to the n by n jacobian
   matrix associated with a specified problem of n functions in n
   variables. if the jacobian has a banded form, then function
   evaluations are saved by only approximating the nonzero terms. */
int CMINPACK_EXPORT fdjac1(minpack_func_nn fcn,
	     void *p, int n, float *x, const float *fvec, float *fjac, int ldfjac,
	     int ml, int mu, float epsfcn, float *wa1,
	     float *wa2);

/* compute inverse(JtJ) after a run of lmdif or lmder. The covariance matrix is obtained
   by scaling the result by enorm(y)**2/(m-n). If JtJ is singular and k = rank(J), the
   pseudo-inverse is computed, and the result has to be scaled by enorm(y)**2/(m-k). */
void CMINPACK_EXPORT covar(int n, float *r, int ldr, 
           const int *ipvt, float tol, float *wa);

/* covar1 estimates the variance-covariance matrix:
   C = sigma**2 (JtJ)**+
   where (JtJ)**+ is the inverse of JtJ or the pseudo-inverse of JtJ (in case J does not have full rank),
   and sigma**2 = fsumsq / (m - k)
   where fsumsq is the residual sum of squares and k is the rank of J.
   The function returns 0 if J has full rank, else the rank of J.
*/
int CMINPACK_EXPORT covar1(int m, int n, float fsumsq, float *r, int ldr, 
                           const int *ipvt, float tol, float *wa);

/* internal MINPACK subroutines */
void dogleg(int n, const float *r, int lr, 
             const float *diag, const float *qtb, float delta, float *x, 
             float *wa1, float *wa2);
void qrfac(int m, int n, float *a, int
            lda, int pivot, int *ipvt, int lipvt, float *rdiag,
            float *acnorm, float *wa);
void qrsolv(int n, float *r, int ldr, 
             const int *ipvt, const float *diag, const float *qtb, float *x, 
             float *sdiag, float *wa);
void qform(int m, int n, float *q, int
            ldq, float *wa);
void r1updt(int m, int n, float *s, int
             ls, const float *u, float *v, float *w, int *sing);
void r1mpyq(int m, int n, float *a, int
             lda, const float *v, const float *w);
void lmpar(int n, float *r, int ldr, 
            const int *ipvt, const float *diag, const float *qtb, float delta, 
            float *par, float *x, float *sdiag, float *wa1, 
            float *wa2);
void rwupdt(int n, float *r, int ldr, 
             const float *w, float *b, float *alpha, float *cos, 
             float *sin);
#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __CMINPACK_H__ */
