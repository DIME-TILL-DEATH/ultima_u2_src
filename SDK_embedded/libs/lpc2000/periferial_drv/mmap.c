#include "mmap.h"
#include "lpc21xx.h"
#include "string.h"

 

void  set_mmap( enum TMmap mmap) 
{
  MEMMAP = mmap ;
}

enum TMmap get_mmap() 
{
  return MEMMAP ;
}


void set_exception_vector_ins ( enum TExeptionType exeption_type , unsigned int vector_ins  )
{
  ((volatile unsigned int *)0x40000000)[exeption_type ] = vector_ins ; 
}
void set_exception_handler_addr( enum TExeptionType exeption_type , unsigned int handler_addr )
{
  ((volatile unsigned int *)0x40000000)[exeption_type + 0x8 ] = handler_addr ; 
}

unsigned int  get_exception_vector_ins ( enum TExeptionType exeption_type)
{
  return ((volatile unsigned int *)0x40000000)[exeption_type] ;
}
unsigned int  get_exception_handler_addr( enum TExeptionType exeption_type)
{
  return ((volatile unsigned int *)0x40000000)[exeption_type + 0x8 ] ; 
}

void copy_bootsector_flash2ram ()
{
  // если функия вызывается, значит что таблица "in ram" векторов должна быть размещена
  // 64 * 4 = 64 байта вектора + дыра + 223 байта bootloader = 512 байт

  // это вызвано тем что скрипт линкера не имеет отделной фиксированной секции ".ram_vec_table"
  // такая секция добавляется как подсекция ".data" в случае наличия данных помеченных __attribute__((section (".ram_vec_table")))
  // данный подход экономит ОЗУ в случае отсутствия подсекций ".ram_vec_table" и облегчает работу
  // с ELF (всего 3 секции: .text .data .bss, остальные оформляются как подсекции)

  static void* ram_vec[64] __attribute__((section (".ram_vec_table"))) ;

  for (int i = 0 ; i < 16 ; i++) 
    ((volatile unsigned int *)ram_vec)[i] = ((volatile unsigned int *)0x0)[i] ;
}




