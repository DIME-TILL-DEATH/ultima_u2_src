#ifndef __SDCARD_H__
#define __SDCARD_H__

//  1) не допускается передача буффера в адрессном пространстве недоступном DMA (напрмер CCM)
//  2) максимальныое число блоков к обмену - 512 ( 512 байт *512 = 256кБ -> 256*1024 / 4 [байта/транз] = 56 * 1024 = 2^16 => разрядность dma.ndtr)

/************************ SDIO DEFENITION FOR PERIPHERIASLS ********************************


constexpr uint32_t SDCARD_DETECT_VAL        = 0;
constexpr uint32_t SDIO_CMD0TIMEOUT         = 0x00010000;
constexpr uint8_t  INIT_DIVIDER             = 118;
constexpr uint8_t  TRANSFER_DIVIDER         = 0;
constexpr uint32_t SDIO_IRQ_PRIORITY        = 0xa0;
constexpr uint32_t SDIO_DMA_IRQ_PRIORITY    = 0xf0;
constexpr uint32_t SDIO_DMA_STREAM_PRIORITY = dma_stream_t::configuration_t::priority_level_t::low;

/************** SDIO/DMA IRQ HANDLERS IMPLEMENTATION ADD TO USER CODE  *********************


sdcard_t sdcard ;

extern "C"
{
	void sdio_irq_handler()
	{
	   sdcard.sdio_irq_proc();
	}

	void dma2_stream3_irq_handler(void)
	{
	   sdcard.dma_irq_proc();
	}

	void detect_gpio_irq_handler(void)
	{
	  if ( sdcard.detect()==sdcard_t::present)
	     sdcard_initialize();
	  else
	     sdcard_deinitialize();
	}
}
/****************************************************************************/

#include "sdk.h"

class sdcard_t
{
public:
   enum consts_t {
     SD_CMD_GO_IDLE_STATE                       = 0,
     SD_CMD_SEND_OP_COND                        = 1,
     SD_CMD_ALL_SEND_CID                        = 2,
     SD_CMD_SET_REL_ADDR                        = 3,
     SD_CMD_SET_DSR                             = 4,
     SD_CMD_SDIO_SEN_OP_COND                    = 5,
     SD_CMD_HS_SWITCH                           = 6,
     SD_CMD_SEL_DESEL_CARD                      = 7,
     SD_CMD_HS_SEND_EXT_CSD                     = 8,
     SD_CMD_SEND_CSD                            = 9,
     SD_CMD_SEND_CID                            = 10,
     SD_CMD_READ_DAT_UNTIL_STOP                 = 11,
     SD_CMD_STOP_TRANSMISSION                   = 12,
     SD_CMD_SEND_STATUS                         = 13,
     SD_CMD_HS_BUSTEST_READ                     = 14,
     SD_CMD_GO_INACTIVE_STATE                   = 15,
     SD_CMD_SET_BLOCKLEN                        = 16,
     SD_CMD_READ_SINGLE_BLOCK                   = 17,
     SD_CMD_READ_MULT_BLOCK                     = 18,
     SD_CMD_HS_BUSTEST_WRITE                    = 19,
     SD_CMD_WRITE_DAT_UNTIL_STOP                = 20,
     SD_CMD_SET_BLOCK_COUNT                     = 23,
     SD_CMD_WRITE_SINGLE_BLOCK                  = 24,
     SD_CMD_WRITE_MULT_BLOCK                    = 25,
     SD_CMD_PROG_CID                            = 26,
     SD_CMD_PROG_CSD                            = 27,
     SD_CMD_SET_WRITE_PROT                      = 28,
     SD_CMD_CLR_WRITE_PROT                      = 29,
     SD_CMD_SEND_WRITE_PROT                     = 30,
     SD_CMD_SD_ERASE_GRP_START                  = 32,
     SD_CMD_SD_ERASE_GRP_END                    = 33,
     SD_CMD_ERASE_GRP_START                     = 35,
     SD_CMD_ERASE_GRP_END                       = 36,
     SD_CMD_ERASE                               = 38,
     SD_CMD_FAST_IO                             = 39,
     SD_CMD_GO_IRQ_STATE                        = 40,
     SD_CMD_LOCK_UNLOCK                         = 42,
     SD_CMD_APP_CMD                             = 55,
     SD_CMD_GEN_CMD                             = 56,
     SD_CMD_NO_CMD                              = 64,

     SD_CMD_APP_SD_SET_BUSWIDTH                 = 6,
     SD_CMD_SD_APP_STAUS                        = 13,
     SD_CMD_SD_APP_SEND_NUM_WRITE_BLOCKS        = 22,
     SD_CMD_SD_APP_OP_COND                      = 41,
     SD_CMD_SD_APP_SET_CLR_CARD_DETECT          = 42,
     SD_CMD_SD_APP_SEND_SCR                     = 51,
     SD_CMD_SDIO_RW_DIRECT                      = 52,
     SD_CMD_SDIO_RW_EXTENDED                    = 53,

     SD_CMD_SD_APP_GET_MKB                      = 43,
     SD_CMD_SD_APP_GET_MID                      = 44,
     SD_CMD_SD_APP_SET_CER_RN1                  = 45,
     SD_CMD_SD_APP_GET_CER_RN2                  = 46,
     SD_CMD_SD_APP_SET_CER_RES2                 = 47,
     SD_CMD_SD_APP_GET_CER_RES1                 = 48,
     SD_CMD_SD_APP_SECURE_READ_MULTIPLE_BLOCK   = 18,
     SD_CMD_SD_APP_SECURE_WRITE_MULTIPLE_BLOCK  = 25,
     SD_CMD_SD_APP_SECURE_ERASE                 = 38,
     SD_CMD_SD_APP_CHANGE_SECURE_AREA           = 49,
     SD_CMD_SD_APP_SECURE_WRITE_MKB             = 48,

     SD_OCR_ADDR_OUT_OF_RANGE        		= 0x80000000,
     SD_OCR_ADDR_MISALIGNED         		= 0x40000000,
     SD_OCR_BLOCK_LEN_ERR            		= 0x20000000,
     SD_OCR_ERASE_SEQ_ERR            		= 0x10000000,
     SD_OCR_BAD_ERASE_PARAM          		= 0x08000000,
     SD_OCR_WRITE_PROT_VIOLATION     		= 0x04000000,
     SD_OCR_LOCK_UNLOCK_FAILED       		= 0x01000000,
     SD_OCR_COM_CRC_FAILED           		= 0x00800000,
     SD_OCR_ILLEGAL_CMD              		= 0x00400000,
     SD_OCR_CARD_ECC_FAILED          		= 0x00200000,
     SD_OCR_CC_ERROR                 		= 0x00100000,
     SD_OCR_GENERAL_UNKNOWN_ERROR    		= 0x00080000,
     SD_OCR_STREAM_READ_UNDERRUN     		= 0x00040000,
     SD_OCR_STREAM_WRITE_OVERRUN     		= 0x00020000,
     SD_OCR_CID_CSD_OVERWRIETE       		= 0x00010000,
     SD_OCR_WP_ERASE_SKIP            		= 0x00008000,
     SD_OCR_CARD_ECC_DISABLED        		= 0x00004000,
     SD_OCR_ERASE_RESET              		= 0x00002000,
     SD_OCR_AKE_SEQ_ERROR            		= 0x00000008,
     SD_OCR_ERRORBITS                		= 0xFDFFE008,

     SD_R6_GENERAL_UNKNOWN_ERROR     		= 0x00002000,
     SD_R6_ILLEGAL_CMD               		= 0x00004000,
     SD_R6_COM_CRC_FAILED            		= 0x00008000,

     SD_VOLTAGE_WINDOW_SD            			 = 0x80100000,
     SD_HIGH_CAPACITY                			 = 0x40000000,
     SD_STD_CAPACITY                 			 = 0x00000000,
     SD_CHECK_PATTERN                			 = 0x000001AA,

     SD_MAX_VOLT_TRIAL               			 = 0x0000FFFF,
     SD_ALLZERO                      			 = 0x00000000,

     SD_WIDE_BUS_SUPPORT             			 = 0x00040000,
     SD_SINGLE_BUS_SUPPORT           			 = 0x00010000,
     SD_CARD_LOCKED                  			 = 0x02000000,

     SD_DATATIMEOUT                  			 = 0xFFFFFFFF,
     SD_0TO7BITS                     			 = 0x000000FF,
     SD_8TO15BITS                    			 = 0x0000FF00,
     SD_16TO23BITS                   			 = 0x00FF0000,
     SD_24TO31BITS                  			 = 0xFF000000,
     SD_MAX_DATA_LENGTH              			 = 0x01FFFFFF,

     SD_HALFFIFO                     			 = 0x00000008,
     SD_HALFFIFOBYTES                			 = 0x00000020,

     SD_CCCC_LOCK_UNLOCK             			 = 0x00000080,
     SD_CCCC_WRITE_PROT             			 = 0x00000040,
     SD_CCCC_ERASE                   			 = 0x00000020,

     SDIO_SEND_IF_COND               			 = 0x00000008,

     // дополнительные константы
     SD_DMA_MAX_TRANSFER_SIZE                            = 0x40000, // размер NDTR * 4 ( словные транзакции обмена ) - 256кБ
   };

