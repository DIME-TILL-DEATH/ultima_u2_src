#ifndef __ADF4351_H__
#define __ADF4351_H__

#include <stdint.h>

/* Registers */
#define ADF4351_REG0	0
#define ADF4351_REG1	1
#define ADF4351_REG2	2
#define ADF4351_REG3	3
#define ADF4351_REG4	4
#define ADF4351_REG5	5

/* REG0 Bit Definitions */
#define ADF4351_REG0_FRACT(x)			(((x) & 0xFFF) << 3)
#define ADF4351_REG0_INT(x)			(((x) & 0xFFFF) << 15)

/* REG1 Bit Definitions */
#define ADF4351_REG1_MOD(x)			(((x) & 0xFFF) << 3)
#define ADF4351_REG1_PHASE(x)			(((x) & 0xFFF) << 15)
#define ADF4351_REG1_PRESCALER			(1 << 27)
#define ADF4351_REG1_PHA_ADJ                    (1 << 28)

/* REG2 Bit Definitions */
#define ADF4351_REG2_COUNTER_RESET_EN		(1 << 3)
#define ADF4351_REG2_CP_THREESTATE_EN		(1 << 4)
#define ADF4351_REG2_POWER_DOWN_EN		(1 << 5)
#define ADF4351_REG2_PD_POLARITY_POS		(1 << 6)
#define ADF4351_REG2_LDP_6ns			(1 << 7)
#define ADF4351_REG2_LDP_10ns			(0 << 7)
#define ADF4351_REG2_LDF_FRACT_N		(0 << 8)
#define ADF4351_REG2_LDF_INT_N			(1 << 8)
#define ADF4351_REG2_CHARGE_PUMP_CURR_uA(x)	(((((x)-312) / 312) & 0xF) << 9)
#define ADF4351_REG2_DOUBLE_BUFF_EN		(1 << 13)
#define ADF4351_REG2_10BIT_R_CNT(x)		((x) << 14)
#define ADF4351_REG2_RDIV2_EN			(1 << 24)
#define ADF4351_REG2_RMULT2_EN			(1 << 25)
#define ADF4351_REG2_MUXOUT(x)			((x) << 26)
#define ADF4351_REG2_NOISE_MODE(x)		((x) << 29)

/* REG3 Bit Definitions */
#define ADF4351_REG3_12BIT_CLKDIV(x)		((x) << 3)
#define ADF4351_REG3_12BIT_CLKDIV_MODE(x)	((x) << 16)
#define ADF4351_REG3_12BIT_CSR_EN		(1 << 18)
#define ADF4351_REG3_CHARGE_CANCELLATION_EN	(1 << 21)
#define ADF4351_REG3_ANTI_BACKLASH_3ns_EN	(1 << 22)
#define ADF4351_REG3_BAND_SEL_CLOCK_MODE_HIGH	(1 << 23)

/* REG4 Bit Definitions */
#define ADF4351_REG4_OUTPUT_PWR(x)		((x) << 3)
#define ADF4351_REG4_RF_OUT_EN			(1 << 5)
#define ADF4351_REG4_AUX_OUTPUT_PWR(x)		((x) << 6)
#define ADF4351_REG4_AUX_OUTPUT_EN		(1 << 8)
#define ADF4351_REG4_AUX_OUTPUT_FUND		(1 << 9)
#define ADF4351_REG4_AUX_OUTPUT_DIV		(0 << 9)
#define ADF4351_REG4_MUTE_TILL_LOCK_EN		(1 << 10)
#define ADF4351_REG4_VCO_PWRDOWN_EN		(1 << 11)
#define ADF4351_REG4_8BIT_BAND_SEL_CLKDIV(x)	((x) << 12)
#define ADF4351_REG4_RF_DIV_SEL(x)		((x) << 20)
#define ADF4351_REG4_FEEDBACK_DIVIDED		(0 << 23)
#define ADF4351_REG4_FEEDBACK_FUND		(1 << 23)

/* REG5 Bit Definitions */
#define ADF4351_REG5_LD_PIN_MODE_LOW		(0 << 22)
#define ADF4351_REG5_LD_PIN_MODE_DIGITAL	(1 << 22)
#define ADF4351_REG5_LD_PIN_MODE_HIGH		(3 << 22)

