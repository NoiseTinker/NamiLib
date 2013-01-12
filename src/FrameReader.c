/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "FrameReader.h"

bool nami_open_reader(FrameReader* reader, char* filename)
{
	reader->file = fopen(filename, "r");

	return reader->file != NULL;
}

bool nami_close_reader(FrameReader* reader)
{
	return fclose(reader->file) == 0;
}

size_t nami_read_frame(FrameReader* reader, Frame* frame)
{
	size_t samplesRead = fread(frame->data, nami_frame_sample_size(frame), frame->size, reader->file);
	return frame->used = samplesRead;
}
