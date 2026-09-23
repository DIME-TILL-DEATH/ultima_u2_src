#include "appdefs.h"
#include "i2c_gpio.h"

#define I2C_BIT_SET 1
#define I2C_BIT_CLEAR 0
#define I2C_ACK_DISABLE 1
#define I2C_ACK_ENABLE 0
#define I2C_SEND_START 1
#define I2C_NO_START 0
#define I2C_SEND_STOP 1
#define I2C_NO_STOP 0
#define I2C_SUCCESS 0
#define I2C_ARBITRATION_LOST 10
#define I2C_NACK 1
#define I2C_TIMEOUT 11

// Defines the length of time the i2c software will wait for clock stretching
// The number of attempts simply corresponds with the number of iterations
// through a for loop.
#define I2C_MAX_ATTEMPTS 1000
#define I2C_DELAY_INIT() //int _counter;
#define I2C_DELAY() for( volatile uint32_t counter = 0; counter < 1000; counter++ ) { asm volatile("mov r0, r0"); }
#define I2C_DELAY_SHORT() asm volatile("mov r0, r0")

// -----------------------------------------------------------------------------------------------
// CODE FOR BIT-BANGING THE I2C INTERFACE.
// -----------------------------------------------------------------------------------------------
// Flag to indicate that an i2c transfer has already started.
static uint8_t g_i2cStarted = 0;
/*******************************************************************************
* Function Name : i2cReset
* Input : None
* Output : None
* Return : 1 if success, 0 if fail
* Description : Resets i2c bus (used on bus errors)
*******************************************************************************/
static uint8_t i2cReadSDA( void )
  {
    // Set SDA pin to high-Z state
    HAL_GPIO_WritePin(I2C_GPIO_PORT, I2C_GPIO_SDA_PIN, GPIO_PIN_SET);
    // Return the value of the bit
    return HAL_GPIO_ReadPin( I2C_GPIO_PORT, I2C_GPIO_SDA_PIN );
  }
//-----------------------------------------------------------
static void i2cClearSDA( void )
  {
    // Pull SDA pin low
    HAL_GPIO_WritePin( I2C_GPIO_PORT, I2C_GPIO_SDA_PIN, GPIO_PIN_RESET );
  }
//-----------------------------------------------------------
static void i2cClearSCL( void )
  {
    // Pull SCL pin low
  HAL_GPIO_WritePin( I2C_GPIO_PORT, I2C_GPIO_SCL_PIN, GPIO_PIN_RESET );
  }
//-----------------------------------------------------------
static uint8_t i2cReadSCL( void )
  {
    // Set SCL pin to high-Z state
    HAL_GPIO_WritePin( I2C_GPIO_PORT, I2C_GPIO_SCL_PIN, GPIO_PIN_SET );
    // Return the value of the bit
    return HAL_GPIO_ReadPin( I2C_GPIO_PORT, I2C_GPIO_SCL_PIN );
  }
//----------------------------------------------------------
static uint8_t i2cGenerateStart( void )
  {
    int32_t attempts;
    I2C_DELAY_INIT();
    if( g_i2cStarted )
      {
        // Set SDA to 1
        i2cReadSDA();
        I2C_DELAY();
        // Handle clock stretching
        attempts = 0;
        while( (i2cReadSCL() == 0) )
          {
            attempts++;
            if( attempts > I2C_MAX_ATTEMPTS )
              {
                return I2C_TIMEOUT;
              }
          }
      }
    if( i2cReadSDA() == 0 )
      {
        // Something is pulling the SDA pin low. This shouldn't be happening.
        // Return arbitration lost.
        return I2C_ARBITRATION_LOST;
      }
    // Set SDA from 1 to 0
    i2cClearSDA();
    I2C_DELAY();
    I2C_DELAY();
    I2C_DELAY();
    I2C_DELAY();
    I2C_DELAY();
    I2C_DELAY();
    i2cClearSCL();
    // Set flag indicating that an i2c was started
    g_i2cStarted = 1;
    return I2C_SUCCESS;
  }
