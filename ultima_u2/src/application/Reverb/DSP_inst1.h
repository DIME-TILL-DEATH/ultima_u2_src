#include "init.h"
#include "fpv4-sp-d16-instr.h"

extern float accumul;
extern uint32_t ear_point;
extern float ear_mem[];
extern float B;
extern float C;

inline float _read(uint32_t memadr)
{
	return ear_mem[(ear_point + memadr) % pre_size];
}
inline void _write(uint32_t memadr)
{
	ear_mem[(ear_point + memadr) % pre_size] = accumul;
}
//--------------------------------------------------------------------------------------------
inline void _RZP (uint32_t ind_mem,float koef_mem)
{
  accumul = _read(ind_mem) * koef_mem;
}
inline void _RAP (uint32_t ind_mem,float koef_mem)
{
  accumul += _read(ind_mem) * koef_mem;
}
inline void _RCP (uint32_t ind_mem,float koef_mem)
{
  accumul = C + _read(ind_mem) * koef_mem;
}
inline void _RAPB (uint32_t ind_mem,float koef_mem)
{
  accumul += _read(ind_mem) * koef_mem;
  B = accumul;
}
inline void _WAP (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul += accumul * koef_mem;
}
inline void _WZP (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul = accumul*koef_mem;
}
inline void _WAPC (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul += accumul*koef_mem;
  C = accumul;
}
inline void _WBPC (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul = B + accumul*koef_mem;
  C = accumul;
}
inline void _WZPC (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul += koef_mem;
  C = accumul;
}
inline void _WZPB (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul = accumul*koef_mem;
  B = accumul;
}
inline void _WCP (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul = C + accumul*koef_mem;
}
inline void _WBP (uint32_t ind_mem,float koef_mem)
{
  _write(ind_mem);
  accumul = B + accumul*koef_mem;
}
