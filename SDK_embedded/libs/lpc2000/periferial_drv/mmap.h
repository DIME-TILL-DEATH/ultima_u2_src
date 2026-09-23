#ifndef __MMAP_H__
#define __MMAP_H__


enum TMmap {mmBootloader = 0 , mmFlash , mmRam } ;
void  set_mmap( enum TMmap mmap) ;
enum TMmap get_mmap() ;


enum TExeptionType { etReset = 0 , etUndefined , etSwi , etPAbort , etDAbort , etReserve , etIrq , etFiq } ;
void set_exception_vector_ins ( enum TExeptionType exeption_type , unsigned int vector_ins  ) ;
void set_exception_handler_addr( enum TExeptionType exeption_type , unsigned int handler_addr ) ;
unsigned int  get_exception_vector_ins ( enum TExeptionType exeption_type);
unsigned int  get_exception_handler_addr( enum TExeptionType exeption_type);

void copy_bootsector_flash2ram ();

#endif /*__MMAP_H__*/