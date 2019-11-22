/* Includes ------------------------------------------------------------------*/
#include <assert.h>
#include "ring_buffer.h"
#include <stdint.h>


bool RingBuffer_Init(RingBuffer* ringBuffer, char* dataBuffer, size_t dataBufferSize){
	assert(ringBuffer);
	assert(dataBuffer);
	assert(dataBufferSize > 0);
    // if arguments are correct,
	if ((ringBuffer) && (dataBuffer) && (dataBufferSize > 0)) {
        ringBuffer->dataBufferSize = dataBufferSize;
        ringBuffer->head = -1;
        ringBuffer->tail = -1;
        ringBuffer->dataBuffer = dataBuffer;
	  return true;
	}
	return false;
}

bool RingBuffer_Clear(RingBuffer* ringBuffer){
	assert(ringBuffer);

	if (ringBuffer) {
		ringBuffer->head = -1;
		ringBuffer->tail = -1;
		return true;
	}
	return false;
}

bool RingBuffer_IsEmpty(const RingBuffer* ringBuffer){
  assert(ringBuffer);
	if(ringBuffer->head == -1 && ringBuffer->tail == -1){
        return true;
	}
	return false;
}

bool RingBuffer_IsFull(const RingBuffer* ringBuffer){
  assert(ringBuffer);
    if(ringBuffer->head == ((ringBuffer->tail+1) % ringBuffer->dataBufferSize)){
        return true;
    }
	return false;
}

size_t RingBuffer_GetLen(const RingBuffer* ringBuffer){
	assert(ringBuffer);
	if (ringBuffer) {
        if(RingBuffer_IsEmpty(ringBuffer)){
            return 0;
        }else if(ringBuffer->tail >= ringBuffer->head){
            return (ringBuffer->tail - ringBuffer->head)+1;
        }else{
            return (ringBuffer->dataBufferSize +1 + ringBuffer->tail - ringBuffer->head);
        }
	}
	return 0;
}

size_t RingBuffer_GetCapacity(const RingBuffer *ringBuffer){
	assert(ringBuffer);
	if (ringBuffer) {
		return ringBuffer->dataBufferSize;
	}
	return 0;
}

bool RingBuffer_PutChar(RingBuffer* ringBuffer, char c){
	assert(ringBuffer);
	if (ringBuffer) {
	    if(RingBuffer_IsFull(ringBuffer)){
            return false;
	    }
        if(RingBuffer_IsEmpty(ringBuffer)){
            ringBuffer->head = 0;
        }
        ringBuffer->tail = ((ringBuffer->tail + 1) %  ringBuffer->dataBufferSize);
        ringBuffer->dataBuffer[ringBuffer->tail] = c;
        return true;
    }
	return false;
}

bool RingBuffer_GetChar(RingBuffer* ringBuffer, char* c){

	assert(ringBuffer);
	assert(c);

  if ((ringBuffer) && (c)) {
    if(RingBuffer_IsEmpty(ringBuffer)){
            return false;
        }
        if(RingBuffer_GetLen(ringBuffer) == 1){
            *c = ringBuffer->dataBuffer[ringBuffer->head];
            RingBuffer_Clear(ringBuffer);
        }else{
            *c = ringBuffer->dataBuffer[ringBuffer->head];
            ringBuffer->head = (ringBuffer->head + 1) % ringBuffer->dataBufferSize;
        }
        return true;
	}
	return false;
}


