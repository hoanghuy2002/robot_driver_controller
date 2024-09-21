#include "ringbuffer.h"


void RingBuffer_Init(RingBuffer_Struct *Buffer_Config,uint16_t BufferSize)
{
	Buffer_Config->Buffer = (uint8_t *)malloc(BufferSize);
	Buffer_Config->pPushData = 0;
	Buffer_Config->pGetData = 0;
	Buffer_Config->Size = BufferSize;
}

void RingBuffer_PushData(RingBuffer_Struct *Buffer_Handle,uint8_t Data)
{
	Buffer_Handle->Buffer[Buffer_Handle->pPushData] = Data;
	Buffer_Handle->pPushData++;
	Buffer_Handle->pPushData %= Buffer_Handle->Size;
}

uint8_t RingBuffer_GetData(RingBuffer_Struct *Buffer_Handle)
{
	uint8_t Data =0;
	if(Buffer_Handle->pGetData < Buffer_Handle->pPushData)
	{
		Data = Buffer_Handle->Buffer[Buffer_Handle->pGetData];
		Buffer_Handle->pGetData++;
		Buffer_Handle->pGetData %= Buffer_Handle->Size;
	}
	return Data;
}

uint16_t RingBuffer_GetFreeSize(RingBuffer_Struct *Buffer_Handle)
{
	uint16_t Data = (Buffer_Handle->Size - 1 - Buffer_Handle->pPushData) + (Buffer_Handle->pGetData);
	return Data;
}