class adf4351
{
  /* Specifications */
  const uint64_t  ADF4351_MAX_OUT_FREQ         =  4400000000ULL ; /* Hz */
  const uint64_t  ADF4351_MIN_OUT_FREQ         =	34375000 ; /* Hz */
  const uint64_t  ADF4351_MIN_VCO_FREQ         =	2200000000ULL ; /* Hz */
  const uint64_t  ADF4351_MAX_FREQ_45_PRESC    =	3000000000ULL ; /* Hz */
  const uint64_t  ADF4351_MAX_FREQ_PFD         =	32000000 ; /* Hz */
  const uint64_t  ADF4351_MAX_BANDSEL_CLK      =	125000 ; /* Hz */
  const uint64_t  ADF4351_MAX_FREQ_REFIN       =	250000000 ; /* Hz */
  const uint64_t  ADF4351_MAX_MODULUS          =	4095 ;
  const uint64_t  ADF4351_MAX_R_CNT            =	1023 ;


  typedef struct
  {
  	uint32_t	clkin;
  	uint32_t	channel_spacing;
  	uint64_t	power_up_frequency;

  	uint16_t	ref_div_factor; /* 10-bit R counter */
  	uint8_t	        ref_doubler_en;
  	uint8_t	        ref_div2_en;

  	uint32_t        r2_user_settings;
  	uint32_t        r3_user_settings;
  	uint32_t        r4_user_settings;
  } adf4351_platform_data_t ;


  typedef struct
  {
  	adf4351_platform_data_t	data;
  	uint32_t	clkin;
  	uint32_t	chspc;	/* Channel Spacing */
  	uint32_t	fpfd;	/* Phase Frequency Detector */
  	uint32_t	min_out_freq;
  	uint32_t	r0_fract;
  	uint32_t	r0_int;
  	uint32_t	r1_mod;
  	uint32_t	r4_rf_div_sel;
  	uint32_t	regs[6];
  	uint32_t	regs_hw[6];
  	uint32_t 	val;
  }adf4351_st_t;



   public:
      typedef void (*init_fn_t) () ;               // init hw interface (spi,gpio, etc...)
      typedef void (*write_fn_t) (uint32_t val) ;  // write  reg (32 bit series)
      typedef bool (*lock_detect_fn_t) () ;        // read lock detect pin
      typedef bool (*muxout_fn_t) () ;             // read mux out pin

      typedef struct
      {
         init_fn_t        init ;
         write_fn_t       write ;
         lock_detect_fn_t lock_detect ;
         muxout_fn_t      muxout ;
       } io_t ;


      /** Initializes the ADF4351. */
      adf4351( const io_t& _io ) : io(_io)
         {
	    io.init();

	    st.data.clkin = 25000000 ;
	    st.data.channel_spacing = 10000 ;
	    st.data.power_up_frequency = 0 ;
	    st.data.ref_div_factor = 100 ;
	    st.data.ref_div2_en = 0 ;
	    st.data.ref_doubler_en = 0 ;
	    st.data.r2_user_settings = ADF4351_REG2_PD_POLARITY_POS | ADF4351_REG2_CHARGE_PUMP_CURR_uA(2500);
	    st.data.r3_user_settings = ADF4351_REG3_12BIT_CLKDIV_MODE(0);
	    st.data.r4_user_settings = ADF4351_REG4_OUTPUT_PWR(3)   | ADF4351_REG4_MUTE_TILL_LOCK_EN ;

	    setup();
         }

      int32_t frequency_resolution(int32_t Hz)    /** Stores PLL 0 frequency resolution/channel spacing in Hz. */
            {
            	if(Hz != INT32_MAX)
            	{
            		st.chspc = Hz;
            	}
            	return st.chspc;
            }

      int64_t refin_frequency(int64_t Hz)  /** Sets PLL 0 REFin frequency in Hz. */
            {
            	if(Hz < ADF4351_MAX_FREQ_REFIN)
            	{
            		st.clkin = (uint32_t)Hz;
            	}

            	return st.clkin;
            }


