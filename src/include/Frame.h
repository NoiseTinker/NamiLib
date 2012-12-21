/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* A frame contain a number of PCM samples.
*/

#ifndef __FRAME_H__
#define __FRAME_H__

#include <stdint.h>

typedef struct {
	double* data;
	uint16_t size;
} Frame;

Frame* initFrame(Frame* frame, double* data, uint16_t size);

uint16_t frameSize(Frame* frame);

double* frameData(Frame* frame);

#endif

