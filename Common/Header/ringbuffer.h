#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#include <stdlib.h>
#include <stdint.h>

typedef struct
{
	uint8_t *Buffer;
	uint16_t pPushData;
	uint16_t pGetData;
	uint16_t Size;
}RingBuffer_Struct;

void RingBuffer_Init(RingBuffer_Struct *Buffer_Config,uint16_t BufferSize);
void RingBuffer_PushData(RingBuffer_Struct *Buffer_Handle,uint8_t Data);
uint8_t RingBuffer_GetData(RingBuffer_Struct *Buffer_Handle);
uint16_t RingBuffer_GetFreeSize(RingBuffer_Struct *Buffer_Handle);

#endif