   enum present_t { present=SDCARD_DETECT_VAL, not_present = !present };
   enum transfer_state_t : uint8_t { transfer_ok = 0, transfer_busy, transfer_error } ;
   enum result_t: uint8_t
      {
  	SD_OK,
  	SD_CMD_CRC_FAIL,
  	SD_DATA_CRC_FAIL,
  	SD_CMD_RSP_TIMEOUT,
  	SD_DATA_TIMEOUT,
  	SD_TX_UNDERRUN,
  	SD_RX_OVERRUN,
  	SD_START_BIT_ERR,
  	SD_CMD_OUT_OF_RANGE,
  	SD_ADDR_MISALIGNED,
  	SD_BLOCK_LEN_ERR,
  	SD_ERASE_SEQ_ERR,
  	SD_BAD_ERASE_PARAM,
  	SD_WRITE_PROT_VIOLATION,
  	SD_LOCK_UNLOCK_FAILED,
  	SD_COM_CRC_FAILED,
  	SD_ILLEGAL_CMD,
  	SD_CARD_ECC_FAILED,
  	SD_CC_ERROR,
  	SD_GENERAL_UNKNOWN_ERROR,
  	SD_STREAM_READ_UNDERRUN,
  	SD_STREAM_WRITE_OVERRUN,
  	SD_CID_CSD_OVERWRITE,
  	SD_WP_ERASE_SKIP,
  	SD_CARD_ECC_DISABLED,
  	SD_ERASE_RESET,
  	SD_AKE_SEQ_ERROR,
  	SD_INVALID_VOLTRANGE,
  	SD_ADDR_OUT_OF_RANGE,
  	SD_SWITCH_ERROR,
  	SD_SDIO_DISABLED,
  	SD_SDIO_FUNCTION_BUSY,
  	SD_SDIO_FUNCTION_FAILED,
  	SD_SDIO_UNKNOWN_FUNCTION,
  	SD_INTERNAL_ERROR,
  	SD_NOT_CONFIGURED,
  	SD_REQUEST_PENDING,
  	SD_REQUEST_NOT_APPLICABLE,
  	SD_INVALID_PARAMETER,
  	SD_UNSUPPORTED_FEATURE,
  	SD_UNSUPPORTED_HW,
  	SD_ERROR,

	// дополнительные кода ошибок
	SD_UNSUPPORTED_DMA_TRANSFER_SIZE = 128,
     } ;


        struct card_info_t
   		  {
                     struct csd_t
                      {
          	        uint8_t  CSDStruct;
          	        uint8_t  SysSpecVersion;
          	        uint8_t  Reserved1;
          	        uint8_t  TAAC;
          	        uint8_t  NSAC;
          	        uint8_t  MaxBusClkFrec;
          	        uint16_t CardComdClasses;
          	        uint8_t  RdBlockLen;
          	        uint8_t  PartBlockRead;
          	        uint8_t  WrBlockMisalign;
          	        uint8_t  RdBlockMisalign;
          	        uint8_t  DSRImpl;
          	        uint8_t  Reserved2;
          	        uint32_t DeviceSize;
          	        uint8_t  MaxRdCurrentVDDMin;
          	        uint8_t  MaxRdCurrentVDDMax;
          	        uint8_t  MaxWrCurrentVDDMin;
          	        uint8_t  MaxWrCurrentVDDMax;
          	        uint8_t  DeviceSizeMul;
          	        uint8_t  EraseGrSize;
          	        uint8_t  EraseGrMul;
          	        uint8_t  WrProtectGrSize;
          	        uint8_t  WrProtectGrEnable;
          	        uint8_t  ManDeflECC;
          	        uint8_t  WrSpeedFact;
          	        uint8_t  MaxWrBlockLen;
          	        uint8_t  WriteBlockPaPartial;
          	        uint8_t  Reserved3;
          	        uint8_t  ContentProtectAppli;
          	        uint8_t  FileFormatGrouop;
          	        uint8_t  CopyFlag;
          	        uint8_t  PermWrProtect;
          	        uint8_t  TempWrProtect;
          	        uint8_t  FileFormat;
          	        uint8_t  ECC;
          	        uint8_t  CSD_CRC;
          	        uint8_t  Reserved4;
                      } csd     ;
                    struct cid_t
                      {
                      	uint8_t  manufacturer_id;
                      	uint16_t orem_app_id;
                      	uint32_t product_name_1;
                      	uint8_t  product_name_2;
                      	uint8_t  product_revision;
                      	uint32_t product_serial_number;
                      	uint8_t  reserve_1;
                      	uint16_t manufactured_date;
                      	uint8_t  cid_crc;
                      	uint8_t  reserve_2;
                      } cid;
   		    uint64_t capacity;
   		    uint32_t block_size;
   		    uint16_t rca;
   		    enum type_t { std_capacity_sd_card_v1_1,
   		                  std_capacity_sd_card_v2_0,
   		                  high_capacity_std_card,
   		                  multimedia_card,
   		                  secure_digital_io_card,
   		                  high_speed_multimedia_card,
   		                  secure_digital_io_combo_card,
   		                  high_capacity_mmc_card }   type;
   		  };

	  struct card_status_t
		  {
		    uint8_t bus_width;
		    uint8_t recured_mode;
		    uint16_t sd_card_type;
		    uint32_t size_of_protected_area;
	            uint8_t speed_class;
		    uint8_t performance_movi;
		    uint8_t allocation_unit_size;
		    uint16_t erase_size;
		    uint8_t erase_timeout;
		    uint8_t erase_offset;
		  } ;


	inline ~sdcard_t() {}
	inline sdcard_t() { result=SD_ERROR; is_initialized=false; card_info.type=card_info_t::std_capacity_sd_card_v1_1; };

	inline result_t init()
	{

	        if ( is_initialized ) return SD_OK ;

		gpio_t::pin_configure( SDCARD_DETECT ) ;


		if (detect() == not_present)
			return SD_ERROR;

		gpio_t::pin_configure(SDCARD_D0);
		gpio_t::pin_configure(SDCARD_D1);
		gpio_t::pin_configure(SDCARD_D2);
		gpio_t::pin_configure(SDCARD_D3);
		gpio_t::pin_configure(SDCARD_CMD);
		gpio_t::pin_configure(SDCARD_CLK);

		nvic.sdio_priority(SDIO_IRQ_PRIORITY);
		nvic.sdio_enable();
		rcc.sdio_enable();

		nvic.dma2_stream3_priority(SDIO_DMA_IRQ_PRIORITY);
		nvic.dma2_stream3_enable();
		dma2.clock_enable();

		dma_init();

		result = SD_OK;

	        sdio.reset();

	        sdio.clock_divider_bypass_disable();
		sdio.bus_wide1();
		sdio.clk_divider(INIT_DIVIDER);
		sdio.ck_polarity_rising();
		sdio.flow_control_disable();
		sdio.power_saving_disable();

	  	power_on();

	  	if (result != SD_OK)
	  		return result;

	  	cards_init();

	  	if (result != SD_OK)
	  		return result;

	  	sdio.clock_control.modify( (sdio_t::clock_control_t::clk_divider_t::enum_t)TRANSFER_DIVIDER,
					   sdio_t::clock_control_t::power_saving_t::enum_t::disable,
					   sdio_t::clock_control_t::clock_divider_bypass_t::enum_t::disable,
					   sdio_t::clock_control_t::bus_wide_t::enum_t::wide1,
					   sdio_t::clock_control_t::ck_polarity_t::enum_t::rising,
					   sdio_t::clock_control_t::flow_control_t::enum_t::disable) ;

	  	if (result == SD_OK)
	    	   select_deselect();

	  	if (result == SD_OK)
	    	   enable_wide_bus_operation(sdio_t::clock_control_t::bus_wide_t::enum_t::wide4);

	  	if (result == SD_OK)
	  		is_initialized = true;
		return (result);
	}

	inline void deinit()
	{
	  	is_initialized = false;

	  	power_off();

	  	nvic.sdio_priority(0);
		nvic.sdio_disable();
		rcc.sdio_reset();
		rcc.sdio_disable();

		dma2_stream3.reset();

		nvic.dma2_stream3_priority(0);
		nvic.dma2_stream3_disable();

		gpio_t::pin_default_state(SDCARD_D0);
		gpio_t::pin_default_state(SDCARD_D1);
		gpio_t::pin_default_state(SDCARD_D2);
		gpio_t::pin_default_state(SDCARD_D3);
		gpio_t::pin_default_state(SDCARD_CMD);
		gpio_t::pin_default_state(SDCARD_CLK);
		gpio_t::pin_default_state(SDCARD_DETECT) ;
	}


	inline result_t read_sc(uint8_t *buffer, uint32_t address, const uint32_t blockcount)
	{
	        result = SD_OK;
		xfer_error = SD_OK;
		end_of_xfer = false;
		stop_condition = true;

		sdio.data_control.write(0);

		sdio.mask.modify( sdio_t::mask_t::data_block_crc_failed_interrupt_t::enable,
				  sdio_t::mask_t::data_timeout_interrupt_t::enable,
				  sdio_t::mask_t::data_end_interrupt_t::enable,
				  sdio_t::mask_t::rx_fifo_overrun_error_interrupt_t::enable,
				  sdio_t::mask_t::start_bit_not_detected_interrupt_t::enable
	                        ) ;

		sdio.dma_enable();
                dma_rx_config((uint32_t *)buffer, blockcount); if (result != SD_OK)  return result;

                address *= card_info.block_size;

	  	sdio.send_command(cmd_set_block_len, card_info.block_size);
	  	cmd_R1_error(cmd_set_block_len.index); if (result != SD_OK) return result ;

		sdio.data_timer = SD_DATATIMEOUT;
		sdio.data_length = card_info.block_size * blockcount;
		sdio.data_control.modify( sdio_t::data_control_t::transfer_t::enable,
                                          sdio_t::data_control_t::direction_t::card_to_controller,
                                          sdio_t::data_control_t::transfer_mode_t::block,
                                          sdio_t::data_control_t::block_size_t::bytes512);

	  	if( blockcount > 1 )
	  	  {
	  	     sdio.send_command(cmd_read_mult_block, address);
	  	     cmd_R1_error(cmd_read_mult_block.index); if (result != SD_OK) return result ;
	  	  }
	  	else
	  	  {
	  	     sdio.send_command(cmd_read_single_block, address);
	  	     cmd_R1_error(cmd_read_single_block.index); if (result != SD_OK) return result ;
	  	  }

	  	wait_read_operation( blockcount > 1 );

		return result ;
	}

