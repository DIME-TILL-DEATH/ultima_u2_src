#include "appdefs.h"
#include "SN1106.h"


volatile uint8_t dma_complete_fl = 1;
volatile uint8_t manual_complete_fl = 0;
__attribute__((section(".dtcm_data"))) uint8_t zero_buf[128];
__attribute__((section(".dtcm_data"))) uint8_t font_buf[128];

void spi3_dma_init_transfer(uint8_t length , uint32_t* adr)
{
	dma_complete_fl = 0;
	dma1_stream5.disable();
	dma1_stream5.memory0_address=((uint32_t)adr);
	dma1_stream5.number_of_data = length;
	dma1_stream0.disable();
	dma1_stream0.number_of_data = length;
    gpioa.pin15_reset();
    nop_rep(50);
    dma1_stream0.enable();
	dma1_stream5.enable();
    while(!dma_complete_fl);
    nop_rep(50);
	gpioa.pin15_set();
}
void sh1106_write_byte(uint8_t comm,uint8_t data)
{
  if(!comm)gpiod.pin6_reset();
  else gpiod.pin6_set();
  font_buf[0] = data;
  spi3_dma_init_transfer(1,(uint32_t*)font_buf);
  gpiod.pin6_set();
}
void sh1106_gotoXY(uint8_t x, uint8_t y)
{
  x = x + 2;                                          // Panel is 128 pixels wide, controller RAM has space for 132,    	                                                    // it's centered so add an offset to ram address.
  nop_while(0x1);
  sh1106_write_byte(SH1106_COMMAND, 0xB0 + y);           // Set row ... SH1106_COMMAND is defined as 0
  nop_while(0x1);
  sh1106_write_byte(SH1106_COMMAND, x & 0xF);            // Set lower column address ... SH1106_COMMAND is defined as 0
  nop_while(0x1);
  sh1106_write_byte(SH1106_COMMAND, 0x10 | (x >> 4));    // Set higher column address ... SH1106_COMMAND is defined as 0
}
void sh1106_clear()
{
  for (uint8_t j = 0 ; j < SH1106_ROWS ; j++)
   {
      sh1106_gotoXY(0, j);
      spi3_dma_init_transfer(128,(uint32_t*)zero_buf);
   }
}
void disp_init(void)
{
//-------------------------------------------------------------config display SPI3--------------------------------------
	gpioa.clock_enable();
	gpioc.clock_enable();
	gpiod.clock_enable();

	gpioc.pin10_mode_alternate_function();
	gpioc.pin10_output_type_pull_push();
	gpioc.pin10_pull_no();
	gpioc.pin10_output_speed_very_high();
	gpioc.pin10_af_spi3_sck_i2s3_ck();

	gpioc.pin12_mode_alternate_function();
	gpioc.pin12_output_type_pull_push();
	gpioc.pin12_pull_no();
	gpioc.pin12_output_speed_very_high();
	gpioc.pin12_af_spi3_mosi_i2s3_sd();

	gpioa.pin15_mode_output();
	gpioa.pin15_output_type_pull_push();
	gpioa.pin15_pull_no();
	gpioa.pin15_output_speed_high();
	gpioa.pin15_set();                            // display CS

	gpiod.pin5_mode_output();
	gpiod.pin5_output_type_pull_push();
	gpiod.pin5_pull_no();
	gpiod.pin5_output_speed_high();
	gpiod.pin5_reset();                          // display Reset

	gpiod.pin6_mode_output();
	gpiod.pin6_output_type_pull_push();
	gpiod.pin6_pull_no();
	gpiod.pin6_output_speed_high();
	gpiod.pin6_reset();                         // display DC

	spi3.clock_enable();
	spi3.reset();
	spi3.boud_rate_fpclk_div_8();
	spi3.clock_polarity_hight();
	spi3.clock_phase_second_clock();
	spi3.frame_first_msb();
	spi3.mode_selection_master();
	spi3.fifo_reception_threshold_1div4();
	spi3.data_size_8_bits();
	spi3.ss_output_enable();
	spi3.nss_pulse_management_enable();
	spi3.crc_polynomial=7;
	spi3.tx_buff_dma_enable();
	spi3.rx_dma_buff_enable();
	spi3.enable();

	dma1.clock_enable();
	dma1_stream5.channel_spi3_tx();
	dma1_stream5.number_of_data = 4;
	dma1_stream5.peripheral_address=((uint32_t)0x40003C0C) ;
	dma1_stream5.memory0_address=((uint32_t)0) ;
	dma1_stream5.direction_memory_to_peripheral();
	dma1_stream5.peripheral_increment_mode_disable();
	dma1_stream5.memory_increment_mode_enable();
	dma1_stream5.peripheral_data_size_byte();
	dma1_stream5.memory_data_size_byte();
	dma1_stream5.circular_mode_disable();
	dma1_stream5.disable();

	dma1_stream0.channel_spi3_rx();
	dma1_stream0.number_of_data = 4;
	dma1_stream0.peripheral_address=((uint32_t)0x40003C0C) ;
	dma1_stream0.memory0_address=((uint32_t)&zero_buf) ;
	dma1_stream0.direction_peripheral_to_memory();
	dma1_stream0.peripheral_increment_mode_disable();
	dma1_stream0.memory_increment_mode_enable();
	dma1_stream0.peripheral_data_size_byte();
	dma1_stream0.memory_data_size_byte();
	dma1_stream0.circular_mode_disable();
	dma1_stream0.disable();
	dma1_stream0.transfer_complete_interrupt_enable();
	nvic.dma1_stream0_priority(configMAX_SYSCALL_INTERRUPT_PRIORITY + 1);
	nvic.dma1_stream0_enable();

	memset(zero_buf,0,128);

  gpiod.pin5_set();
  nop_while(0xffff);
  sh1106_write_byte(SH1106_COMMAND, 0xAE);           /*display off*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0x02);           /*set lower column address*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0x10);           /*set higher column address*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0x40);           /*set display start line*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0xB0);           /*set page address*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0x81);           /*contract control*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0x80);        /*128*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0xA1);           /*set segment remap*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0xA6);  /*normal / reverse*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0xA8);           /*multiplex ratio*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0x3F);           /*duty = 1/32*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0xAD);           /*set charge pump enable*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0x8B);           /*external VCC   */
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0x30 | 2);     /*0X30---0X33  set VPP   9V liangdu!!!!*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0xC8);           /*Com scan direction*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0xD3);           /*set display offset*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0x00);           /*   0x20  */
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0xD5);           /*set osc division*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0x80);
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0xD9);           /*set pre-charge period*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0x1F);           /*0x22*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0xDA);           /*set COM pins*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0x12);
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0xDB);           /*set vcomh*/
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0x40);
  nop_while(0xff);
  sh1106_write_byte(SH1106_COMMAND, 0xAF);
  nop_while(0xff);
  sh1106_clear();
}
IRQ_HANDLER(dma1_stream0)
{
	dma1.stream0_transfer_complete_interrupt_clear();
	dma1.stream5_transfer_complete_interrupt_clear();
	dma_complete_fl = 1;
}
