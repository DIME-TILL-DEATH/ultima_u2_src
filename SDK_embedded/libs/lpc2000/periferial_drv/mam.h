#ifndef __MAM_H__
#define __MAM_H__

#define MAM_MODE_UNUSED   0x00
#define MAM_MODE_LINEAR   0x01
#define MAM_MODE_FULL     0x02

void set_mam( unsigned char mam_mode, unsigned char mam_tim ) ;
void get_mam( unsigned char* mam_mode, unsigned char* mam_tim ) ;

#endif /*__MAM_H__*/