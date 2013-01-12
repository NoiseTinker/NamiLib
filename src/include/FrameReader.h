/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#ifndef __FRAMEREADER_H__
#define __FRAMEREADER_H__

#include "Frame.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	FILE* file;
} FrameReader;

bool nami_open_reader(FrameReader* reader, char* filename);

bool nami_close_reader(FrameReader* reader);

size_t nami_read_frame(FrameReader* reader, Frame* frame);

#endif
