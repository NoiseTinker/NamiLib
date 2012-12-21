/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* A frame contain a number of PCM samples.
*/

#include "Frame.h"

Frame* initFrame(Frame* frame, double* data, uint16_t size)
{
	frame->data = data;
	frame->size = size;

	return frame;
}

uint16_t frameSize(Frame* frame)
{
	return frame->size;
}

double* frameData(Frame* frame)
{
	return frame->data;
}