	inline result_t write_sc(const uint8_t *buffer, uint32_t address, const uint32_t blockcount)
	{
	        result = SD_OK;

		xfer_error = SD_OK;
		end_of_xfer = false;
		stop_condition = true;

	        sdio.data_control.write(0);

	        sdio.mask.modify( sdio_t::mask_t::data_block_crc_failed_interrupt_t::enable,
				  sdio_t::mask_t::data_timeout_interrupt_t::enable,
				  sdio_t::mask_t::data_end_interrupt_t::enable,
				  sdio_t::mask_t::tx_fifo_underrun_error_interrupt_t::enable,
				  sdio_t::mask_t::start_bit_not_detected_interrupt_t::enable
	                        ) ;

	        dma_tx_config((uint32_t *)buffer, blockcount); if (result != SD_OK)  return result;
	        sdio.dma_enable();

	        address *= card_info.block_size;

	  	sdio.send_command(cmd_set_block_len, card_info.block_size);
	  	cmd_R1_error(cmd_set_block_len.index);  if (result != SD_OK) return result ;
/*
	  	sdio.send_command(cmd_app_cmd, card_info.rca << 16);
	  	cmd_R1_error(cmd_app_cmd.index);  if (result != SD_OK) return result ;

	  	sdio.send_command(cmd_set_block_count, blockcount);
	  	cmd_R1_error(cmd_set_block_count.index);  if (result != SD_OK) return result ;
*/
	        if( blockcount > 1 )
	  	  {
	  	     sdio.send_command(cmd_write_mult_block, address);
	  	     cmd_R1_error(cmd_write_mult_block.index);   if (result != SD_OK) return result ;
	  	  }
	  	else
	  	  {
	  	     sdio.send_command(cmd_write_single_block, address);
	  	     cmd_R1_error(cmd_write_single_block.index);  if (result != SD_OK) return result ;
	  	  }

		sdio.data_timer = SD_DATATIMEOUT;
		sdio.data_length = card_info.block_size * blockcount;
		sdio.data_control.modify( sdio_t::data_control_t::transfer_t::enable,
                                    sdio_t::data_control_t::direction_t::controller_to_card,
                                    sdio_t::data_control_t::transfer_mode_t::block,
                                    sdio_t::data_control_t::block_size_t::bytes512);


		wait_write_operation( blockcount > 1 );

	  	return result ;

	}

	inline result_t erase_sc(uint32_t startaddr, uint32_t endaddr)
	{
	        result = SD_OK;
	  	uint32_t delay = 0;
	  	uint32_t maxdelay = 0;
	  	uint8_t cardstate = 0;

	  	if (  ! (card_info.csd.CardComdClasses & SD_CCCC_ERASE) )
	  	   {
	    	      result = SD_REQUEST_NOT_APPLICABLE;
	    	      return(result);
	  	   }

	  	maxdelay = 120000 / (TRANSFER_DIVIDER + 2);

	  	if (sdio.response_1 & SD_CARD_LOCKED)
	  	   {
	    	      result = SD_LOCK_UNLOCK_FAILED;
	    	      return(result);
	  	   }

	    	      startaddr *= card_info.block_size;
	    	      endaddr *= card_info.block_size;


	  	if ((card_info.type == card_info_t::std_capacity_sd_card_v1_1) ||
	  		(card_info.type == card_info_t::std_capacity_sd_card_v2_0) ||
			(card_info.type == card_info_t::high_capacity_std_card))
	  	   {
	  	        sdio.send_command(cmd_sd_erase_grp_start, startaddr);
	  		cmd_R1_error(cmd_sd_erase_grp_start.index);

	   		if (result != SD_OK) return(result);

	  	  	sdio.send_command(cmd_sd_erase_grp_end, endaddr);
	  	  	cmd_R1_error(cmd_sd_erase_grp_end.index);

	   		if (result != SD_OK) return result ;
	  	   }

	  	cmd_R1_error(SD_CMD_ERASE);

	  	if (result != SD_OK) return result;

	  	for (delay = 0; delay < maxdelay; delay++) { }

	  	is_busy(cardstate);
	  	delay = SD_DATATIMEOUT;

	  	while ((delay > 0) && (result == SD_OK) && ((card_programming == cardstate) || (card_receiving == cardstate)))
	  	   {
	    	      is_busy(cardstate);
	    	      delay--;
	  	   }

	  	return result ;
	}

//***********

	inline result_t read_hcxc(uint8_t *buffer, uint32_t address, const uint32_t blockcount)
	{
	        result = SD_OK;
		xfer_error = SD_OK;
		end_of_xfer = false;
		stop_condition = true;

		sdio.data_control.write(0);

		sdio.mask.modify( sdio_t::mask_t::data_block_crc_failed_interrupt_t::enable,
				  sdio_t::mask_t::data_timeout_interrupt_t::enable,
				  sdio_t::mask_t::data_end_interrupt_t::enable,
				  sdio_t::mask_t::rx_fifo_overrun_error_interrupt_t::enable,
				  sdio_t::mask_t::start_bit_not_detected_interrupt_t::enable
	                        ) ;

		sdio.dma_enable();
                dma_rx_config((uint32_t *)buffer,blockcount); if (result != SD_OK)  return result;

		sdio.data_timer = SD_DATATIMEOUT;
		sdio.data_length = card_info.block_size * blockcount;
		sdio.data_control.modify( sdio_t::data_control_t::transfer_t::enable,
                                          sdio_t::data_control_t::direction_t::card_to_controller,
                                          sdio_t::data_control_t::transfer_mode_t::block,
                                          sdio_t::data_control_t::block_size_t::bytes512);

	  	if( blockcount > 1 )
	  	  {
	  	     sdio.send_command(cmd_read_mult_block, address);
	  	     cmd_R1_error(cmd_read_mult_block.index); if (result != SD_OK)  return result;
	  	  }
	  	else
	  	  {
	  	     sdio.send_command(cmd_read_single_block, address);
	  	     cmd_R1_error(cmd_read_single_block.index); if (result != SD_OK)  return result;
	  	  }


	  	wait_read_operation( blockcount > 1 );

		return result ;
	}

	inline result_t write_hcxc(const uint8_t *buffer, uint32_t address, const uint32_t blockcount)
	{
	        result = SD_OK;

		xfer_error = SD_OK;
		end_of_xfer = false;
		stop_condition = true;

	        sdio.data_control.write(0);

	        sdio.mask.modify( sdio_t::mask_t::data_block_crc_failed_interrupt_t::enable,
				  sdio_t::mask_t::data_timeout_interrupt_t::enable,
				  sdio_t::mask_t::data_end_interrupt_t::enable,
				  sdio_t::mask_t::tx_fifo_underrun_error_interrupt_t::enable,
				  sdio_t::mask_t::start_bit_not_detected_interrupt_t::enable
	                        ) ;

	        dma_tx_config((uint32_t *)buffer,blockcount); if (result != SD_OK)  return result;
	        sdio.dma_enable();

/*
	  	sdio.send_command(cmd_set_block_len, 512);
	  	cmd_R1_error(cmd_set_block_len.index);  if (result != SD_OK) return result ;

	  	sdio.send_command(cmd_app_cmd, card_info.rca << 16);
	  	cmd_R1_error(cmd_app_cmd.index);  if (result != SD_OK) return result ;

	  	sdio.send_command(cmd_set_block_count, blockcount);
	  	cmd_R1_error(cmd_set_block_count.index);  if (result != SD_OK) return result ;
*/
	        if( blockcount > 1 )
	  	  {
	  	     sdio.send_command(cmd_write_mult_block, address);
	  	     cmd_R1_error(cmd_write_mult_block.index);   if (result != SD_OK) return result ;
	  	  }
	  	else
	  	  {
	  	     sdio.send_command(cmd_write_single_block, address);
	  	     cmd_R1_error(cmd_write_single_block.index);  if (result != SD_OK) return result ;
	  	  }

		sdio.data_timer = SD_DATATIMEOUT;
		sdio.data_length = card_info.block_size * blockcount;
		sdio.data_control.modify( sdio_t::data_control_t::transfer_t::enable,
                                          sdio_t::data_control_t::direction_t::controller_to_card,
                                          sdio_t::data_control_t::transfer_mode_t::block,
                                          sdio_t::data_control_t::block_size_t::bytes512);


		wait_write_operation( blockcount > 1 );

	  	return result ;
	}

	inline result_t erase_hcxc(uint32_t startaddr, uint32_t endaddr)
	{
	        result = SD_OK;
	  	uint32_t delay = 0;
	  	uint32_t maxdelay = 0;
	  	uint8_t cardstate = 0;

	  	if (  ! (card_info.csd.CardComdClasses & SD_CCCC_ERASE) )
	  	   {
	    	      result = SD_REQUEST_NOT_APPLICABLE;
	    	      return(result);
	  	   }

	  	maxdelay = 120000 / (TRANSFER_DIVIDER + 2);

	  	if (sdio.response_1 & SD_CARD_LOCKED)
	  	   {
	    	      result = SD_LOCK_UNLOCK_FAILED;
	    	      return(result);
	  	   }

	  	if ((card_info.type == card_info_t::std_capacity_sd_card_v1_1) ||
	  		(card_info.type == card_info_t::std_capacity_sd_card_v2_0) ||
			(card_info.type == card_info_t::high_capacity_std_card))
	  	   {
	  	        sdio.send_command(cmd_sd_erase_grp_start, startaddr);
	  		cmd_R1_error(cmd_sd_erase_grp_start.index);

	   		if (result != SD_OK) return(result);

	  	  	sdio.send_command(cmd_sd_erase_grp_end, endaddr);
	  	  	cmd_R1_error(cmd_sd_erase_grp_end.index);

	   		if (result != SD_OK) return result ;
	  	   }

	  	cmd_R1_error(SD_CMD_ERASE);

	  	if (result != SD_OK) return result;

	  	for (delay = 0; delay < maxdelay; delay++) { }

	  	is_busy(cardstate);
	  	delay = SD_DATATIMEOUT;

	  	while ((delay > 0) && (result == SD_OK) && ((card_programming == cardstate) || (card_receiving == cardstate)))
	  	   {
	    	      is_busy(cardstate);
	    	      delay--;
	  	   }

	  	return result ;
	}

