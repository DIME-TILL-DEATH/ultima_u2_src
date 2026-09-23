#include "reverb.h"

extern float accumul;
extern uint32_t reverb_point;
extern float memrev[];
extern float B;
extern float C;
extern float C;
extern float B;

inline float _read(uint32_t memadr)
{
	return memrev[(reverb_point + memadr) & 0xffff];
}
inline void _write(uint32_t memadr)
{
	memrev[(reverb_point + memadr) & 0xffff] = accumul;
}
//--------------------------------------------------------------------------------------------
inline void RZP (uint32_t ind_mem,float koef_mem)
{
  accumul = _read(ind_mem) * koef_mem;
}
inline void RAP (uint32_t ind_mem,float koef_mem)
{
  accumul += _read(ind_mem) * koef_mem;
}
inline void RCP (uint32_t ind_mem,float koef_mem)
{
  accumul = C + _read(ind_mem) * koef_mem;
}
inline void RAPB (uint32_t ind_mem,float koef_mem)
{
  accumul += _read(ind_mem) * koef_mem;
  B = accumul;
}
inline void WAP (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul += accumul * koef_mem;
}
inline void WZP (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul = accumul*koef_mem;
}
inline void WAPC (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul += accumul*koef_mem;
  C = accumul;
}
inline void WBPC (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul = B + accumul*koef_mem;
  C = accumul;
}
inline void WZPC (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul += koef_mem;
  C = accumul;
}
inline void WZPB (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul = accumul*koef_mem;
  B = accumul;
}
inline void WCP (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul = C + accumul*koef_mem;
}
inline void WBP (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul = B + accumul*koef_mem;
}
//--------------------------------------------------------------------------------------------------------------------------------
#define filt1_1   	2
#define filt1_2   	3
#define filt1_3   	4
#define filt2_1   	5
#define filt2_2   	6
#define filt3_1   	7
#define filt3_2   	8
#define filt4_1   	9
#define filt4_2   	10
#define temp_rev  	11
#define alp1		13
//-------------------------------------------------------------------------------------------------------------------------------
