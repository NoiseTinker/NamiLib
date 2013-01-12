/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "FrameWriter.h"

bool nami_open_writer(FrameWriter* writer, char* filename)
{
	writer->file = fopen(filename, "w");

	return writer->file != NULL;
}

bool nami_close_writer(FrameWriter* writer)
{
	return fclose(writer->file) == 0;
}

size_t nami_write_frame(FrameWriter* writer, Frame* frame)
{
	return fwrite(frame->data, nami_frame_sample_size(frame), frame->used, writer->file);
}

