/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* A frame contain a number of PCM samples.
*/

#ifndef __FRAME_H__
#define __FRAME_H__

#include <stdint.h>
#include <stddef.h>

enum FrameEncoding {
	UINT8,
	SINT16,
	FLOAT,
	DOUBLE
};

typedef struct {
	enum FrameEncoding encoding;
	void* data;
	size_t size;
	size_t used;
} Frame;

Frame* nami_init_frame(Frame* frame, enum FrameEncoding encoding, void* data, size_t size);

uint16_t nami_frame_size(Frame* frame);

enum FrameEncoding nami_frame_encoding(Frame* frame);

size_t nami_frame_sample_size(Frame* frame);

Frame* nami_frame_write_sample(Frame* frame, double data, size_t index);

uint8_t* nami_frame_uint8(Frame* frame);

int16_t* nami_frame_sint16(Frame* frame);

float* nami_frame_float(Frame* frame);

double* nami_frame_double(Frame* frame);

#endif

