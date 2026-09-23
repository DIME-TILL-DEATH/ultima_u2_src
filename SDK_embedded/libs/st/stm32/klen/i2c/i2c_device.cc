#include "i2c_device.h"


TI2CDevice::TI2CDevice ()
{
	queue = new TQueue( 1 , 0 /* ���������� ��� ������� */) ;
	request.receiver = queue ;

	write_timeout = 0 ;
	read_timeout = portMAX_DELAY ;
}

TI2CDevice::~TI2CDevice ()
{
	delete queue ;
}
//---------------------------------------------------------------------------------

TI2CDevice::TTransactionResult TI2CDevice::Transaction()
{
	// ������ ������� � ������� ���������
	if ( bus_mngr->Request( request , write_timeout ) == errQUEUE_FULL ) return trWriteTimeout ;
	// �������� ������
	return Wait() ;
}
//---------------------------------------------------------------------------------
TI2CDevice::TTransactionResult TI2CDevice::Transaction(TI2CBusManager::TI2CBusManagerRequest& request )
{
        // ������ ������� � ������� ���������
        request.receiver = this->queue ;
        if ( bus_mngr->Request( request , write_timeout ) == errQUEUE_FULL ) return trWriteTimeout ;
        // �������� ������
        return Wait() ;
}
//--------------------------------------------------------------------------------
TI2CDevice::TTransactionResult TI2CDevice::Wait()
{
        if ( queue->Receive( NULL , read_timeout )  == TQueue::qrrQueueEmpty )
          return trReadTimeout ;
        else
          return trOk ;
} ;
