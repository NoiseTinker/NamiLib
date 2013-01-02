/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "FrameWriter.h"

bool openFrameWriter(FrameWriter* frameWriter, char* filename)
{
	frameWriter->file = fopen(filename, "w");

	return frameWriter->file != NULL;
}

bool closeFrameWriter(FrameWriter* frameWriter)
{
	return fclose(frameWriter->file) == 0;
}

size_t writeFrame(FrameWriter* frameWriter, Frame* frame)
{
	return fwrite(frame->data, frameSampleDataSize(frame), frame->size, frameWriter->file);
}