//-----------------------------------------------------------
static uint8_t i2cWriteBit( uint8_t value )
  {
    int32_t attempts;
    I2C_DELAY_INIT();
    if( value == I2C_BIT_SET )
      {
        i2cReadSDA();
      }
    else
      {
        i2cClearSDA();
      }
    I2C_DELAY();
    // Set SCL high and handle clock stretching
    attempts = 0;
    while( (i2cReadSCL() == 0) )
      {
        attempts++;
        if( attempts > I2C_MAX_ATTEMPTS )
          {
            return I2C_TIMEOUT;
          }
      }
// SCL is high - data should be valid
// If SDA is supposed to be high, make sure that nothing else on the bus is screwing with it
/*
if( value == I2C_BIT_SET )
{
if( i2cReadSDA() == 0 )
{
return I2C_ARBITRATION_LOST;
}
}
*/
// Delay for half the clock period after read.
      I2C_DELAY();
      // Now set SCL low
      i2cClearSCL();
      I2C_DELAY();
      return I2C_SUCCESS;
}
//---------------------------------------------------------------------
static uint8_t i2cReadBit( void )
  {
    int32_t attempts;
    uint8_t bus_data;
    I2C_DELAY_INIT();
    // Let the slave drive the data
    i2cReadSDA();
    I2C_DELAY_SHORT();
    // Handle clock stretching
    attempts = 0;
    while( (i2cReadSCL() == 0) )
      {
        attempts++;
        if( attempts > I2C_MAX_ATTEMPTS )
          {
            return I2C_TIMEOUT;
          }
      }
    // Data should be valid now
    // i2cReadSDA();
    // I2C_DELAY_SHORT();
    bus_data = i2cReadSDA();
    I2C_DELAY();
    // Set clock low
    i2cClearSCL();
    I2C_DELAY();
    return bus_data;
  }
//---------------------------------------------------------------
static uint8_t i2cGenerateStop( void )
  {
    int32_t attempts;
    I2C_DELAY_INIT();
    // Set SDA to 0
    i2cClearSDA();
    I2C_DELAY();
    // Handle clock stretching
    attempts = 0;
    while( (i2cReadSCL() == 0) )
      {
        attempts++;
        if( attempts > I2C_MAX_ATTEMPTS )
          {
            return I2C_TIMEOUT;
          }
      }
    // Set SDA from 0 to 1
    attempts = 0;
    while( (i2cReadSDA() == 0) )
      {
        attempts++;
        if( attempts > I2C_MAX_ATTEMPTS )
          {
            return I2C_ARBITRATION_LOST;
          }
      }
    I2C_DELAY();
    g_i2cStarted = 0;
    return I2C_SUCCESS;
  }
//------------------------------------------------------------------
static uint8_t i2cFailed( uint8_t status )
  {
    i2cGenerateStop();
    return status;
  }
//-----------------------------------------------------------------
static uint8_t i2cTransmitByte( uint8_t byte, uint8_t send_start, uint8_t send_stop )
  {
    uint8_t bit_index;
    uint8_t nack;
    uint8_t returnval;
    if( send_start == I2C_SEND_START )
      {
        returnval = i2cGenerateStart();
        if( returnval != I2C_SUCCESS )
          {
            return returnval;
          }
      }
    for( bit_index = 0; bit_index < 8; bit_index++ )
      {
        returnval = i2cWriteBit((byte >> 7) & 0x01);
        if( returnval != I2C_SUCCESS )
          {
            return returnval;
          }
        byte <<= 1;
      }
    nack = i2cReadBit();
    if( send_stop == I2C_SEND_STOP )
      {
        returnval = i2cGenerateStop();
        if( returnval != I2C_SUCCESS )
          {
            return returnval;
          }
      }
    return nack;
  }