	inline transfer_state_t get_status(void)
	   {
		state_t cardstate =  card_transfer;
	  	cardstate = get_state();

	  	if (cardstate == card_transfer) return(transfer_state_t::transfer_ok);
	  	else
	  	   if(cardstate == card_error)  return (transfer_state_t::transfer_error);
	  	   else  	                   return(transfer_busy);
	   }

	inline void card_status(card_status_t& card_status)
	{
	        result = SD_OK;

	        uint32_t sd_status[16];

	  	send_sd_status(sd_status);

	  	if (result  != SD_OK) return;

	  	    /* Byte 0 */
	  	    uint8_t tmp = (sd_status[0U] & 0xC0U) >> 6U;
	  	  card_status.bus_width = (uint8_t)tmp;

	  	    /* Byte 0 */
	  	    tmp = (sd_status[0U] & 0x20U) >> 5U;
	  	  card_status.recured_mode = (uint8_t)tmp;

	  	    /* Byte 2 */
	  	    tmp = (sd_status[0U] & 0x00FF0000U) >> 16U;
	  	  card_status.sd_card_type = (uint16_t)(tmp << 8U);

	  	    /* Byte 3 */
	  	    tmp = (sd_status[0U] & 0xFF000000U) >> 24U;
	  	  card_status.sd_card_type |= (uint16_t)tmp;

	  	    /* Byte 4 */
	  	    tmp = (sd_status[1U] & 0xFFU);
	  	  card_status.size_of_protected_area = (uint32_t)(tmp << 24U);

	  	    /* Byte 5 */
	  	    tmp = (sd_status[1U] & 0xFF00U) >> 8U;
	  	  card_status.size_of_protected_area |= (uint32_t)(tmp << 16U);

	  	    /* Byte 6 */
	  	    tmp = (sd_status[1U] & 0xFF0000U) >> 16U;
	  	  card_status.size_of_protected_area |= (uint32_t)(tmp << 8U);

	  	    /* Byte 7 */
	  	    tmp = (sd_status[1U] & 0xFF000000U) >> 24U;
	  	  card_status.size_of_protected_area |= (uint32_t)tmp;

	  	    /* Byte 8 */
	  	    tmp = (sd_status[2U] & 0xFFU);
	  	  card_status.speed_class = (uint8_t)tmp;

	  	    /* Byte 9 */
	  	    tmp = (sd_status[2U] & 0xFF00U) >> 8U;
	  	  card_status.performance_movi = (uint8_t)tmp;

	  	    /* Byte 10 */
	  	    tmp = (sd_status[2U] & 0xF00000U) >> 20U;
	  	  card_status.allocation_unit_size = (uint8_t)tmp;

	  	    /* Byte 11 */
	  	    tmp = (sd_status[2U] & 0xFF000000U) >> 24U;
	  	  card_status.erase_size = (uint16_t)(tmp << 8U);

	  	    /* Byte 12 */
	  	    tmp = (sd_status[3U] & 0xFFU);
	  	  card_status.erase_size |= (uint16_t)tmp;

	  	    /* Byte 13 */
	  	    tmp = (sd_status[3U] & 0xFC00U) >> 10U;
	  	  card_status.erase_timeout = (uint8_t)tmp;

	  	    /* Byte 13 */
	  	    tmp = (sd_status[3U] & 0x0300U) >> 8U;
	  	  card_status.erase_offset = (uint8_t)tmp;

	}

	present_t detect() const { return (present_t)((const gpio_t::pin_config_t&)SDCARD_DETECT).port.pin( ((const gpio_t::pin_config_t&)SDCARD_DETECT).pin ); }

	inline void sdio_irq_proc(void)
	   {
	          if (sdio.data_end())
		  {
		    xfer_error = SD_OK;
		    sdio.data_end_clear();
		    end_of_xfer = true;
		  }
		  else if (sdio.data_block_crc_failed())
		  {
	            sdio.data_block_crc_failed_clear();
		    xfer_error = SD_DATA_CRC_FAIL;
		  }
		  else if (sdio.data_timeout())
		  {
		    sdio.data_timeout_clear();
	            xfer_error = SD_DATA_TIMEOUT;
		  }
		  else if (sdio.rx_fifo_overrun_error())
		  {
	            sdio.rx_fifo_overrun_error_clear();
		    xfer_error = SD_RX_OVERRUN;
		  }
		  else if (sdio.tx_fifo_underrun_error())
		  {
		    sdio.tx_fifo_underrun_error_clear();
		    xfer_error = SD_TX_UNDERRUN;
		  }
		  else if (sdio.start_bit_not_detected())
		  {
		    sdio.start_bit_not_detected_clear();
		    xfer_error = SD_START_BIT_ERR;
		  }

		  //if (tx_request)
		  //   sdio.dma_disable();

		  sdio.mask.modify( sdio_t::mask_t::data_block_crc_failed_interrupt_t::disable,
			            sdio_t::mask_t::data_timeout_interrupt_t::disable,
				    sdio_t::mask_t::data_end_interrupt_t::disable,
				    sdio_t::mask_t::tx_fifo_underrun_error_interrupt_t::disable,
				    sdio_t::mask_t::rx_fifo_overrun_error_interrupt_t::disable,
				    sdio_t::mask_t::tx_fifo_half_empty_interrupt_t::disable,
				    sdio_t::mask_t::rx_fifo_half_full_interrupt_t::disable,
				    sdio_t::mask_t::start_bit_not_detected_interrupt_t::disable
		                  ) ;
	   }

	inline void dma_irq_proc(void)
	   {
	      if( dma2_stream3.transfer_complete_interrupt_flag() == dma_t::low_interrupt_status_t::stream3_transfer_complete_interrupt_t::occurred)
	         {
	            dma_end_of_xfer = true;
	            dma2.stream3_transfer_complete_interrupt_clear();
	         }
	      if( dma2_stream3.fifo_error_interrupt_flag() == dma_t::low_interrupt_status_t::stream3_fifo_error_interrupt_t::occurred )
	         {
		    dma2.stream3_fifo_error_interrupt_clear();
	         }
	   }

	inline uint32_t block_size() const { return card_info.block_size ; }
	inline uint32_t block_count()const { return card_info.capacity / card_info.block_size ; }
	inline uint32_t capacity()   const { return card_info.capacity ; }
	inline bool     is_hcxc()    const { return card_info.type == card_info_t::type_t::high_capacity_std_card ; }
	inline const card_info_t&  get_card_info() const { return card_info ; } ;


private:
	   enum state_t : uint32_t
	   {
	   	card_ready                  = ((uint32_t)0x00000001),
	   	card_identification         = ((uint32_t)0x00000002),
	   	card_standby                = ((uint32_t)0x00000003),
	   	card_transfer               = ((uint32_t)0x00000004),
	   	card_sending                = ((uint32_t)0x00000005),
	   	card_receiving              = ((uint32_t)0x00000006),
	   	card_programming            = ((uint32_t)0x00000007),
	   	card_disconnected           = ((uint32_t)0x00000008),
	   	card_error                  = ((uint32_t)0x000000FF),
	   } ;



	//volatile bool tx_request ;
        volatile result_t xfer_error;
        volatile bool dma_end_of_xfer;
        volatile bool end_of_xfer;
        volatile bool stop_condition;
        bool is_initialized;
        result_t result ;
	card_info_t card_info;

	inline void power_on(void)
	{
	        result = SD_OK;
	  	uint32_t response = 0, count = 0, validvoltage = 0;
	 	uint32_t SDType = SD_STD_CAPACITY;

	 	sdio.power_on();
	 	sdio.clk_enable();

	 	sdio.send_command(cmd_go_idle_state, 0);
	  	cmd_error();

	  	if (result != SD_OK)
	  		return;

		sdio.send_command(cmd_send_if_cond, SD_CHECK_PATTERN);
	  	cmd_R7_error();

	  	if (result == SD_OK)
	  	   {
	  	      card_info.type = card_info_t::std_capacity_sd_card_v2_0;
	    	      SDType = SD_HIGH_CAPACITY;
	  	   }

	  	else
	  	   {
	  	  	sdio.send_command(cmd_app_cmd, 0);
	  	  	cmd_R1_error(cmd_app_cmd.index);
	  	   }

	  	sdio.send_command(cmd_app_cmd, 0);
	  	cmd_R1_error(cmd_app_cmd.index);

	  	if (result == SD_OK)
	  	{
	    	   while ((!validvoltage) && (count < SD_MAX_VOLT_TRIAL))
	    	      {
	    	  	sdio.send_command(cmd_app_cmd, 0);
	      		cmd_R1_error(cmd_app_cmd.index);

	  		if (result != SD_OK)
	  		   return;

	   		sdio.send_command(cmd_sd_app_op_cond, SD_VOLTAGE_WINDOW_SD | SDType );
	                cmd_R3_error();

	  		if (result != SD_OK)
	  		   return;

	      		response = sdio.response_1;
	      		validvoltage = (((response >> 31) == 1) ? 1 : 0);
	      		count++;
	    	      }

	    	if (count >= SD_MAX_VOLT_TRIAL)
	    	   {
	      	      result = SD_INVALID_VOLTRANGE;
	              return;
	    	   }

	    	if (response &= SD_HIGH_CAPACITY)
	    	   {
	    	      card_info.type = card_info_t::high_capacity_std_card;
	    	   }
		}
	}

	inline void power_off()
	{
	        sdio.clk_disable();
	  	sdio.power_off();
	  	result=SD_OK;
	}

