/* ------------------------------------------------------------------------------
File: CHR_i2c.h
Author: CH Robotics
Version: 1.0
Description: Code for working with i2c bus
------------------------------------------------------------------------------ */
#ifndef __I2C_GPIO_H__
#define __I2C_GPIO_H__

// Software-emulated i2c function calls. Use these ones.
uint8_t i2cBatchWrite( uint8_t address7, uint8_t* txBuffer, uint8_t bytesToWrite );
uint8_t i2cBatchRead( uint8_t address7, uint8_t device_start_address, uint8_t* rxBuffer, uint8_t bytesToRead );
void    i2cInit();


#endif  /*__I2C_GPIO_H__*/
