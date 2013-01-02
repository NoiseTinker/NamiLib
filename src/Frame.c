/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* A frame contain a number of PCM samples.
*/

#include "Frame.h"
#include <stdio.h>

Frame* initFrame(Frame* frame, enum FrameEncoding encoding, void* data, uint16_t size)
{
	frame->encoding = encoding;
	frame->data = data;
	frame->size = size;

	return frame;
}

uint16_t frameSize(Frame* frame)
{
	return frame->size;
}

enum FrameEncoding frameEncoding(Frame* frame)
{
	return frame->encoding;
}

size_t frameSampleDataSize(Frame* frame)
{
	size_t size;

	switch (frame->encoding) {

		case UINT8:
		size = sizeof(uint8_t);
		break;
		case SINT16:
		size = sizeof(int16_t);
		break;
		case FLOAT:
		size = sizeof(float);
		break;
		case DOUBLE:
		size = sizeof(double);
		break;
		default:
		size = 0;
		break;
	}

	return size;
}

Frame* writeFrameDataSample(Frame* frame, double data, uint32_t index)
{

	switch (frame->encoding) {

		case UINT8:
		((uint8_t*)frame->data)[index] = 0.5 * (data + 1) * UINT8_MAX;
		break;
		case SINT16:
		((int16_t*)frame->data)[index] = data * INT16_MAX;
		break;
		case FLOAT:
		((float*)frame->data)[index] = data;
		break;
		case DOUBLE:
		((double*)frame->data)[index] = data;
		break;
		default:
		break;
	}

	return frame;
}

uint8_t* frameUInt8Data(Frame* frame)
{
	if(frame->encoding == UINT8) {
		return (uint8_t*)frame->data;
	} else {
		return NULL;
	}
}

int16_t* frameSInt16Data(Frame* frame)
{
	if(frame->encoding == SINT16) {
		return (int16_t*)frame->data;
	} else {
		return NULL;
	}
}

float* frameFloatData(Frame* frame)
{
	if(frame->encoding == FLOAT) {
		return (float*)frame->data;
	} else {
		return NULL;
	}
}

double* frameDoubleData(Frame* frame)
{
	if(frame->encoding == DOUBLE) {
		return (double*)frame->data;
	} else {
		return NULL;
	}
}