       int32_t powerdown(bool pwd)  /** Powers down the PLL.  */
            {
            	if(pwd)
            	{
            	   st.regs[ADF4351_REG2] |= ADF4351_REG2_POWER_DOWN_EN;
            	   sync_config();
            	}
            	else
            	{
            	   st.regs[ADF4351_REG2] &= ~ADF4351_REG2_POWER_DOWN_EN;
            	   sync_config();
            	}
            	return (st.regs[ADF4351_REG2] & ADF4351_REG2_POWER_DOWN_EN);
            }


            inline int64_t frequency()
            {
              uint64_t tmp = (uint64_t)((st.r0_int * st.r1_mod) + st.r0_fract) * (uint64_t)st.fpfd;
              tmp = tmp / ((uint64_t)st.r1_mod * ((uint64_t)1 << st.r4_rf_div_sel));
      	      return tmp;
            }

            /** Stores PLL 0 frequency in Hz. */
                  int64_t frequency(uint64_t freq)
                  {
                  	uint64_t tmp;
                  	uint32_t div_gcd, prescaler, chspc;
                  	uint16_t mdiv, r_cnt = 0;
                  	uint8_t band_sel_div;

                  	if ((freq > ADF4351_MAX_OUT_FREQ) || (freq < ADF4351_MIN_OUT_FREQ))
                  		return 0;

                  	st.r4_rf_div_sel = 0;

                  	while (freq < ADF4351_MIN_VCO_FREQ) {
                  		freq <<= 1;
                  		st.r4_rf_div_sel++;
                  	}

                  	if (freq > ADF4351_MAX_FREQ_45_PRESC) {
                  		prescaler = ADF4351_REG1_PRESCALER;
                  		mdiv = 75;
                  	} else {
                  		prescaler = 0;
                  		mdiv = 23;
                  	}

                  	/*
                  	 * Allow a predefined reference division factor
                  	 * if not set, compute our own
                  	 */
                  	if (st.data.ref_div_factor)
                  		r_cnt = st.data.ref_div_factor - 1;

                  	chspc = st.chspc;

                  	do  {
                  	      do {
                  	             do  {

                  		r_cnt = tune_r_cnt(r_cnt);
                  				st.r1_mod = st.fpfd / chspc;
                  				if (r_cnt > ADF4351_MAX_R_CNT) {
                  					/* try higher spacing values */
                  					chspc++;
                  					r_cnt = 0;
                  		}
                  			} while ((st.r1_mod > ADF4351_MAX_MODULUS) && r_cnt);
                  		} while (r_cnt == 0);


                  		tmp = freq * (uint64_t)st.r1_mod + (st.fpfd > 1); // ????

                  		tmp = (tmp  + st.fpfd/2) / st.fpfd ;	/* Div round closest (n + d/2)/d */

                  		st.r0_fract = tmp % st.r1_mod;
                  		tmp = tmp / st.r1_mod;

                  		st.r0_int = (uint32_t)tmp;
                  	} while (mdiv > st.r0_int);

                  	band_sel_div = (((st.fpfd) + (ADF4351_MAX_BANDSEL_CLK) - 1) / (ADF4351_MAX_BANDSEL_CLK));	// DIV_ROUND_UP

                  	if (st.fpfd == ADF4351_MAX_FREQ_PFD)
                  		band_sel_div = 255;

                  	if (st.r0_fract && st.r1_mod)
                  	  {
                  		div_gcd = gcd(st.r1_mod, st.r0_fract);
                  		st.r1_mod /= div_gcd;
                  		st.r0_fract /= div_gcd;
                  	  }
                  	else
                  	  {
                  		st.r0_fract = 0;
                  		st.r1_mod = 1;
                  	  }

                  	st.regs[ADF4351_REG0] = ADF4351_REG0_INT(st.r0_int) |
                  				 ADF4351_REG0_FRACT(st.r0_fract);

                  	st.regs[ADF4351_REG1] = ADF4351_REG1_PHASE(1) |
                  				 ADF4351_REG1_MOD(st.r1_mod) |
                  				 prescaler;

                  	st.regs[ADF4351_REG2] =
                  		ADF4351_REG2_10BIT_R_CNT(r_cnt) |
                  		ADF4351_REG2_DOUBLE_BUFF_EN |
                  		(st.data.ref_doubler_en ? ADF4351_REG2_RMULT2_EN : 0) |
                  		(st.data.ref_div2_en ? ADF4351_REG2_RDIV2_EN : 0) |
                  		(st.data.r2_user_settings & (ADF4351_REG2_PD_POLARITY_POS |
                  		ADF4351_REG2_LDP_6ns | ADF4351_REG2_LDF_INT_N |
                  		ADF4351_REG2_CHARGE_PUMP_CURR_uA(5000) |
                  		ADF4351_REG2_MUXOUT(0x7) | ADF4351_REG2_NOISE_MODE(0x3)));

                  	st.regs[ADF4351_REG3] = st.data.r3_user_settings &
                  				 (ADF4351_REG3_12BIT_CLKDIV(0xFFF) |
                  				 ADF4351_REG3_12BIT_CLKDIV_MODE(0x3) |
                  				 ADF4351_REG3_12BIT_CSR_EN |
                  				 ADF4351_REG3_CHARGE_CANCELLATION_EN |
                  				 ADF4351_REG3_ANTI_BACKLASH_3ns_EN |
                  				 ADF4351_REG3_BAND_SEL_CLOCK_MODE_HIGH);

                  	st.regs[ADF4351_REG4] =
                  		ADF4351_REG4_FEEDBACK_FUND |
                  		ADF4351_REG4_RF_DIV_SEL(st.r4_rf_div_sel) |
                  		ADF4351_REG4_8BIT_BAND_SEL_CLKDIV(band_sel_div) |
                  		ADF4351_REG4_RF_OUT_EN |
                  		(st.data.r4_user_settings &
                  		(ADF4351_REG4_OUTPUT_PWR(0x3) |
                  		ADF4351_REG4_AUX_OUTPUT_PWR(0x3) |
                  		ADF4351_REG4_AUX_OUTPUT_EN |
                  		ADF4351_REG4_AUX_OUTPUT_FUND |
                  		ADF4351_REG4_MUTE_TILL_LOCK_EN));

                  	st.regs[ADF4351_REG5] = ADF4351_REG5_LD_PIN_MODE_DIGITAL + 0x00180000;

                  	sync_config();

                  	return frequency() ;
                  }


