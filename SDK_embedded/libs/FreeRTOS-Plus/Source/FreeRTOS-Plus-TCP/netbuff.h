#ifndef __NETBUFF_ALLOC_H__
#define __NETBUFF_ALLOC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* NOTE PUBLIC API FUNCTIONS. */
BaseType_t xNetworkBuffersInitialise( void );
NetworkBufferDescriptor_t *pxGetNetworkBufferWithDescriptor( size_t xRequestedSizeBytes, TickType_t xBlockTimeTicks );
NetworkBufferDescriptor_t *pxNetworkBufferGetFromISR( size_t xRequestedSizeBytes );
void vReleaseNetworkBufferAndDescriptor( NetworkBufferDescriptor_t * const pxNetworkBuffer );
BaseType_t vNetworkBufferReleaseFromISR( NetworkBufferDescriptor_t * const pxNetworkBuffer );
uint8_t *pucGetNetworkBuffer( size_t *pxRequestedSizeBytes );
void vReleaseNetworkBuffer( uint8_t *pucEthernetBuffer );

/* Get the current number of free network buffers. */
UBaseType_t uxGetNumberOfFreeNetworkBuffers( void );

/* Get the lowest number of free network buffers. */
UBaseType_t uxGetMinimumFreeNetworkBuffers( void );

/* Copy a network buffer into a bigger buffer. */
NetworkBufferDescriptor_t *pxDuplicateNetworkBufferWithDescriptor( NetworkBufferDescriptor_t * const pxNetworkBuffer,
	BaseType_t xNewLength);

/* Increase the size of a Network Buffer.
In case BufferAllocation_2.c is used, the new space must be allocated. */
NetworkBufferDescriptor_t *pxResizeNetworkBufferWithDescriptor( NetworkBufferDescriptor_t * pxNetworkBuffer,
	size_t xNewSizeBytes );

#if ipconfigTCP_IP_SANITY
	/*
	 * Check if an address is a valid pointer to a network descriptor
	 * by looking it up in the array of network descriptors
	 */
	UBaseType_t bIsValidNetworkDescriptor (const NetworkBufferDescriptor_t * pxDesc);
	BaseType_t prvIsFreeBuffer( const NetworkBufferDescriptor_t *pxDescr );
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* __NETBUFF_ALLOC_H__ */