	inline void cards_init()
	{
	        result = SD_OK;
	  	uint16_t rca = 0x01;

	  	uint32_t CSD_Tab[4] = {0};
	  	uint32_t CID_Tab[4] = {0};

	  	if (card_info_t::secure_digital_io_card != card_info.type)
	  	   {
	  	      sdio.send_command(cmd_all_send_cid, 0 );
	              cmd_R2_error();

	  	      if (result != SD_OK)
	  	         return ;

	    	      CID_Tab[0] = sdio.response_1;
	    	      CID_Tab[1] = sdio.response_2;
	    	      CID_Tab[2] = sdio.response_3;
	    	      CID_Tab[3] = sdio.response_4;
	  	   }

	  	if ((card_info_t::std_capacity_sd_card_v1_1 == card_info.type) ||
	  		(card_info_t::std_capacity_sd_card_v2_0 == card_info.type) ||
	  		(card_info_t::secure_digital_io_combo_card == card_info.type) ||
	  		(card_info_t::high_capacity_std_card == card_info.type))
	  	   {
	  	      sdio.send_command(cmd_set_rel_addr, 0 );
	              cmd_R6_error(cmd_set_rel_addr.index, &rca);

	  	      if (result != SD_OK)
	  		 return ;
	  	   }

	  	if (card_info_t::secure_digital_io_card != card_info.type)
	  	   {
	   	      sdio.send_command(cmd_send_csd, rca << 16 );
	              cmd_R2_error();

	  	      if (result != SD_OK)
	                return ;

	    	      CSD_Tab[0] = sdio.response_1;
	    	      CSD_Tab[1] = sdio.response_2;
	    	      CSD_Tab[2] = sdio.response_3;
	    	      CSD_Tab[3] = sdio.response_4;
	  	   }

	  	//-----------------------------------------------
	        result = SD_OK;
	  	uint8_t tmp = 0;

	//  	card_info.type = (uint8_t)CardType;  заполнена в power_on
	  	card_info.rca = (uint16_t)rca;

	  	/*!< Byte 0 */
	  	tmp = (uint8_t)((CSD_Tab[0] & 0xFF000000) >> 24);
	  	card_info.csd.CSDStruct = (tmp & 0xC0) >> 6;
	  	card_info.csd.SysSpecVersion = (tmp & 0x3C) >> 2;
	  	card_info.csd.Reserved1 = tmp & 0x03;

	  	/*!< Byte 1 */
	  	tmp = (uint8_t)((CSD_Tab[0] & 0x00FF0000) >> 16);
	  	card_info.csd.TAAC = tmp;

	  	/*!< Byte 2 */
	  	tmp = (uint8_t)((CSD_Tab[0] & 0x0000FF00) >> 8);
	  	card_info.csd.NSAC = tmp;

	  	/*!< Byte 3 */
	  	tmp = (uint8_t)(CSD_Tab[0] & 0x000000FF);
	  	card_info.csd.MaxBusClkFrec = tmp;

	  	/*!< Byte 4 */
	  	tmp = (uint8_t)((CSD_Tab[1] & 0xFF000000) >> 24);
	  	card_info.csd.CardComdClasses = tmp << 4;

	  	/*!< Byte 5 */
	  	tmp = (uint8_t)((CSD_Tab[1] & 0x00FF0000) >> 16);
	  	card_info.csd.CardComdClasses |= (tmp & 0xF0) >> 4;
	  	card_info.csd.RdBlockLen = tmp & 0x0F;

	  	/*!< Byte 6 */
	  	tmp = (uint8_t)((CSD_Tab[1] & 0x0000FF00) >> 8);
	  	card_info.csd.PartBlockRead = (tmp & 0x80) >> 7;
	  	card_info.csd.WrBlockMisalign = (tmp & 0x40) >> 6;
	  	card_info.csd.RdBlockMisalign = (tmp & 0x20) >> 5;
	  	card_info.csd.DSRImpl = (tmp & 0x10) >> 4;
	  	card_info.csd.Reserved2 = 0; /*!< Reserved */

	  	if ((card_info.type == card_info_t::std_capacity_sd_card_v1_1) || (card_info.type == card_info_t::std_capacity_sd_card_v2_0))
	  	   {
	    	      card_info.csd.DeviceSize = (tmp & 0x03) << 10;

	    	      /*!< Byte 7 */
	    	      tmp = (uint8_t)(CSD_Tab[1] & 0x000000FF);
	    	      card_info.csd.DeviceSize |= (tmp) << 2;

	    	      /*!< Byte 8 */
	    	      tmp = (uint8_t)((CSD_Tab[2] & 0xFF000000) >> 24);
	    	      card_info.csd.DeviceSize |= (tmp & 0xC0) >> 6;

	    	      card_info.csd.MaxRdCurrentVDDMin = (tmp & 0x38) >> 3;
	    	      card_info.csd.MaxRdCurrentVDDMax = (tmp & 0x07);

	    	      /*!< Byte 9 */
	    	      tmp = (uint8_t)((CSD_Tab[2] & 0x00FF0000) >> 16);
	    	      card_info.csd.MaxWrCurrentVDDMin = (tmp & 0xE0) >> 5;
	    	      card_info.csd.MaxWrCurrentVDDMax = (tmp & 0x1C) >> 2;
	    	      card_info.csd.DeviceSizeMul = (tmp & 0x03) << 1;

	    	      /*!< Byte 10 */
	    	      tmp = (uint8_t)((CSD_Tab[2] & 0x0000FF00) >> 8);
	    	      card_info.csd.DeviceSizeMul |= (tmp & 0x80) >> 7;

	    	      card_info.capacity = (card_info.csd.DeviceSize + 1) ;
	    	      card_info.capacity *= (1 << (card_info.csd.DeviceSizeMul + 2));
	    	      card_info.block_size = 1 << (card_info.csd.RdBlockLen);
	    	      card_info.capacity *= card_info.block_size;
	  	   }
	  	else
	  	   if (card_info.type == card_info_t::high_capacity_std_card)
	  	      {
	    	         /*!< Byte 7 */
	    	         tmp = (uint8_t)(CSD_Tab[1] & 0x000000FF);
	    	         card_info.csd.DeviceSize = (tmp & 0x3F) << 16;

	    	         /*!< Byte 8 */
	    	         tmp = (uint8_t)((CSD_Tab[2] & 0xFF000000) >> 24);

	    	         card_info.csd.DeviceSize |= (tmp << 8);

	    	         /*!< Byte 9 */
	    	         tmp = (uint8_t)((CSD_Tab[2] & 0x00FF0000) >> 16);

	    	         card_info.csd.DeviceSize |= (tmp);

	    	         /*!< Byte 10 */
	    	         tmp = (uint8_t)((CSD_Tab[2] & 0x0000FF00) >> 8);

	    	         card_info.capacity = ((uint64_t)card_info.csd.DeviceSize + 1) * 512 * 1024;
	    	         card_info.block_size = 512;
	  	       }


	  	card_info.csd.EraseGrSize = (tmp & 0x40) >> 6;
	  	card_info.csd.EraseGrMul = (tmp & 0x3F) << 1;

	  	/*!< Byte 11 */
	  	tmp = (uint8_t)(CSD_Tab[2] & 0x000000FF);
	  	card_info.csd.EraseGrMul |= (tmp & 0x80) >> 7;
	  	card_info.csd.WrProtectGrSize = (tmp & 0x7F);

	  	/*!< Byte 12 */
	  	tmp = (uint8_t)((CSD_Tab[3] & 0xFF000000) >> 24);
	  	card_info.csd.WrProtectGrEnable = (tmp & 0x80) >> 7;
	  	card_info.csd.ManDeflECC = (tmp & 0x60) >> 5;
	  	card_info.csd.WrSpeedFact = (tmp & 0x1C) >> 2;
	  	card_info.csd.MaxWrBlockLen = (tmp & 0x03) << 2;

	  	/*!< Byte 13 */
	  	tmp = (uint8_t)((CSD_Tab[3] & 0x00FF0000) >> 16);
	  	card_info.csd.MaxWrBlockLen |= (tmp & 0xC0) >> 6;
	  	card_info.csd.WriteBlockPaPartial = (tmp & 0x20) >> 5;
	  	card_info.csd.Reserved3 = 0;
	  	card_info.csd.ContentProtectAppli = (tmp & 0x01);

	  	/*!< Byte 14 */
	  	tmp = (uint8_t)((CSD_Tab[3] & 0x0000FF00) >> 8);
	  	card_info.csd.FileFormatGrouop = (tmp & 0x80) >> 7;
	  	card_info.csd.CopyFlag = (tmp & 0x40) >> 6;
	  	card_info.csd.PermWrProtect = (tmp & 0x20) >> 5;
	  	card_info.csd.TempWrProtect = (tmp & 0x10) >> 4;
	  	card_info.csd.FileFormat = (tmp & 0x0C) >> 2;
	  	card_info.csd.ECC = (tmp & 0x03);

	  	/*!< Byte 15 */
	  	tmp = (uint8_t)(CSD_Tab[3] & 0x000000FF);
	  	card_info.csd.CSD_CRC = (tmp & 0xFE) >> 1;
	  	card_info.csd.Reserved4 = 1;

	  	/*!< Byte 0 */
	  	tmp = (uint8_t)((CID_Tab[0] & 0xFF000000) >> 24);
	  	card_info.cid.manufacturer_id = tmp;

	  	/*!< Byte 1 */
	  	tmp = (uint8_t)((CID_Tab[0] & 0x00FF0000) >> 16);
	  	card_info.cid.orem_app_id = tmp << 8;

	  	/*!< Byte 2 */
	  	tmp = (uint8_t)((CID_Tab[0] & 0x000000FF00) >> 8);
	  	card_info.cid.orem_app_id |= tmp;

	  	/*!< Byte 3 */
	  	tmp = (uint8_t)(CID_Tab[0] & 0x000000FF);
	  	card_info.cid.product_name_1 = tmp << 24;

	  	/*!< Byte 4 */
	  	tmp = (uint8_t)((CID_Tab[1] & 0xFF000000) >> 24);
	  	card_info.cid.product_name_1 |= tmp << 16;

	  	/*!< Byte 5 */
	  	tmp = (uint8_t)((CID_Tab[1] & 0x00FF0000) >> 16);
	  	card_info.cid.product_name_1 |= tmp << 8;

	  	/*!< Byte 6 */
	  	tmp = (uint8_t)((CID_Tab[1] & 0x0000FF00) >> 8);
	  	card_info.cid.product_name_1 |= tmp;

	  	/*!< Byte 7 */
	  	tmp = (uint8_t)(CID_Tab[1] & 0x000000FF);
	  	card_info.cid.product_name_2 = tmp;

	  	/*!< Byte 8 */
	  	tmp = (uint8_t)((CID_Tab[2] & 0xFF000000) >> 24);
	  	card_info.cid.product_revision = tmp;

	  	/*!< Byte 9 */
	  	tmp = (uint8_t)((CID_Tab[2] & 0x00FF0000) >> 16);
	  	card_info.cid.product_serial_number = tmp << 24;

	  	/*!< Byte 10 */
	  	tmp = (uint8_t)((CID_Tab[2] & 0x0000FF00) >> 8);
	  	card_info.cid.product_serial_number |= tmp << 16;

	  	/*!< Byte 11 */
	  	tmp = (uint8_t)(CID_Tab[2] & 0x000000FF);
	  	card_info.cid.product_serial_number |= tmp << 8;

	  	/*!< Byte 12 */
	  	tmp = (uint8_t)((CID_Tab[3] & 0xFF000000) >> 24);
	  	card_info.cid.product_serial_number |= tmp;

	  	/*!< Byte 13 */
	  	tmp = (uint8_t)((CID_Tab[3] & 0x00FF0000) >> 16);
	  	card_info.cid.reserve_1 |= (tmp & 0xF0) >> 4;
	  	card_info.cid.manufactured_date = (tmp & 0x0F) << 8;

	  	/*!< Byte 14 */
	  	tmp = (uint8_t)((CID_Tab[3] & 0x0000FF00) >> 8);
	  	card_info.cid.manufactured_date |= tmp;

	  	/*!< Byte 15 */
	  	tmp = (uint8_t)(CID_Tab[3] & 0x000000FF);
	  	card_info.cid.cid_crc = (tmp & 0xFE) >> 1;
	  	card_info.cid.reserve_2 = 1;
	  	//-----------------------------------------------

	  	result = SD_OK;
	}

