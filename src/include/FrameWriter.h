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

bool nami_open_writer(FrameWriter* writer, char* filename);

bool nami_close_writer(FrameWriter* writer);

size_t nami_write_frame(FrameWriter* writer, Frame* frame);

#endif
