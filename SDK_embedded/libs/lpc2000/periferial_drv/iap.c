#include "iap.h"

typedef struct iap_data {
  unsigned long cmd;           // Command
  unsigned long par[4];        // Parameters
  unsigned long status;
  unsigned long result;
}Iap;

#define PrepareSectors       50
#define RAM2Flash            51
#define EraseSectors         52
#define BlankCheckSectors    53
#define ReadPartID           54
#define ReadBootloaderVer    55
#define CompareSectors       56
#define ReinvokeISP          57


#define CMD_SUCCESS         0      //  Command is executed successfully.
#define INVALID_COMMAND     1      //  Invalid command.
#define SRC_ADDR_ERROR      2      //  Source address is not on a word boundary.
#define DST_ADDR_ERROR      3      //  Destination address is not on a correct boundary.
#define SRC_ADDR_NOT_MAPPED 4      //  Source address is not mapped in the memory map.
#define DST_ADDR_NOT_MAPPED 5      //  Destination address is not mapped in the memory
#define COUNT_ERROR         6      //  Byte count is not multiple of 4 or is not a permitted value.
#define INVALID_SECTOR      7      //  Sector number is invalid.
#define SECTOR_NOT_BLANK    8      //  Sector is not blank.
#define SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION 9 //Command to prepare sector for write operation was not executed.
#define COMPARE_ERROR       10     //  Source and destination data is not same.
#define BUSY                11  


typedef void (*IAP)(unsigned long*,unsigned long* );
Iap data ;

unsigned long* PrepareSector(unsigned int start_sector , unsigned end_sector )
{
 data.cmd = PrepareSectors ;
 data.par[0] = start_sector ;
 data.par[1] = end_sector   ;
 IAP iap_entry = (IAP)0x7ffffff1 ;
 iap_entry ( (unsigned long  *)&data, ((unsigned long *)&data) + 5 );
 return &data.status ;
}

unsigned long* Ram2Flash (unsigned int dest , unsigned int src , unsigned int size , unsigned int cclk  )
 {
   data.cmd = RAM2Flash ;
   data.par[0] = dest ;
   data.par[1] = src ;
   data.par[2] = size ;
   data.par[3] = cclk ;
   IAP iap_entry = (IAP)0x7ffffff1 ;
   iap_entry ( (unsigned long  *)&data, ((unsigned long *)&data) + 5 );
   return &data.status ;
 } 

unsigned long* Erase (unsigned int start_sector , unsigned end_sector)
 {
   data.cmd = EraseSectors ;
   data.par[0] = start_sector ;
   data.par[1] = end_sector   ;
   IAP iap_entry = (IAP)0x7ffffff1 ;
   iap_entry ( (unsigned long  *)&data, ((unsigned long *)&data) + 5 );
   return &data.status ;
 } 

unsigned long* BlankCheck (unsigned int start_sector , unsigned end_sector)
 {
   data.cmd = BlankCheckSectors ;
   data.par[0] = start_sector ;
   data.par[1] = end_sector   ;
   IAP iap_entry = (IAP)0x7ffffff1 ;
   iap_entry ( (unsigned long  *)&data, ((unsigned long *)&data) + 5 );
   return &data.status ;
 } 

unsigned long* GetPartID (void)
 {
   data.cmd = ReadPartID ;
   IAP iap_entry = (IAP)0x7ffffff1 ;
   iap_entry ( (unsigned long  *)&data, ((unsigned long *)&data) + 5 );
   return &data.result ;
 } 

unsigned long* GetBootloaderVer (void)
 {
   data.cmd = ReadBootloaderVer ;
   IAP iap_entry = (IAP)0x7ffffff1 ;
   iap_entry ( (unsigned long  *)&data, ((unsigned long *)&data) + 5 );
   return &data.result ;
 } 

unsigned long* Compare (unsigned int dest , unsigned int src , unsigned int size )
 {
   data.cmd = CompareSectors ;
   data.par[0] = dest ;
   data.par[1] = src  ; 
   data.par[2] = size ;  
   IAP iap_entry = (IAP)0x7ffffff1 ;
   iap_entry ( (unsigned long  *)&data, ((unsigned long *)&data) + 5 );
   return &data.status ;
 } 
