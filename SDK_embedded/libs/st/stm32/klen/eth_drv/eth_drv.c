#include "eth_drv.h"
#include "lwip\tcpip.h"
#include "lwip\mem.h"
#include "lwip\pbuf.h"
#include "arch\cc.h"
#include "leds.h"
#include "dev_debug.h"
#include "dev_config.h"

eth_DMADesc_t EthRxDsc[ETH_RX_BUFF_COUNT];
eth_DMADesc_t EthTxDsc[ETH_TX_BUFF_COUNT];

uint8_t RxBuff[ETH_RX_BUFF_COUNT][ETH_RX_BUFF_SIZE];
uint8_t TxBuff[ETH_TX_BUFF_COUNT][ETH_TX_BUFF_SIZE]; 

typedef struct eth_pcb_tag
{
  struct netif  *ethif;
  eth_DMADesc_t *CurrRxDsc;
  eth_DMADesc_t *CurrTxDsc;
  osSem_t       RxSem;
  uint16_t      PhyAddr;
  uint16_t      Speed;
}eth_pcb_t;

eth_pcb_t Eth_pcb;

//forward declaration
err_t EthReadPHYRegister(uint16_t PHY_address, uint16_t PHY_reg, uint16_t *read_value);
err_t EthWritePHYRegister(uint16_t PHY_rddress, uint16_t PHY_reg, uint16_t write_value);
err_t output(struct netif *netif, struct pbuf *p);
/******************************************************************************
* FUNCTION:     ETHInit
*
* DESCRIPTION:  инициализация драйвера ethernet
* PARAMETERS:   нет
* RETURNS:      нет
*
******************************************************************************/
void EthIRQ(void)
{
  signed long xYieldRequired = pdFALSE;;
  uint32_t isr;
  isr = ETH->DMASR;
  if (isr & (1 << 6))
  {
    ETH->DMASR = (1 << 6) | (1 << 16);
    osSemSignalFromIRQ(Eth_pcb.RxSem,&xYieldRequired);
    portEND_SWITCHING_ISR(xYieldRequired);
  }
}
/******************************************************************************
* FUNCTION:     Eth_DSC_Init
*
* DESCRIPTION:  
* PARAMETERS:   
* RETURNS:      
*
******************************************************************************/
inline static void Eth_DSC_Init(void)
{
  uint32_t i;
  ETH->DMAOMRbit.ST  = 0;
  ETH->DMAOMRbit.SR  = 0;
  
  /*********************** DESCRIPTOR INIT ************************/
  //rx
  for ( i=0; i < ETH_RX_BUFF_COUNT-1; i++ )
  {
    EthRxDsc[i].Status  = 0x80000000u;
    EthRxDsc[i].Control = 0x00004000 | ETH_RX_BUFF_SIZE; 
    EthRxDsc[i].BufferAddr = &RxBuff[i][0];
    EthRxDsc[i].NextDesc   = &EthRxDsc[i+1];
  }
  
  EthRxDsc[i].Status  = ETH_DMARxDesc_OWN;
  EthRxDsc[i].Control = ETH_DMARxDesc_RCH | ETH_RX_BUFF_SIZE; 
  EthRxDsc[i].BufferAddr = &RxBuff[i][0];
  EthRxDsc[i].NextDesc   = &EthRxDsc[0];

  Eth_pcb.CurrRxDsc = &EthRxDsc[0];
  ETH->DMARDLAR = (uint32_t)&EthRxDsc[0];
  
  //tx 
  for ( i=0; i < ETH_TX_BUFF_COUNT-1; i++ )
  {
    EthTxDsc[i].Status     = ETH_DMATxDesc_TCH;
    EthTxDsc[i].Control    = 0; 
    EthTxDsc[i].BufferAddr = &TxBuff[i][0];
    EthTxDsc[i].NextDesc   = &EthTxDsc[i+1];
  }

  EthTxDsc[i].Status     = ETH_DMATxDesc_TCH;
  EthTxDsc[i].Control    = 0; 
  EthTxDsc[i].BufferAddr = &TxBuff[i][0];
  EthTxDsc[i].NextDesc   = &EthTxDsc[0];

  Eth_pcb.CurrTxDsc = &EthTxDsc[0];
  ETH->DMATDLAR = (uint32_t)EthTxDsc;  
  ETH->DMAOMRbit.ST  = 1;
  ETH->DMAOMRbit.SR  = 1;
}
/******************************************************************************
* FUNCTION:     Eth_LwIP_Status_Callback
*
* DESCRIPTION:  
* PARAMETERS:   
* RETURNS:      
*
******************************************************************************/
void Eth_LwIP_Status_Callback(struct netif *netif)
{
  if ( netif->flags & NETIF_FLAG_UP)
  {
    ETH->MACCRbit.TE   = 1;
    ETH->MACCRbit.RE   = 1;    
  }
  else
  {
    ETH->MACCRbit.RE   = 0;
    ETH->MACCRbit.TE   = 0;    
  }
}
/******************************************************************************
* FUNCTION:     Eth_LinkCheck
*
* DESCRIPTION:  
* PARAMETERS:   
* RETURNS:      
*
******************************************************************************/
static inline uint32_t Eth_LinkCheck(eth_pcb_t *pcb)
{
  uint16_t phy_value;
  if (EthReadPHYRegister(pcb->PhyAddr,PHY_BASIC_STATUS_ADDR,&phy_value)!=ERR_OK)
  {
    return 0;
  }
  else
  {
    return ((phy_value & (1 << PHY_BASIC_STATUS_LINK_SHIFT))!=0);
  }  
}
/******************************************************************************
* FUNCTION:     Eth_LinkUP
*
* DESCRIPTION:  
* PARAMETERS:   
* RETURNS:      
*
******************************************************************************/
uint32_t Eth_LinkUP(eth_pcb_t *pcb)
{
  uint32_t f_flag,s_flag,timeout;
  uint16_t phy_value;
  timeout = 200;
  switch ( pcb->Speed )
  {
    case LINK_SPEED_100FULL:
      f_flag = 1;
      s_flag = 1;
      EthWritePHYRegister(pcb->PhyAddr,PHY_BASIC_CONTROL_ADDR,PHY_100FULL);
    break;
    case LINK_SPEED_100HALF:
      f_flag = 0;
      s_flag = 1;
      EthWritePHYRegister(pcb->PhyAddr,PHY_BASIC_CONTROL_ADDR,PHY_100HALF);
    break;
    case LINK_SPEED_10FULL:
      f_flag = 1;
      s_flag = 0;
      EthWritePHYRegister(pcb->PhyAddr,PHY_BASIC_CONTROL_ADDR,PHY_10FULL);
    break;
    case LINK_SPEED_10HALF:
      f_flag = 0;
      s_flag = 0;
      EthWritePHYRegister(pcb->PhyAddr,PHY_BASIC_CONTROL_ADDR,PHY_10HALF);
    break;
    default:  //LINK_SPEED_AUTO
      f_flag  = 1;
      s_flag  = 1;
      EthWritePHYRegister(pcb->PhyAddr,PHY_BASIC_CONTROL_ADDR,PHY_START_AUTONEGOTIATION);
      do
      {
        osSleep(1);
        EthReadPHYRegister(pcb->PhyAddr,PHY_BASIC_STATUS_ADDR,&phy_value);
        if (phy_value & (1 << PHY_BASIC_STATUS_ANC_SHIFT))
        {
          EthReadPHYRegister(pcb->PhyAddr,PHY_CONTROL2_ADDR,&phy_value);
          f_flag = (phy_value & PHY_CONTROL2_FULL_MASK)?1:0;
          s_flag = (phy_value & PHY_CONTROL2_SPEED_MASK)?0:1;
          break;
        }
      } while (timeout--);
    break;
  } //end switch  
  /******************************* MAC *****************************/
  ETH->MACCR = 0
               |(0 << ETH_MACCR_RE_SHIFT)  
               |(0 << ETH_MACCR_TE_SHIFT)  
               |(1 << ETH_MACCR_DC_SHIFT)  
               |(0 << ETH_MACCR_BL_SHIFT)  
               |(1 << ETH_MACCR_APCS_SHIFT)
               |(0 << ETH_MACCR_RD_SHIFT)  
               #ifdef ETHERNET_CHECKSUM_BY_HARDWARE
               |(1 << ETH_MACCR_IPCO_SHIFT) //enable CRC
               #endif
               |(f_flag << ETH_MACCR_DM_SHIFT)  
               |(0 << ETH_MACCR_LM_SHIFT)  
               |(1 << ETH_MACCR_ROD_SHIFT) 
               |(s_flag << ETH_MACCR_FES_SHIFT) 
               |(0 << ETH_MACCR_CSD_SHIFT) 
               |(4 << ETH_MACCR_IFG_SHIFT) 
               |(0 << ETH_MACCR_JD_SHIFT)  
               |(1 << ETH_MACCR_WD_SHIFT)  
               ;
  if (Eth_LinkCheck(pcb))
  {
    if ( pcb->ethif->flags & NETIF_FLAG_UP)
    {
      ETH->MACCR |= (1 << ETH_MACCR_RE_SHIFT) | (1 << ETH_MACCR_TE_SHIFT); 
    }
    return 1;  
  }
  else
  {
    return 0;
  }
};
/******************************************************************************
* FUNCTION:     EthRxTask
*
* DESCRIPTION:  инициализация драйвера ethernet
* PARAMETERS:   нет
* RETURNS:      нет
*
******************************************************************************/
__task void EthRxTask(eth_pcb_t *pcb)
{
  uint32_t frame_size,status;
  struct pbuf *p, *q;
  uint8_t *ptr;
  for( ;; )
  {
    if (osSemWait(pcb->RxSem,500) != SEM_TIMEOUT)
    {
      while(( pcb->CurrRxDsc->Status & ETH_DMARxDesc_OWN ) == 0)
      {
        status = pcb->CurrRxDsc->Status;
        if(((status & ETH_DMATxDesc_ES) == 0) && ((status & ETH_DMARxDescLSFS_MASK)!=0))
        {
          frame_size = ((status >> ETH_DMARxDescFL_SHIFT) & ETH_DMARxDescFL_MASK) - 4;
          p = pbuf_alloc(PBUF_RAW, frame_size, PBUF_POOL);
          if (p != NULL)
          {
            ptr = pcb->CurrRxDsc->BufferAddr;
            for (q = p; q != NULL; q = q->next)
            {
              memcpy((u8_t*)q->payload, ptr, q->len);
              ptr += q->len;
            }
            if (tcpip_input(p,pcb->ethif) != ERR_OK) pbuf_free(p); 
          }
        };
        pcb->CurrRxDsc->Status = 0x80000000u;
        pcb->CurrRxDsc = pcb->CurrRxDsc->NextDesc;
      };
      
      if(ETH->DMASR & (1  << ETH_DMASR_RBUS_SHIFT))  
      {
        ETH->DMASR = (1 << ETH_DMASR_RBUS_SHIFT);
        ETH->DMARPDR = 0;
      }
    }
    else
    {
      if(Eth_LinkCheck(pcb) == 0)
      {
        netif_set_link_down(pcb->ethif);
      }
      else
      {
        if ((pcb->ethif->flags & NETIF_FLAG_LINK_UP) == 0)
        {
          if (Eth_LinkUP(pcb)) 
          {
            netif_set_link_up(pcb->ethif);
          }
        }
      }
    }
  }
}
/******************************************************************************
* FUNCTION:     ETHInit
*
* DESCRIPTION:  инициализация драйвера ethernet
* PARAMETERS:   нет
* RETURNS:      нет
*
******************************************************************************/
err_t EthInit(struct netif *ethif)
{
  eth_config_t *eth_config = (eth_config_t*)ethif->state;
  
  netif_set_link_down(ethif);
  ethif->output     = etharp_output;                          //Вывод через ARP модуль
  ethif->linkoutput = output;                                 //Вывод через MAC модуль
  ethif->input      = tcpip_input;                            //Ввод в стек 
  ethif->mtu        = 1500;                                   //maximum transfer unit
  ethif->flags      = NETIF_FLAG_BROADCAST|NETIF_FLAG_ETHARP; //broadcast capability
  Eth_pcb.ethif     = ethif;
  Eth_pcb.PhyAddr   = eth_config->phy_addr;
  Eth_pcb.Speed     = eth_config->speed;
  /********************** Клоки AHB APB1 APB2 шины ************************************/
  RCC->AHBENR |= (1 << RCC_ETHMACRXEN_SHIFT) | (1 << RCC_ETHMACTXEN_SHIFT) | (1 << RCC_ETHMACEN_SHIFT);
  /****************** RESET MAC CORE ************************************/
  ETH->DMABMR = 0x01;
  while( ETH->DMABMR & 0x01 );
  /****************** PHY Clock **************************************/
  if((CPU_HCLK_FREQUENCY >= 20000000) && (CPU_HCLK_FREQUENCY < 35000000))
  {
    ETH->MACMIIARbit.CR = 0x02; /* CSR Clock Range between 20-35 MHz */
  }
  else if((CPU_HCLK_FREQUENCY >= 35000000) && (CPU_HCLK_FREQUENCY < 60000000))
  {
    ETH->MACMIIARbit.CR = 0x03;/* CSR Clock Range between 35-60 MHz */ 
  }  
  else 
  {
    ETH->MACMIIARbit.CR = 0x00;/* CSR Clock Range between 60-72 MHz */   
  }
  /**************************** LwIP CallBACKs **********************/
  netif_set_status_callback(ethif,Eth_LwIP_Status_Callback);
  /******************************* SET MAC ADDR ********************/
  ethif->hwaddr_len = 6;
  memcpy(ethif->hwaddr,eth_config->MAC,sizeof(ethif->hwaddr));
  ETH->MACA0HR  = (1 << 31) | (eth_config->MAC[5] << 8) | (eth_config->MAC[4]);
  ETH->MACA0LR  = (eth_config->MAC[3] << 24) | (eth_config->MAC[2] << 16) | (eth_config->MAC[1] << 8) | (eth_config->MAC[0]); 
  ETH->MACA1HR  = 0;
  ETH->MACA2HR  = 0;
  ETH->MACA3HR  = 0;
  /********************** REG SETS ********************************/
  ETH->MACFFR = 0 
                |( 0 << ETH_MACFFR_PM_SHIFT)  
                |( 0 << ETH_MACFFR_HU_SHIFT)  
                |( 0 << ETH_MACFFR_HM_SHIFT)  
                |( 0 << ETH_MACFFR_DAIF_SHIFT)
                |( 0 << ETH_MACFFR_PAM_SHIFT) 
                |( 0 << ETH_MACFFR_BFD_SHIFT) 
                |( 0 << ETH_MACFFR_PCF_SHIFT) 
                |( 1 << ETH_MACFFR_SAF_SHIFT) 
                |( 0 << ETH_MACFFR_HPF_SHIFT) 
                ;

  ETH->MACHTHR = 0;
  ETH->MACHTLR = 0;
  ETH->MACIMR  = 0;

  ETH->MACFCR = 0
                |( 0 << ETH_MACFCR_FCB_BPA_SHIFT)
                |( 0 << ETH_MACFCR_TFCE_SHIFT)   
                |( 0 << ETH_MACFCR_RFCE_SHIFT)   
                |( 0 << ETH_MACFCR_UPFD_SHIFT)   
                |( 0 << ETH_MACFCR_PLT_SHIFT)    
                |( 1 << ETH_MACFCR_ZQPD_SHIFT)   
                |( 5 << ETH_MACFCR_PT_SHIFT)     
                ;

  ETH->MACVLANTR = 0;

  /**************************** PTP **************************/
  ETH->MACPMTCSR = 0;
  /**************************** MMC **************************/
  ETH->MMCCR = 0
               |( 1 << ETH_MMCCR_CR_SHIFT) 
               |( 0 << ETH_MMCCR_CSR_SHIFT)
               |( 0 << ETH_MMCCR_ROR_SHIFT)
               |( 0 << ETH_MMCCR_MCF_SHIFT)
               ; 
  ETH->MMCRIMR = 0;
  ETH->MMCTIMR = 0;

  /**************************** DMA ***************************/
  ETH->DMAOMR = 0
                | ( 0 << ETH_DMAOMR_SR_SHIFT )    
                | ( 0 << ETH_DMAOMR_OSF_SHIFT )  
                | ( 0 << ETH_DMAOMR_RTC_SHIFT )   
                | ( 0 << ETH_DMAOMR_FUGF_SHIFT )  
                | ( 0 << ETH_DMAOMR_FEF_SHIFT )   
                | ( 0 << ETH_DMAOMR_ST_SHIFT )    
                | ( 0 << ETH_DMAOMR_TTC_SHIFT )   
                | ( 0 << ETH_DMAOMR_FTF_SHIFT )   
                | ( 1 << ETH_DMAOMR_TSF_SHIFT )   
                | ( 0 << ETH_DMAOMR_DFRF_SHIFT )  
                | ( 1 << ETH_DMAOMR_RSF_SHIFT )   
                | ( 0 << ETH_DMAOMR_DTCEFD_SHIFT )
                ;

  ETH->DMABMR = 0
                |( 0<< ETH_DMABMR_SR_SHIFT )   
                |( 0<< ETH_DMABMR_DA_SHIFT )  
                |( 0<< ETH_DMABMR_DSL_SHIFT )  
                |( 1<< ETH_DMABMR_PBL_SHIFT )  
                |( 0<< ETH_DMABMR_RTPR_SHIFT ) 
                |( 0<< ETH_DMABMR_FB_SHIFT )   
                |( 1<< ETH_DMABMR_RDP_SHIFT )  
                |( 1<< ETH_DMABMR_USP_SHIFT )  
                |( 0<< ETH_DMABMR_FPM_SHIFT )  
                |( 1<< ETH_DMABMR_AAB_SHIFT )  
                ; 
  Eth_DSC_Init();  
  /********************** PHY RESET ********************************/
  if(EthWritePHYRegister(eth_config->phy_addr,PHY_BASIC_CONTROL_ADDR,PHY_SOFTWARE_RESET)!=ERR_OK)
  {
    return ERR_IF;
  }
  /*********************** Task init ******************************/
  osSemNew(Eth_pcb.RxSem,SEM_NO_SIGNAL,"EthRx");
  if ( Eth_pcb.RxSem == NULL )
  {
    return ERR_MEM;
  };
  
  if ( xTaskCreate((pdTASK_CODE)EthRxTask,"Eth",75,&Eth_pcb,2,NULL) == NULL )
  {
    return ERR_MEM;
  }
  /*********************** ISR enable ******************************/
  ETH->DMAIERbit.RIE = 1;
  ETH->DMAIERbit.NISE = 1; 
  NVIC_SETPriority(ETH_IRQChannel,DEVICE_MID_INTERRUPT_PRIORITY);
  NVIC_IRQEnable(ETH_IRQChannel);
  return DEV_ERR_OK;
}
/******************************************************************************
* FUNCTION:     EthReadPHYRegister
*
* DESCRIPTION:  Чтение регистра PHY
* PARAMETERS:   uint16_t PHY_address - адрес микросхемы PHY
*               uint16_t PHY_reg     - регистр PHY,
*               uint16_t *read_value - указатель куда сохранять прочитанное значение
* RETURNS:      ERR_OK || ERR_TIMEOUT
*
******************************************************************************/
#pragma inline =forced
inline err_t EthReadPHYRegister(uint16_t PHY_address, uint16_t PHY_reg, uint16_t *read_value)
{
  uint32_t timeout = PHY_TIME_OUT;
  uint32_t tmp = ETH->MACMIIAR;
  ((__eth_macmiiar_bits*)&tmp)->PA = PHY_address;
  ((__eth_macmiiar_bits*)&tmp)->MR = PHY_reg;
  ((__eth_macmiiar_bits*)&tmp)->MW = 0;
  ((__eth_macmiiar_bits*)&tmp)->MB = 1;
  ETH->MACMIIAR = tmp;
  osTaskYIELD();
  while( ETH->MACMIIARbit.MB )
  {
    if ( --timeout == 0 ) return ERR_TIMEOUT;
    osSleep(1);
  };
  *read_value = ETH->MACMIIDR; 
  return ERR_OK;
}
/******************************************************************************
* FUNCTION:     EthWritePHYRegister
*
* DESCRIPTION:  Запись регистра PHY
* PARAMETERS:   uint16_t PHY_address - адрес микросхемы PHY
*               uint16_t PHY_reg     - регистр PHY,
*               uint16_t *read_value - указатель куда сохранять прочитанное значение
* RETURNS:      ERR_OK || ERR_TIMEOUT
*
******************************************************************************/
#pragma inline =forced
inline err_t EthWritePHYRegister(uint16_t PHY_address, uint16_t PHY_reg, uint16_t write_value)
{
  uint32_t timeout = PHY_TIME_OUT;
  uint32_t tmp;
  ETH->MACMIIDR = write_value;
  tmp = ETH->MACMIIAR;
  ((__eth_macmiiar_bits*)&tmp)->PA = PHY_address;
  ((__eth_macmiiar_bits*)&tmp)->MR = PHY_reg;
  ((__eth_macmiiar_bits*)&tmp)->MW = 1;
  ((__eth_macmiiar_bits*)&tmp)->MB = 1;
  ETH->MACMIIAR = tmp;
  osTaskYIELD();
  while( ETH->MACMIIARbit.MB)
  {
    if ( --timeout == 0 ) return ERR_TIMEOUT;
    osSleep(1);
  };
  return ERR_OK;
}
/******************************************************************************
* FUNCTION:     output
*
* DESCRIPTION:  
* PARAMETERS:   
* RETURNS:      
*
******************************************************************************/
err_t output(struct netif *netif, struct pbuf *p)
{
  struct pbuf *q;
  uint8_t *ptr;
  
  while ( Eth_pcb.CurrTxDsc->Status & ETH_DMATxDesc_OWN  )
  {
    if ((ETH->DMASR & ( 1 << ETH_DMASR_TBUS_SHIFT)) != 0)
    {
      ETH->DMASR = ( 1 << ETH_DMASR_TBUS_SHIFT );
      ETH->DMATPDR = 0;
    }
    osTaskYIELD();
  };
  
  ptr = Eth_pcb.CurrTxDsc->BufferAddr;
  for(q = p; q != NULL; q = q->next) 
  {
    memcpy(ptr, q->payload, q->len);
	 ptr += q->len;
  }
  Eth_pcb.CurrTxDsc->Control = p->tot_len;
  Eth_pcb.CurrTxDsc->Status = ETH_DMATxDesc_LS 
                            | ETH_DMATxDesc_FS 
                            | ETH_DMATxDesc_TCH
                            #ifdef ETHERNET_CHECKSUM_BY_HARDWARE
                            | ETH_DMATxDesc_CIC_TCPUDPICMP_Full 
                            #endif
                            | ETH_DMATxDesc_OWN
                            ;
  if ((ETH->DMASR & ( 1 << ETH_DMASR_TBUS_SHIFT)) != 0)
  {
    ETH->DMASR = ( 1 << ETH_DMASR_TBUS_SHIFT );
    ETH->DMATPDR = 0;
  }
  Eth_pcb.CurrTxDsc = Eth_pcb.CurrTxDsc->NextDesc;
  return ERR_OK;
}