	inline void select_deselect()
	{
	  	sdio.send_command(cmd_select_deselect, card_info.rca << 16 );
	  	cmd_R1_error(cmd_select_deselect.index);
	}

	inline void enable_wide_bus_operation(sdio_t::clock_control_t::bus_wide_t::enum_t mode)
	{
	        result = SD_OK;

	  	if (card_info.type == card_info_t::multimedia_card )
	  	   {
	    	      result = SD_UNSUPPORTED_FEATURE;
	    	      return;
	  	   }

	  	else
	  	   if ((card_info.type == card_info_t::std_capacity_sd_card_v1_1) ||
	               (card_info.type == card_info_t::std_capacity_sd_card_v2_0) ||
		       (card_info.type == card_info_t::high_capacity_std_card))
	  	      {
	  		 switch(mode)
	  		   {
	  		      case sdio_t::clock_control_t::bus_wide_t::enum_t::wide8 :
	  			 result = SD_UNSUPPORTED_FEATURE;
	      			 return;

	      		      case sdio_t::clock_control_t::bus_wide_t::enum_t::wide4:
	      			 wide_bus(true);
	      			 if (result == SD_OK)
	      			    {

	      			       sdio.clock_control.modify( (sdio_t::clock_control_t::clk_divider_t::enum_t)TRANSFER_DIVIDER,
	      							   sdio_t::clock_control_t::power_saving_t::enum_t::disable,
	      							   sdio_t::clock_control_t::clock_divider_bypass_t::enum_t::disable,
	      							   sdio_t::clock_control_t::bus_wide_t::enum_t::wide4,
	      							   sdio_t::clock_control_t::ck_polarity_t::enum_t::rising,
	      							   sdio_t::clock_control_t::flow_control_t::enum_t::disable) ;

	      			    }
	        		  break;

	        	      case sdio_t::clock_control_t::bus_wide_t::enum_t::wide1:
	        	      default:
	        		  wide_bus(false);
	        		  if (result == SD_OK)
	        		     {
	      			  	sdio.clock_control.modify( (sdio_t::clock_control_t::clk_divider_t::enum_t)TRANSFER_DIVIDER,
	      							    sdio_t::clock_control_t::power_saving_t::enum_t::disable,
	      							    sdio_t::clock_control_t::clock_divider_bypass_t::enum_t::disable,
	      							    sdio_t::clock_control_t::bus_wide_t::enum_t::wide1,
	      							    sdio_t::clock_control_t::ck_polarity_t::enum_t::rising,
	      							    sdio_t::clock_control_t::flow_control_t::enum_t::disable) ;
	        		     }
	        		   break;
	  		      }
	               }
	}

	inline void stop_transfer(void)
	{
	        result = SD_OK;
	  	sdio.send_command(cmd_stop_transmission, 0 );
	  	cmd_R1_error(cmd_stop_transmission.index);
	}

	inline void send_sd_status(uint32_t *sd_status)
	{
	        result = SD_OK;
	  	uint32_t count = 0;

	  	if (sdio.response_1 & SD_CARD_LOCKED)
	  	   {
	    	      result = SD_LOCK_UNLOCK_FAILED;
	    	      return;
	  	   }

	  	sdio.send_command(cmd_set_block_len, 64 );
	  	cmd_R1_error(cmd_set_block_len.index);

	  	if (result != SD_OK) return;

	  	sdio.send_command(cmd_app_cmd, card_info.rca << 16 );
	  	cmd_R1_error(cmd_app_cmd.index);

	  	if (result != SD_OK) return;

		sdio.data_timer = SD_DATATIMEOUT;
		sdio.data_length = 64;
		sdio.data_control.modify( sdio_t::data_control_t::transfer_t::enable,
                                          sdio_t::data_control_t::direction_t::card_to_controller,
                                          sdio_t::data_control_t::transfer_mode_t::block,
                                          sdio_t::data_control_t::block_size_t::bytes64 );

	  	sdio.send_command(cmd_sd_app_status, 0 );
	  	cmd_R1_error(cmd_sd_app_status.index);

	  	if (result != SD_OK) return;

	        while (!sdio.rx_fifo_overrun_error() &&
	  	       !sdio.data_block_crc_failed() &&
	  	       !sdio.data_timeout() &&
	  	       !sdio.data_block_end() &&
	  	       !sdio.start_bit_not_detected())
	  	   {
	    	      if (sdio.rx_fifo_half_full())
	    	         {
	      		    for (count = 0; count < 8; count++)
	      		       {
	        		  *(sd_status++) = sdio.fifo;
	      		       }
	    	         }
	  	   }

	  	if (sdio.data_timeout())
	  	   {
	  	      sdio.data_timeout();
	    	      result = SD_DATA_TIMEOUT;
	    	      return;
	  	   }
	  	else
	  	   if (sdio.data_block_crc_failed())
	  	      {
	  	         sdio.data_block_crc_failed_clear();
	    	         result = SD_DATA_CRC_FAIL;
	    	         return;
	  	      }
	  	   else
	  	      if (sdio.rx_fifo_overrun_error())
	  	         {
	  		    sdio.rx_fifo_overrun_error_clear();
	    	            result = SD_RX_OVERRUN;
	    	            return;
	  	         }
	              else
	        	 if (sdio.start_bit_not_detected())
	        	    {
	        	       sdio.start_bit_not_detected_clear();
	        	       result = SD_START_BIT_ERR;
	        	       return;
	        	    }

	  	count = SD_DATATIMEOUT;
	  	while (sdio.data_available_in_rx_fifo() && (count > 0))
	  	   {
	  	       *(sd_status++) = sdio.fifo;
	    	       count--;
	  	   }

	  	sdio.static_flags_clear();
	}

	inline void send_status(uint32_t *pcardstatus)
	{
	        result = SD_OK;

		if (pcardstatus == NULL)
		   {
	              result = SD_INVALID_PARAMETER;
	              return;
		   }

	  	sdio.send_command(cmd_send_status, card_info.rca << 16 );
	  	cmd_R1_error(cmd_send_status.index);

		if (result != SD_OK) return;

		*pcardstatus = sdio.response_1;
	}

	inline state_t get_state()
	{
	  if(detect()== present)
	     {
	       uint32_t resp1 = 0;
	       send_status(&resp1) ;
	       if ( result != SD_OK) return card_error;
	       else                  return (state_t)((resp1 >> 9) & 0x0F);
	     }

	  return card_error;
	}

	inline void cmd_error(void)
	{
	        result = SD_OK;
		uint32_t timeout;

	  	timeout = SDIO_CMD0TIMEOUT; /*!< 10000 */

	  	while ((timeout > 0) && !sdio.command_sent())
	  	   {
	    	      timeout--;
	  	   }

	  	if (timeout == 0)
	  	   {
	    	      result = SD_CMD_RSP_TIMEOUT;
	    	      return;
	  	   }

	  	sdio.static_flags_clear();
	}