//---------------------------------------------------------------------
static uint8_t i2cReadByte( uint8_t nack, uint8_t send_stop, uint8_t* status )
  {
    uint8_t byte = 0;
    uint8_t bit_index;
    uint8_t returnval;
    for( bit_index = 0; bit_index < 8; bit_index++ )
      {
        byte <<= 1;
        returnval = i2cReadBit();
        if( returnval > 1 )
          {
            *status = returnval;
            return 0;
          }
        byte |= returnval;
      }
    returnval = i2cWriteBit( nack );
    if( returnval != I2C_SUCCESS )
      {
        return returnval;
      }
    if( send_stop == I2C_SEND_STOP )
      {
        returnval = i2cGenerateStop();
        if( returnval != I2C_SUCCESS )
          {
            *status = returnval;
            return 0;
          }
      }
    *status = I2C_SUCCESS;
    return byte;
}
//---------------------------------------------------------------------
void i2cInit()
{
        I2C_GPIO_CLOCK_ENABLE();

        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.Pin = I2C_GPIO_SCL_PIN | I2C_GPIO_SDA_PIN ;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FAST ;
        HAL_GPIO_Init(I2C_GPIO_PORT, &GPIO_InitStruct);
}
//------------------------------------------------------------------
uint8_t i2cBatchWrite( uint8_t address7, uint8_t* txBuffer, uint8_t bytesToWrite )
  {
    int i;
    uint8_t returnval;
    // Send start condition and address byte
    returnval = i2cTransmitByte( (address7 | 0x00), I2C_SEND_START, I2C_NO_STOP );
    if( returnval != I2C_SUCCESS )
      {
        return i2cFailed(returnval);
      }
    // Send data bytes
    for( i = 0; i < (bytesToWrite-1); i++ )
      {
        i2cTransmitByte( txBuffer[i], I2C_NO_START, I2C_NO_STOP );
        if( returnval != I2C_SUCCESS )
          {
            return i2cFailed(returnval);
          }
      }
    // Send the final byte along with stop condition
    returnval = i2cTransmitByte( txBuffer[bytesToWrite-1], I2C_NO_START, I2C_SEND_STOP );
    return returnval;
  }
//------------------------------------------------------------------
uint8_t i2cBatchRead( uint8_t address7, uint8_t device_start_address, uint8_t* rxBuffer, uint8_t bytesToRead )
  {
    int i;
    uint8_t returnval;

    if ( device_start_address != 0xff )
      {
        // Send start condition and address byte
        returnval = i2cTransmitByte( (address7 | 0x00), I2C_SEND_START, I2C_NO_STOP );
        if( returnval != I2C_SUCCESS )
          {
            return i2cFailed(returnval);
          }
        // Send start address for read
        returnval = i2cTransmitByte( device_start_address, I2C_NO_START, I2C_NO_STOP );
        if( returnval != I2C_SUCCESS )
          {
            return i2cFailed(returnval);
          }
      }

    // Send new start condition and initiate read
    returnval = i2cTransmitByte( (address7 | 0x01), I2C_SEND_START, I2C_NO_STOP );
    if( returnval != I2C_SUCCESS )
      {
        return i2cFailed(returnval);
      }
    // Start read
    for( i = 0; i < (bytesToRead - 1); i++ )
      {
        rxBuffer[i] = i2cReadByte( I2C_ACK_ENABLE, I2C_NO_STOP, &returnval );
        if( returnval != I2C_SUCCESS )
          {
            return i2cFailed(returnval);
          }
      }
    // Read the last byte
    rxBuffer[bytesToRead - 1] = i2cReadByte( I2C_ACK_DISABLE, I2C_SEND_STOP, &returnval );
    if( returnval != I2C_SUCCESS )
      {
        return i2cFailed(returnval);
      }
    return I2C_SUCCESS;
  }
//------------------------------------------------------------------
