/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#ifndef __FRAMEWRITER_H__
#define __FRAMEWRITER_H__

#include "Frame.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	FILE* file;
} FrameWriter;

bool openFrameWriter(FrameWriter* frameWriter, char* filename);

bool closeFrameWriter(FrameWriter* frameWriter);

size_t writeFrame(FrameWriter* frameWriter, Frame* frame);

#endif