	inline void cmd_R1_error(uint8_t cmd)
	{
	        result = SD_OK;
	  	uint32_t response_r1;

	  	while (!sdio.command_response_crc_failed() &&
		       !sdio.command_response_received() &&
		       !sdio.command_response_timeout());

	  	if (sdio.command_response_timeout())
	  	   {
	    	      result = SD_CMD_RSP_TIMEOUT;
	    	      sdio.command_response_timeout_clear();
	    	      return;
	  	   }
	  	else
	  	   if (sdio.command_response_crc_failed())
	  	      {
	    	         result = SD_CMD_CRC_FAIL;
	    	         sdio.command_response_crc_failed_clear();
	    	         return;
	  	      }

	  	if (sdio.command_response != cmd)
	  	   {
	    	      result = SD_ILLEGAL_CMD;
	    	      return;
	  	   }

	  	sdio.static_flags_clear();

	  	response_r1 = sdio.response_1;

	  	if ((response_r1 & SD_OCR_ERRORBITS) == SD_ALLZERO) return;
	  	if (response_r1 & SD_OCR_ADDR_OUT_OF_RANGE)  { result=SD_ADDR_OUT_OF_RANGE ; return;}
		if (response_r1 & SD_OCR_ADDR_MISALIGNED) { result=SD_ADDR_MISALIGNED ; return;}
	        if (response_r1 & SD_OCR_BLOCK_LEN_ERR)  { result=SD_BLOCK_LEN_ERR ; return;}
	        if (response_r1 & SD_OCR_ERASE_SEQ_ERR)  { result=SD_ERASE_SEQ_ERR ; return;}
	        if (response_r1 & SD_OCR_BAD_ERASE_PARAM) { result=SD_BAD_ERASE_PARAM ; return;}
	  	if (response_r1 & SD_OCR_WRITE_PROT_VIOLATION ){ result=SD_WRITE_PROT_VIOLATION ; return;}
	  	if (response_r1 & SD_OCR_LOCK_UNLOCK_FAILED) { result=SD_LOCK_UNLOCK_FAILED ; return;}
	  	if (response_r1 & SD_OCR_COM_CRC_FAILED) { result=SD_COM_CRC_FAILED ; return;}
	  	if (response_r1 & SD_OCR_ILLEGAL_CMD) { result=SD_ILLEGAL_CMD ; return;}
	  	if (response_r1 & SD_OCR_CARD_ECC_FAILED) { result=SD_CARD_ECC_FAILED ; return;}
	  	if (response_r1 & SD_OCR_CC_ERROR) { result=SD_CC_ERROR ; return;}
	  	if (response_r1 & SD_OCR_GENERAL_UNKNOWN_ERROR){ result=SD_GENERAL_UNKNOWN_ERROR ; return;}
	   	if (response_r1 & SD_OCR_STREAM_READ_UNDERRUN){ result=SD_STREAM_READ_UNDERRUN ; return;}
	  	if (response_r1 & SD_OCR_STREAM_WRITE_OVERRUN){ result=SD_STREAM_WRITE_OVERRUN ; return;}
	  	if (response_r1 & SD_OCR_CID_CSD_OVERWRIETE){ result=SD_CID_CSD_OVERWRITE ; return;}
	  	if (response_r1 & SD_OCR_CARD_ECC_DISABLED){ result=SD_CARD_ECC_DISABLED ; return;}
	  	if (response_r1 & SD_OCR_ERASE_RESET){ result=SD_ERASE_RESET ; return;}
	  	if (response_r1 & SD_OCR_AKE_SEQ_ERROR){ result=SD_AKE_SEQ_ERROR ; return; }
	}

	inline void cmd_R7_error()
	{
	        result = SD_OK;
	  	uint32_t timeout = SDIO_CMD0TIMEOUT;

	  	while (!sdio.command_response_crc_failed() &&
		       !sdio.command_response_received() &&
		       !sdio.command_response_timeout() &&
	  		   (timeout > 0))

	  	   {
	    	      timeout--;
	  	   }

	  	if ((timeout == 0) || sdio.command_response_timeout())
	  	   {
	    	      result = SD_CMD_RSP_TIMEOUT;
	    	      sdio.command_response_timeout_clear();
	    	      return;
	  	   }

	  	if (sdio.command_response_received())
	  	   {
	    	      result = SD_OK;
	    	      sdio.command_response_received_clear();
	    	      return;
	  	   }
	}

	inline void cmd_R3_error(void)
	{
	       result = SD_OK;

	  	while (!sdio.command_response_crc_failed() &&
		       !sdio.command_response_received() &&
		       !sdio.command_response_timeout());

	  	if (sdio.command_response_timeout())
	 	   {
	    	      result = SD_CMD_RSP_TIMEOUT;
	    	      sdio.command_response_timeout_clear();
	    	      return;
	  	   }

	  	sdio.static_flags_clear();
	}

	inline void cmd_R2_error(void)
	{
	       result = SD_OK;

	  	while (!sdio.command_response_crc_failed() &&
		       !sdio.command_response_received() &&
		       !sdio.command_response_timeout());

	  	if (sdio.command_response_timeout())
	  	   {
	    	      result = SD_CMD_RSP_TIMEOUT;
	    	      sdio.command_response_timeout_clear();
	    	      return;
	  	   }
	  	else
	  	  if (sdio.command_response_crc_failed())
	  	     {
	    	        result = SD_CMD_CRC_FAIL;
	    	        sdio.command_response_crc_failed_clear();
	    	        return;
	  	     }

	  	sdio.static_flags_clear();
	  	return;
	}

	inline void cmd_R6_error(uint8_t cmd, uint16_t *rca)
	{
	        result = SD_OK;
	  	uint32_t response_r1;

	  	while (!sdio.command_response_crc_failed() &&
		       !sdio.command_response_received() &&
		       !sdio.command_response_timeout());


	  	if (sdio.command_response_timeout())
	  	   {
	    	      result = SD_CMD_RSP_TIMEOUT;
	    	      sdio.command_response_timeout_clear();
	    	      return;
	  	   }
	  	else
	  	   if (sdio.command_response_crc_failed())
	  	      {
	    	         result = SD_CMD_CRC_FAIL;
	    	         sdio.command_response_crc_failed_clear();
	    	         return;
	  	      }

	  	if (sdio.command_response != cmd)
	  	   {
	    	      result = SD_ILLEGAL_CMD;
	    	      return;
	  	   }

	  	sdio.static_flags_clear();

	  	response_r1 = sdio.response_1;

	  	if (SD_ALLZERO == (response_r1 & (SD_R6_GENERAL_UNKNOWN_ERROR | SD_R6_ILLEGAL_CMD | SD_R6_COM_CRC_FAILED)))
	  	   {
	    	      *rca = (uint16_t) (response_r1 >> 16);
	    	      return;
	  	   }

	  	if (response_r1 & SD_R6_GENERAL_UNKNOWN_ERROR)
	  	   {
	  	      result = SD_GENERAL_UNKNOWN_ERROR ; return;
	  	   }

	  	if (response_r1 & SD_R6_ILLEGAL_CMD)
	  	   {
	  	      result = SD_ILLEGAL_CMD ; return;
	  	   }

	  	if (response_r1 & SD_R6_COM_CRC_FAILED)
	  	   {
	    	      result = SD_COM_CRC_FAILED ; return;
	  	   }
	}

	inline void wide_bus(bool enable)
	{
	        result = SD_OK;
	  	uint32_t scr[2] = {0, 0};

	  	if (sdio.response_1 & SD_CARD_LOCKED)
	  	   {
	    	      result = SD_LOCK_UNLOCK_FAILED;
	    	      return;
	  	   }

	  	sdio.static_flags_clear();

	  	find_scr(card_info.rca, scr);

	  	if (result != SD_OK) return;

	  	if (enable)
	  	   {
	    	      /*!< If requested card supports wide bus operation */
	    	     if ((scr[1] & SD_WIDE_BUS_SUPPORT) != SD_ALLZERO)
	    	        {
	    	  	   sdio.send_command(cmd_app_cmd, card_info.rca << 16 );
	      		   cmd_R1_error(cmd_app_cmd.index);

	  		   if (result != SD_OK) return;

	    	  	   sdio.send_command(cmd_app_sd_set_buswidth, 0x2 );
	      		   cmd_R1_error(cmd_app_sd_set_buswidth.index);

	      		   if (result != SD_OK) return;

	      		   return;
	    	        }
	             else
	    	        {
	      		   result = SD_REQUEST_NOT_APPLICABLE;
	      		   return;
	    	        }
	  	   }
	 	else
	  	   {
	               /*!< If requested card supports 1 bit mode operation */
		       if ((scr[1] & SD_SINGLE_BUS_SUPPORT) != SD_ALLZERO)
		          {

	    	  	     sdio.send_command(cmd_app_cmd, card_info.rca << 16 );
	      		     cmd_R1_error(cmd_app_cmd.index);

			     if (result != SD_OK)  return;

			     sdio.send_command(cmd_app_sd_set_buswidth, 0 );
	    		     cmd_R1_error(cmd_app_sd_set_buswidth.index);

	    		     if (result != SD_OK)  return;
	                     return;
	    	          }
		       else
	    	          {
	      		     result = SD_REQUEST_NOT_APPLICABLE;
	      		     return;
	    	          }
	  	    }
	}

	inline void is_busy(uint8_t& status)
	{
	        result = SD_OK;
		uint32_t respR1 = 0;
	  	sdio.send_command(cmd_send_status, card_info.rca << 16 );
	  	cmd_R1_error(cmd_send_status.index);
	  	respR1 = sdio.response_1;
	  	status = (uint8_t) ((respR1 >> 9) & 0x0000000F);
	}

