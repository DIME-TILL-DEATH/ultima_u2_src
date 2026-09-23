#ifndef __I2C_DEVICE_H__
#define __I2C_DEVICE_H__

#include "stdint.h"

#include "i2c_bus_manager.h"

class TI2CDevice
{
	public:

		typedef enum { trOk , trWriteTimeout , trReadTimeout } TTransactionResult ;


		TI2CDevice  () ;
		virtual ~TI2CDevice () ;
		void BusManager(TI2CBusManager* bus_mngr) { this->bus_mngr = bus_mngr ; }
		TI2CBusManager* BusManager() { return bus_mngr ; }

		TTransactionResult Transaction(TI2CBusManager::TI2CBusManagerRequest& request ) ;
		TTransactionResult Transaction() ;

		virtual bool Init() = 0 ;

		inline void WriteTimeout( portTickType val ) { write_timeout = val ; };
		inline portTickType WriteTimeout() { return write_timeout ; };
		inline void ReadTimeout( portTickType val ) { read_timeout = val ; };
		inline portTickType ReadTimeout() { return read_timeout ; };

	protected:
		TI2CBusManager* bus_mngr ;
		TI2CBusManager::TI2CBusManagerRequest request ;
	private:
		TTransactionResult Wait();
		TQueue* queue ;

		portTickType write_timeout ;
		portTickType read_timeout ;


};

#endif __I2C_DEVICE_H__
