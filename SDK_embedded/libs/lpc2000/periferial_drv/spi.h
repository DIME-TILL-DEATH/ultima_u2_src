#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>

typedef enum { scspFIO0 , scsFIO1  } spi_1_cs_port ;

void spi_1_init( spi_1_cs_port port , uint32_t pin );
void spi_1_chip_enable();
void spi_1_chip_disable();

uint8_t spi_1_write_byte( uint8_t byte );
void    spi_1_read_block( uint8_t *buf, uint32_t size );
void    spi_1_write_block( uint8_t *buf, uint32_t size );


#endif /*__SPI_H__*/