	inline void find_scr(uint16_t rca, uint32_t *scr)
	{
		uint32_t index = 0;
		result = SD_OK;
	  	uint32_t tempscr[2] = {0, 0};

	  	sdio.send_command(cmd_set_block_len, 8 );
	  	cmd_R1_error(cmd_set_block_len.index);

	  	if (result != SD_OK) return;

	  	sdio.send_command(cmd_app_cmd, card_info.rca << 16 );
	  	cmd_R1_error(cmd_app_cmd.index);

	  	if (result != SD_OK) return;

		sdio.data_timer = SD_DATATIMEOUT;
		sdio.data_length = 8;
		sdio.data_control.modify( sdio_t::data_control_t::transfer_t::enable,
                                          sdio_t::data_control_t::direction_t::card_to_controller,
                                          sdio_t::data_control_t::transfer_mode_t::block,
                                          sdio_t::data_control_t::block_size_t::bytes8 );

	  	sdio.send_command(cmd_sd_app_send_scr, 0 );
		cmd_R1_error(cmd_sd_app_send_scr.index);

	  	if (result != SD_OK) return;

	   	while ( !sdio.rx_fifo_overrun_error() && !sdio.data_block_crc_failed() &&
		        !sdio.data_timeout() && !sdio.data_block_end() && !sdio.start_bit_not_detected())
	  	   {
	    	      if (sdio.data_available_in_rx_fifo())
	    	         {
	      		    *(tempscr + index) = sdio.fifo;
	      		    index++;
	    	         }
	  	   }

	  	if (sdio.data_timeout())
	  	   {
	  	      sdio.data_timeout_clear();
	    	      result = SD_DATA_TIMEOUT;
	    	      return;
	  	   }
	  	else
	  	   if (sdio.data_block_crc_failed())
	  	      {
	  	         sdio.data_block_crc_failed_clear();
	    	         result = SD_DATA_CRC_FAIL;
	    	         return;
	  	      }
	  	   else
	  	      if (sdio.rx_fifo_overrun_error())
	  	         {
	  		    sdio.rx_fifo_overrun_error_clear();
	    	            result = SD_RX_OVERRUN;
	    	            return;
	  	         }
	  	      else
	  		 if (sdio.start_bit_not_detected())
	  	            {
	  		       sdio.start_bit_not_detected_clear();
	    	               result = SD_START_BIT_ERR;
	    	               return;
	  	            }

	  	sdio.static_flags_clear();

	  	*(scr + 1) = ((tempscr[0] & SD_0TO7BITS) << 24) | ((tempscr[0] & SD_8TO15BITS) << 8) | ((tempscr[0] & SD_16TO23BITS) >> 8) | ((tempscr[0] & SD_24TO31BITS) >> 24);

	  	*(scr) = ((tempscr[1] & SD_0TO7BITS) << 24) | ((tempscr[1] & SD_8TO15BITS) << 8) | ((tempscr[1] & SD_16TO23BITS) >> 8) | ((tempscr[1] & SD_24TO31BITS) >> 24);
	}

	inline result_t wait_read_operation(const bool multiblock_mode)
	{
	        result = SD_OK;
		uint32_t timeout = SD_DATATIMEOUT;

		while ((dma_end_of_xfer == false) && (end_of_xfer == false) && (xfer_error == SD_OK) && (timeout > 0)) timeout--;

		dma_end_of_xfer = false;
		timeout = SD_DATATIMEOUT;

		while( sdio.data_rx_in_progress() && (timeout > 0)) timeout--;

		if (stop_condition == true)
		{
			if (multiblock_mode)
			         stop_transfer();
			stop_condition = false;
		}

		if ((timeout == 0) && (result == SD_OK)) result = SD_DATA_TIMEOUT;

		sdio.static_flags_clear();

		//------  wait transfer complete ------
	  	transfer_state_t transfer_state ;
	  	while ( (transfer_state = get_status()) == transfer_busy ) {}
		if ( transfer_state == transfer_error ) result = SD_ERROR ;
		//-------------------------------------

		if (xfer_error != SD_OK) return xfer_error ;
		else return result ;
	}


	inline result_t wait_write_operation(const bool multiblock_mode)
	{
	        result = SD_OK;
		uint32_t timeout = SD_DATATIMEOUT;

		while ((dma_end_of_xfer == false) && (end_of_xfer == false) && (xfer_error == SD_OK) && (timeout>0)) timeout--;

		dma_end_of_xfer = false;
		timeout = SD_DATATIMEOUT;

		while( sdio.data_tx_in_progress()  && (timeout > 0)) timeout--;

		if (stop_condition == true)
		{
			if (multiblock_mode)
			         stop_transfer();
			stop_condition = false;
		}

		if ((timeout == 0) && (result == SD_OK)) result = SD_DATA_TIMEOUT;

		sdio.static_flags_clear();

		//------  wait transfer complete ------
	  	transfer_state_t transfer_state ;
	  	while ( (transfer_state = get_status()) == transfer_busy ) {}
		if ( transfer_state == transfer_error ) result = SD_ERROR ;
		//-------------------------------------

		if (xfer_error != SD_OK) return xfer_error ;
		else return result ;

	}


	inline void dma_init()
	{
	  dma2_stream3.reset();
	  dma2_stream3.configuration.modify( dma_stream_t::configuration_t::transfer_complete_interrupt_state_t::enable,
	                                     dma_stream_t::configuration_t::flow_controller_t::peripheral,
					     dma_stream_t::configuration_t::peripheral_increment_mode_t::disable,
					     dma_stream_t::configuration_t::memory_increment_mode_t::enable,
					     dma_stream_t::configuration_t::peripheral_data_size_t::word,
					     dma_stream_t::configuration_t::memory_data_size_t::word,
				             dma_stream_t::configuration_t::priority_level_t::very_high,
					     dma_stream_t::configuration_t::peripheral_burst_transfer_t::incr4,
					     dma_stream_t::configuration_t::memory_burst_transfer_t::incr4,
					     stm32f4::dma2_stream3_t::channel_t::sdio
		                           );

	  dma2_stream3.fifo_control.modify( dma_stream_t::fifo_control_t::direct_mode_t::disable,
					    dma_stream_t::fifo_control_t::threshold_selection_t::threshold_selection_full );

	  dma2_stream3.peripheral_address = (uint32_t)&sdio.fifo ;
	}

	inline void dma_rx_config(uint32_t *buffer, size_t blockcount)
	{
	        dma2.low_interrupt_clear.write_or( dma_t::low_interrupt_clear_t::stream3_fifo_error_interrupt_flag_clear_t::clear,
						   dma_t::low_interrupt_clear_t::stream3_direct_mode_error_interrupt_flag_clear_t::clear,
						   dma_t::low_interrupt_clear_t::stream3_transfer_complete_interrupt_flag_clear_t::clear,
						   dma_t::low_interrupt_clear_t::stream3_half_transfer_interrupt_flag_clear_t::clear,
						   dma_t::low_interrupt_clear_t::stream3_transfer_error_interrupt_flag_clear_t::clear
		                                 ) ;

		if ( SD_DMA_MAX_TRANSFER_SIZE / card_info.block_size < blockcount )  { result = SD_UNSUPPORTED_DMA_TRANSFER_SIZE; return; }

		dma2_stream3.memory0_address=(uint32_t)buffer;
		//tx_request = false ;
		dma2_stream3.configuration.modify( dma_stream_t::configuration_t::state_t::enable,
						   dma_stream_t::configuration_t::direction_t::peripheral_to_memory
		                                 );
		result = SD_OK;
	}

	inline void dma_tx_config(uint32_t *buffer, size_t blockcount)
	{
		dma2.low_interrupt_clear.write_or( dma_t::low_interrupt_clear_t::stream3_fifo_error_interrupt_flag_clear_t::clear,
						   dma_t::low_interrupt_clear_t::stream3_direct_mode_error_interrupt_flag_clear_t::clear,
						   dma_t::low_interrupt_clear_t::stream3_transfer_complete_interrupt_flag_clear_t::clear,
						   dma_t::low_interrupt_clear_t::stream3_half_transfer_interrupt_flag_clear_t::clear,
						   dma_t::low_interrupt_clear_t::stream3_transfer_error_interrupt_flag_clear_t::clear
		                                 ) ;

		if ( SD_DMA_MAX_TRANSFER_SIZE / card_info.block_size < blockcount )  { result = SD_UNSUPPORTED_DMA_TRANSFER_SIZE; return; }

		dma2_stream3.memory0_address=(uint32_t)buffer;
		//tx_request = true ;
		dma2_stream3.configuration.modify( dma_stream_t::configuration_t::state_t::enable,
						   dma_stream_t::configuration_t::direction_t::memory_to_peripheral
		                                 );

		result = SD_OK;
	}

 	static constexpr sdio_t::cmd_t cmd_go_idle_state = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_GO_IDLE_STATE,
 	 	                      .response=sdio_t::command_t::wait_for_response_t::short_disable,
 	 	                      .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	                      .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 				      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_send_if_cond = {.index=(sdio_t::command_t::command_index_t::enum_t)SDIO_SEND_IF_COND,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 			      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_app_cmd = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_APP_CMD,
 	 	 	 	      .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	 	      .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	 	      .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_sd_app_op_cond = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_SD_APP_OP_COND,
 	 	 	 	      .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	 	      .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	 	      .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_all_send_cid = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_ALL_SEND_CID,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::long_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_set_rel_addr = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_SET_REL_ADDR,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_send_csd = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_SEND_CSD,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::long_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 	              .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_select_deselect = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_SEL_DESEL_CARD,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_stop_transmission = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_STOP_TRANSMISSION,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_set_block_len = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_SET_BLOCKLEN,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_sd_app_status = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_SD_APP_STAUS,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_send_status = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_SEND_STATUS,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_app_sd_set_buswidth = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_APP_SD_SET_BUSWIDTH,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_sd_app_send_scr = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_SD_APP_SEND_SCR,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	  	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	  	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_erase = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_ERASE,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_sd_erase_grp_end = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_SD_ERASE_GRP_END,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_sd_erase_grp_start = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_SD_ERASE_GRP_START,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_read_mult_block = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_READ_MULT_BLOCK,
 	 	 	 	      .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	 	      .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_write_mult_block = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_WRITE_MULT_BLOCK,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_set_block_count = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_SET_BLOCK_COUNT,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 	              .cpsm = sdio_t::command_t::cpsm_t::enable} ;



 	static constexpr sdio_t::cmd_t cmd_read_single_block = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_READ_SINGLE_BLOCK,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 		      .cpsm = sdio_t::command_t::cpsm_t::enable} ;

 	static constexpr sdio_t::cmd_t cmd_write_single_block = {.index=(sdio_t::command_t::command_index_t::enum_t)SD_CMD_WRITE_SINGLE_BLOCK,
 	 	 	              .response=sdio_t::command_t::wait_for_response_t::short_enable,
 	 	 	              .waits_for_interrupt=sdio_t::command_t::cpsm_waits_for_interrupt_t::disable ,
 	 	 	              .wait_for_ends=sdio_t::command_t::cpsm_waits_for_ends_of_data_transfer_t::disable,
 	 	 	 	      .cpsm = sdio_t::command_t::cpsm_t::enable} ;


};



#endif /* __SDCARD_H__ */
