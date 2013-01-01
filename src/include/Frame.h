/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* A frame contain a number of PCM samples.
*/

#ifndef __FRAME_H__
#define __FRAME_H__

#include <stdint.h>

enum FrameEncoding {
	UINT8,
	SINT16,
	FLOAT,
	DOUBLE
};

typedef struct {
	enum FrameEncoding encoding;
	void* data;
	uint16_t size;
} Frame;

Frame* initFrame(Frame* frame, enum FrameEncoding encoding, void* data, uint16_t size);

uint16_t frameSize(Frame* frame);

enum FrameEncoding frameEncoding(Frame* frame);

Frame* writeFrameDataSample(Frame* frame, double data, uint32_t index);

uint8_t* frameUInt8Data(Frame* frame);

int16_t* frameSInt16Data(Frame* frame);

float* frameFloatData(Frame* frame);

double* frameDoubleData(Frame* frame);

#endif

