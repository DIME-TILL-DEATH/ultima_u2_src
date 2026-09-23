#include "usbd_cdc_interface.h"

#if  !defined (USBD_CDC_RX_BUFFER_SIZE) || !defined (USBD_CDC_TX_BUFFER_SIZE)
 #error "USBD_CDC_RX_BUFFER_SIZE and USBD_CDC_TX_BUFFER_SIZE must be defined in option.mk, this params must be 2^n !!!"
#endif

uint8_t UserRxBuffer[USBD_CDC_RX_BUFFER_SIZE];/* Received Data over USB are stored in this buffer */
uint8_t UserTxBuffer[USBD_CDC_TX_BUFFER_SIZE];/* Received Data over UART (CDC interface) are stored in this buffer */


uint32_t UserTxBufPtrIn = 0;/* Increment this pointer or roll it back to
                               start address when data are received over USART */
uint32_t UserTxBufPtrOut = 0; /* Increment this pointer or roll it back to
                                 start address when data are sent over USB */

extern USBD_HandleTypeDef  USBD_Device;

/* Private function prototypes -----------------------------------------------*/
static int8_t CDC_Itf_Init(USBD_HandleTypeDef *pdev);
static int8_t CDC_Itf_DeInit(USBD_HandleTypeDef *pdev);
static int8_t CDC_Itf_Control(USBD_HandleTypeDef *pdev, uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t CDC_Itf_Receive(USBD_HandleTypeDef *pdev, uint8_t* pbuf, uint32_t *len);

USBD_CDC_ItfTypeDef USBD_CDC_fops = 
{
  CDC_Itf_Init,
  CDC_Itf_DeInit,
  CDC_Itf_Control,
  CDC_Itf_Receive
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CDC media low layer      
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_Init(USBD_HandleTypeDef *pdev)
{
  USBD_CDC_SetTxBuffer(pdev, UserTxBuffer, 0);
  USBD_CDC_SetRxBuffer(pdev, UserRxBuffer);
  return (USBD_OK);
}

/**
  * @brief  CDC_Itf_DeInit
  *         DeInitializes the CDC media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_DeInit(USBD_HandleTypeDef *pdev)
{
  return (USBD_OK);
}

/**
  * @brief  CDC_Itf_Control
  *         Manage the CDC class requests
  * @param  Cmd: Command code            
  * @param  Buf: Buffer containing command data (request parameters)
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_Control (USBD_HandleTypeDef *pdev, uint8_t cmd, uint8_t* pbuf, uint16_t length)
{ 
  return (USBD_OK);
}

// transmit ower USB
void CDC_SendData(const uint8_t* buf , const uint32_t len )
{
  size_t rbf_size = 0 ;
  size_t lbf_size = 0 ;

  if ( UserTxBufPtrOut <= UserTxBufPtrIn )
    {
      rbf_size = USBD_CDC_TX_BUFFER_SIZE - UserTxBufPtrIn ;
      lbf_size = UserTxBufPtrOut ;

      if ( rbf_size + lbf_size < len )
	{
	  // buffer overflow
	  return ;
	}
      else
	{
	  if ( len <= rbf_size )
	    {
	      memcpy ( UserTxBuffer + UserTxBufPtrIn , buf , len ) ;
	      UserTxBufPtrIn += len ;
	    }
	  else
	    {
	      memcpy ( UserTxBuffer + UserTxBufPtrIn , buf , rbf_size ) ;
	      memcpy ( UserTxBuffer , buf+rbf_size , len-rbf_size ) ;
	      UserTxBufPtrIn = len-rbf_size ;
	    }
	}

     }
   else // UserTxBufPtrOut > UserTxBufPtrIn
    {
      rbf_size = UserTxBufPtrOut - UserTxBufPtrIn ;
      if ( rbf_size < len )
      	{
      	  // buffer overflow
	  return ;
      	}
      else
	{
	  memcpy ( UserTxBuffer + UserTxBufPtrIn , buf , len ) ;
	  UserTxBufPtrIn += len ;
	}
    }

  UserTxBufPtrIn = UserTxBufPtrIn % USBD_CDC_TX_BUFFER_SIZE ;
}

/**
  * @brief  CDC_Itf_DataRx
  *         Data received over USB OUT endpoint are sent over CDC interface 
  *         through this function.
  * @param  Buf: Buffer of data to be transmitted
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_Receive(USBD_HandleTypeDef *pdev, uint8_t* buf, uint32_t *len)
{
  // call user receive handler
  CDC_Receive( buf, *len ) ;
  USBD_CDC_ReceivePacket(pdev);
  return (USBD_OK);
}


size_t CDC_Transmit(USBD_HandleTypeDef *pdev)
{
  size_t rbl_size = 0 ;
  size_t lbl_size = 0 ;

  if(UserTxBufPtrOut == UserTxBufPtrIn) return 0 ;

    if ( UserTxBufPtrOut < UserTxBufPtrIn )
      {
        rbl_size =  UserTxBufPtrIn - UserTxBufPtrOut ;
        USBD_CDC_SetTxBuffer(pdev, (uint8_t*)&UserTxBuffer+UserTxBufPtrOut, rbl_size);
        if ( USBD_CDC_TransmitPacket(pdev) == USBD_OK )
          {
            UserTxBufPtrOut += rbl_size ;
          }
        else return 0 ;
       }
    else
      {
	rbl_size =  USBD_CDC_TX_BUFFER_SIZE - UserTxBufPtrOut ;
	USBD_CDC_SetTxBuffer(pdev, (uint8_t*)&UserTxBuffer+UserTxBufPtrOut, rbl_size);
	if ( USBD_CDC_TransmitPacket(pdev) == USBD_OK )
	   {
	     UserTxBufPtrOut = 0 ;
	   }
	else return 0 ;
	lbl_size = UserTxBufPtrIn ;
	USBD_CDC_SetTxBuffer(pdev, (uint8_t*)&UserTxBuffer+UserTxBufPtrOut, lbl_size);
	if ( USBD_CDC_TransmitPacket(pdev) == USBD_OK )
	   {
	     UserTxBufPtrOut = UserTxBufPtrIn ;
	   }
	else return 0 ;
      }

    UserTxBufPtrOut = UserTxBufPtrOut % USBD_CDC_TX_BUFFER_SIZE ;
    USBD_CDC_ReceivePacket(pdev);

    return UserTxBufPtrOut - UserTxBufPtrIn ;
}

