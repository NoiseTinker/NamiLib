/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "FrameReader.h"

bool openFrameReader(FrameReader* frameReader, char* filename)
{
	frameReader->file = fopen(filename, "r");

	return frameReader->file != NULL;
}

bool closeFrameReader(FrameReader* frameReader)
{
	return fclose(frameReader->file) == 0;
}

size_t readFrame(FrameReader* frameReader, Frame* frame)
{
	size_t samplesRead = fread(frame->data, frameSampleDataSize(frame), frame->size, frameReader->file);
	return frame->used = samplesRead;
}
