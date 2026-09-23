#ifndef __ETH_DRV_H__
#define __ETH_DRV_H__

#include "board.h"
#include "os.h"
#include "lwip\netif.h"
#include "netif\etharp.h"
#include "lwip\pbuf.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PHY_TIME_OUT     10    //таймаут операций запись/чтение в милисикундах
#define PHY_LINK_TIMEOUT 20000 //таймаут линка используется только при автоопределениии скорости

#define PHY_BASIC_CONTROL_ADDR 0x00
#define PHY_BASIC_STATUS_ADDR  0x01
#define PHY_CONTROL2_ADDR      0x1F

#define PHY_SOFTWARE_RESET        0x8000 
#define PHY_START_AUTONEGOTIATION 0x1000
#define PHY_100FULL               ((1 << 13) | (1 << 8))
#define PHY_100HALF                (1 << 13)
#define PHY_10FULL                 (1 << 8)
#define PHY_10HALF                 0

#define PHY_BASIC_STATUS_LINK_SHIFT 2
#define PHY_BASIC_STATUS_ANC_SHIFT  5 //Auto-negotioation complete

#define PHY_CONTROL2_FULL_MASK    (1 << 4)
#define PHY_CONTROL2_SPEED_MASK   (1 << 2)

#define ETH_RX_BUFF_COUNT 4
#define ETH_TX_BUFF_COUNT 2

#define ETH_RX_BUFF_SIZE 1540
#define ETH_TX_BUFF_SIZE 1540

enum eth_link_speed
{
  LINK_SPEED_AUTO    = 0,
  LINK_SPEED_100FULL = 1,
  LINK_SPEED_100HALF = 2,
  LINK_SPEED_10FULL  = 3,
  LINK_SPEED_10HALF  = 4
};

typedef struct eth_config_tag
{ 
  uint8_t  phy_addr;
  uint8_t  speed;
  uint8_t  MAC[6];
}eth_config_t;

typedef struct eth_DMADesc_tag  
{
  uint32_t   Status;                /*!< Status */
  uint32_t   Control;               /*!< Control and Buffer1, Buffer2 lengths */
  uint8_t   *BufferAddr;            /*!< Buffer1 address pointer */
  struct eth_DMADesc_tag   *NextDesc;              /*!< Buffer2 or next descriptor address pointer */
} eth_DMADesc_t;


err_t EthInit(struct netif *ethif);
uint32_t ETH_GetLinkStatus(uint32_t phy_addr);

#define ETH_DMATxDesc_OWN                     ((uint32_t)0x80000000)  /*!< OWN bit: descriptor is owned by DMA engine */
#define ETH_DMATxDesc_IC                      ((uint32_t)0x40000000)  /*!< Interrupt on Completion */
#define ETH_DMATxDesc_LS                      ((uint32_t)0x20000000)  /*!< Last Segment */
#define ETH_DMATxDesc_FS                      ((uint32_t)0x10000000)  /*!< First Segment */
#define ETH_DMATxDesc_DC                      ((uint32_t)0x08000000)  /*!< Disable CRC */
#define ETH_DMATxDesc_DP                      ((uint32_t)0x04000000)  /*!< Disable Padding */
#define ETH_DMATxDesc_TTSE                    ((uint32_t)0x02000000)  /*!< Transmit Time Stamp Enable */
#define ETH_DMATxDesc_CIC                     ((uint32_t)0x00C00000)  /*!< Checksum Insertion Control: 4 cases */
#define ETH_DMATxDesc_CIC_ByPass              ((uint32_t)0x00000000)  /*!< Do Nothing: Checksum Engine is bypassed */ 
#define ETH_DMATxDesc_CIC_IPV4Header          ((uint32_t)0x00400000)  /*!< IPV4 header Checksum Insertion */ 
#define ETH_DMATxDesc_CIC_TCPUDPICMP_Segment  ((uint32_t)0x00800000)  /*!< TCP/UDP/ICMP Checksum Insertion calculated over segment only */ 
#define ETH_DMATxDesc_CIC_TCPUDPICMP_Full     ((uint32_t)0x00C00000)  /*!< TCP/UDP/ICMP Checksum Insertion fully calculated */ 
#define ETH_DMATxDesc_TER                     ((uint32_t)0x00200000)  /*!< Transmit End of Ring */
#define ETH_DMATxDesc_TCH                     ((uint32_t)0x00100000)  /*!< Second Address Chained */
#define ETH_DMATxDesc_TTSS                    ((uint32_t)0x00020000)  /*!< Tx Time Stamp Status */
#define ETH_DMATxDesc_IHE                     ((uint32_t)0x00010000)  /*!< IP Header Error */
#define ETH_DMATxDesc_ES                      ((uint32_t)0x00008000)  /*!< Error summary: OR of the following bits: UE || ED || EC || LCO || NC || LCA || FF || JT */
#define ETH_DMATxDesc_JT                      ((uint32_t)0x00004000)  /*!< Jabber Timeout */
#define ETH_DMATxDesc_FF                      ((uint32_t)0x00002000)  /*!< Frame Flushed: DMA/MTL flushed the frame due to SW flush */
#define ETH_DMATxDesc_PCE                     ((uint32_t)0x00001000)  /*!< Payload Checksum Error */
#define ETH_DMATxDesc_LCA                     ((uint32_t)0x00000800)  /*!< Loss of Carrier: carrier lost during tramsmission */
#define ETH_DMATxDesc_NC                      ((uint32_t)0x00000400)  /*!< No Carrier: no carrier signal from the tranceiver */
#define ETH_DMATxDesc_LCO                     ((uint32_t)0x00000200)  /*!< Late Collision: transmission aborted due to collision */
#define ETH_DMATxDesc_EC                      ((uint32_t)0x00000100)  /*!< Excessive Collision: transmission aborted after 16 collisions */
#define ETH_DMATxDesc_VF                      ((uint32_t)0x00000080)  /*!< VLAN Frame */
#define ETH_DMATxDesc_CC                      ((uint32_t)0x00000078)  /*!< Collision Count */
#define ETH_DMATxDesc_ED                      ((uint32_t)0x00000004)  /*!< Excessive Deferral */
#define ETH_DMATxDesc_UF                      ((uint32_t)0x00000002)  /*!< Underflow Error: late data arrival from the memory */
#define ETH_DMATxDesc_DB                      ((uint32_t)0x00000001)  /*!< Deferred Bit */


