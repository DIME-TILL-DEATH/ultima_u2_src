#ifndef __IAP_H__
#define __IAP_H__


unsigned long* PrepareSector(unsigned int start_sector , unsigned end_sector );
unsigned long* Ram2Flash (unsigned int dest , unsigned int src , unsigned int size , unsigned int cclk  );
unsigned long* Erase (unsigned int start_sector , unsigned end_sector);
unsigned long* BlankCheck (unsigned int start_sector , unsigned end_sector);
unsigned long* GetPartID (void);
unsigned long* GetBootloaderVer (void);
unsigned long* Compare (unsigned int dest , unsigned int src , unsigned int size );

#endif /*#ifndef __IAP_H__*/