   protected:
      void setup()
      {
      	refin_frequency(st.data.clkin);
      	frequency_resolution(st.data.channel_spacing);

      	st.regs[ADF4351_REG5] = ADF4351_REG5_LD_PIN_MODE_DIGITAL + 0x00180000;
      	st.regs[ADF4351_REG4] = ADF4351_REG4_FEEDBACK_FUND + ADF4351_REG4_8BIT_BAND_SEL_CLKDIV(246) + ADF4351_REG4_RF_OUT_EN + ADF4351_REG4_OUTPUT_PWR(3);
      	st.regs[ADF4351_REG3] = ADF4351_REG3_12BIT_CLKDIV(150);
      	st.regs[ADF4351_REG2] = ADF4351_REG2_10BIT_R_CNT(4) + ADF4351_REG2_CHARGE_PUMP_CURR_uA(2496) + ADF4351_REG2_PD_POLARITY_POS + ADF4351_REG2_POWER_DOWN_EN;
      	st.regs[ADF4351_REG1] = ADF4351_REG1_PRESCALER + ADF4351_REG1_MOD(307);
      	st.regs[ADF4351_REG0] = ADF4351_REG0_FRACT(39) + ADF4351_REG0_INT(78);

      	sync_config();
      }

      inline int32_t tune_r_cnt(uint16_t r_cnt)
      {
      	do
      	  {
      	     r_cnt++;
      	     st.fpfd = (st.clkin * (st.data.ref_doubler_en ? 2 : 1)) / (r_cnt * (st.data.ref_div2_en ? 2 : 1));
      	  } while (st.fpfd > ADF4351_MAX_FREQ_PFD);
      	return r_cnt;
      }

      inline uint32_t gcd(uint32_t x, uint32_t y)
      {
      	int32_t tmp;
      	tmp = y > x ? x : y;
      	while((x % tmp) || (y % tmp))
      	{
      		tmp--;
      	}
      	return tmp;
      }