#define ETH_DMARxDescFL_SHIFT   16u
#define ETH_DMARxDescFL_MASK    0x3FFFu
#define ETH_DMARxDescLSFS_MASK  0x300u

#define ETH_DMARxDesc_OWN         ((uint32_t)0x80000000)  /*!< OWN bit: descriptor is owned by DMA engine  */
#define ETH_DMARxDesc_AFM         ((uint32_t)0x40000000)  /*!< DA Filter Fail for the rx frame  */
#define ETH_DMARxDesc_FL          ((uint32_t)0x3FFF0000)  /*!< Receive descriptor frame length  */
#define ETH_DMARxDesc_ES          ((uint32_t)0x00008000)  /*!< Error summary: OR of the following bits: DE || OE || IPC || LC || RWT || RE || CE */
#define ETH_DMARxDesc_DE          ((uint32_t)0x00004000)  /*!< Desciptor error: no more descriptors for receive frame  */
#define ETH_DMARxDesc_SAF         ((uint32_t)0x00002000)  /*!< SA Filter Fail for the received frame */
#define ETH_DMARxDesc_LE          ((uint32_t)0x00001000)  /*!< Frame size not matching with length field */
#define ETH_DMARxDesc_OE          ((uint32_t)0x00000800)  /*!< Overflow Error: Frame was damaged due to buffer overflow */
#define ETH_DMARxDesc_VLAN        ((uint32_t)0x00000400)  /*!< VLAN Tag: received frame is a VLAN frame */
#define ETH_DMARxDesc_FS          ((uint32_t)0x00000200)  /*!< First descriptor of the frame  */
#define ETH_DMARxDesc_LS          ((uint32_t)0x00000100)  /*!< Last descriptor of the frame  */ 
#define ETH_DMARxDesc_IPV4HCE     ((uint32_t)0x00000080)  /*!< IPC Checksum Error: Rx Ipv4 header checksum error   */    
#define ETH_DMARxDesc_LC          ((uint32_t)0x00000040)  /*!< Late collision occurred during reception   */
#define ETH_DMARxDesc_FT          ((uint32_t)0x00000020)  /*!< Frame type - Ethernet, otherwise 802.3    */
#define ETH_DMARxDesc_RWT         ((uint32_t)0x00000010)  /*!< Receive Watchdog Timeout: watchdog timer expired during reception    */
#define ETH_DMARxDesc_RE          ((uint32_t)0x00000008)  /*!< Receive error: error reported by MII interface  */
#define ETH_DMARxDesc_DBE         ((uint32_t)0x00000004)  /*!< Dribble bit error: frame contains non int multiple of 8 bits  */
#define ETH_DMARxDesc_CE          ((uint32_t)0x00000002)  /*!< CRC error */
#define ETH_DMARxDesc_MAMPCE      ((uint32_t)0x00000001)  /*!< Rx MAC Address/Payload Checksum Error: Rx MAC address matched/ Rx Payload Checksum Error */
//control
#define ETH_DMARxDesc_DIC   ((uint32_t)0x80000000)  /*!< Disable Interrupt on Completion */
#define ETH_DMARxDesc_RBS2  ((uint32_t)0x1FFF0000)  /*!< Receive Buffer2 Size */
#define ETH_DMARxDesc_RER   ((uint32_t)0x00008000)  /*!< Receive End of Ring */
#define ETH_DMARxDesc_RCH   ((uint32_t)0x00004000)  /*!< Second Address Chained */
#define ETH_DMARxDesc_RBS1  ((uint32_t)0x00001FFF)  /*!< Receive Buffer1 Size */

#ifdef __cplusplus
}
#endif

#endif
