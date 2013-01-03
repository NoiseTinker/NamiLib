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

bool openFrameReader(FrameReader* frameReader, char* filename);

bool closeFrameReader(FrameReader* frameReader);

size_t readFrame(FrameReader* frameReader, Frame* frame);

#endif