      inline void sync_config()
      {
      	int32_t  i, doublebuf = 0;

      	for (i = ADF4351_REG5; i >= ADF4351_REG0; i--) {
      		if ((st.regs_hw[i] != st.regs[i]) ||
      			((i == ADF4351_REG0) && doublebuf)) {

      			switch (i) {
      			case ADF4351_REG1:
      			case ADF4351_REG4:
      				doublebuf = 1;
      				break;
      			}

      			st.val = (st.regs[i] | i);
      			io.write(st.val);
      			st.regs_hw[i] = st.regs[i];
      		}
      	}
      }

  private:
      const io_t& io ;
      adf4351_st_t st ;
};

extern adf4351 synthesizer ;

#endif // __ADF4351_H__


/*

adf4351 need a implement 'io' function and set
to io_t io struct over constructor


// io implementation


#define SYNTHESIZER_SPI_PORT_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define SYNTHESIZER_SPI_PORT                  GPIOB
#define SYNTHESIZER_SPI_CLK_ENABLE()          __HAL_RCC_SPI2_CLK_ENABLE()
#define SYNTHESIZER_SPI                       SPI2
#define SYNTHESIZER_SPI_MOSI_PIN              GPIO_PIN_15
#define SYNTHESIZER_SPI_SCK_PIN               GPIO_PIN_10
#define SYNTHESIZER_SPI_CS_PIN                GPIO_PIN_11

void synthesizer_init ()
{
  GPIO_InitTypeDef GPIO_InitStruct;
  // init RESET and CS pins
  SYNTHESIZER_SPI_PORT_CLK_ENABLE();
  GPIO_InitStruct.Pin = SYNTHESIZER_SPI_CS_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(SYNTHESIZER_SPI_PORT, &GPIO_InitStruct);


  SYNTHESIZER_SPI_PORT->BSRR = SYNTHESIZER_SPI_CS_PIN ;

  // init SPI MOSI and CSK pins
  GPIO_InitStruct.Pin = SYNTHESIZER_SPI_MOSI_PIN|SYNTHESIZER_SPI_SCK_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(SYNTHESIZER_SPI_PORT, &GPIO_InitStruct);

  // init SPI
  SYNTHESIZER_SPI_CLK_ENABLE();
  SPI_HandleTypeDef hspi ;
  hspi.Instance = SYNTHESIZER_SPI;
  hspi.Init.Mode = SPI_MODE_MASTER;
  hspi.Init.Direction = SPI_DIRECTION_2LINES;
  hspi.Init.DataSize = SPI_DATASIZE_16BIT;
  hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi.Init.NSS = SPI_NSS_SOFT;
  hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi.Init.TIMode = SPI_TIMODE_DISABLED;
  hspi.Init.CRCPolynomial     = 7;
  hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
  HAL_SPI_Init(&hspi);

  __HAL_SPI_ENABLE(&hspi);
}

void synthesizer_write(uint32_t data)
{
    SYNTHESIZER_SPI_PORT->BSRR = SYNTHESIZER_SPI_CS_PIN << 16 ;

    while ( !((SYNTHESIZER_SPI->SR) & SPI_FLAG_TXE));
    SYNTHESIZER_SPI->DR = data >> 16;
    while ( !((SYNTHESIZER_SPI->SR) & SPI_FLAG_TXE));
    while ( !((SYNTHESIZER_SPI->SR) & SPI_FLAG_RXNE));
    while ( ((SYNTHESIZER_SPI->SR) & SPI_FLAG_BSY));

    while ( !((SYNTHESIZER_SPI->SR) & SPI_FLAG_TXE));
    SYNTHESIZER_SPI->DR = data & 0xff ;
    while ( !((SYNTHESIZER_SPI->SR) & SPI_FLAG_TXE));
    while ( !((SYNTHESIZER_SPI->SR) & SPI_FLAG_RXNE));
    while ( ((SYNTHESIZER_SPI->SR) & SPI_FLAG_BSY));

    SYNTHESIZER_SPI_PORT->BSRR = SYNTHESIZER_SPI_CS_PIN  ;
}

// define io interface
static adf4351::io_t io =
    {
	.init        = synthesizer_init,
	.write       = synthesizer_write,
        .lock_detect = 0,
	.muxout      = 0,
    };

// static create object
adf4351 synthesizer(io) ;

*/


