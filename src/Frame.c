/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* A frame contain a number of PCM samples.
*/

#include "Frame.h"
#include <stdio.h>

Frame* nami_init_frame(Frame* frame, enum FrameEncoding encoding, void* data, uint16_t size)
{
	frame->encoding = encoding;
	frame->data = data;
	frame->size = size;
	frame->used = 0;

	return frame;
}

uint16_t nami_frame_size(Frame* frame)
{
	return frame->size;
}

enum FrameEncoding nami_frame_encoding(Frame* frame)
{
	return frame->encoding;
}

size_t nami_frame_sample_size(Frame* frame)
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

Frame* nami_frame_write_sample(Frame* frame, double data, uint32_t index)
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

	frame->used = index + 1;

	return frame;
}

uint8_t* nami_frame_uint8(Frame* frame)
{
	if(frame->encoding == UINT8) {
		return (uint8_t*)frame->data;
	} else {
		return NULL;
	}
}

int16_t* nami_frame_sint16(Frame* frame)
{
	if(frame->encoding == SINT16) {
		return (int16_t*)frame->data;
	} else {
		return NULL;
	}
}

float* nami_frame_float(Frame* frame)
{
	if(frame->encoding == FLOAT) {
		return (float*)frame->data;
	} else {
		return NULL;
	}
}

double* nami_frame_double(Frame* frame)
{
	if(frame->encoding == DOUBLE) {
		return (double*)frame->data;
	} else {
		return NULL;
	}
}
