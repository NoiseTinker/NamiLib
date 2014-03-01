/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <unistd.h>

#include "FrameReader.h"

bool nami_open_reader(FrameReader* reader, FrameReaderOptions options)
{
	reader->type = options.type;

	if (reader->type == SOCKET_TYPE) {
		reader->socket_fd = options.socket_fd;
		if (reader->socket_fd >= 0) {
			return true;
		}
	} else if (reader->type == FILE_TYPE) {
		reader->file = fopen(options.filename, "r");
		return reader->file != NULL;
	}

	return false;
}

bool nami_close_reader(FrameReader* reader)
{
	if (reader->type == SOCKET_TYPE) {
		shutdown(reader->socket_fd, SHUT_RDWR);
		return close(reader->socket_fd);
	} else if (reader->type == FILE_TYPE) {
		return fclose(reader->file) == 0;
	}

	return false;
}

size_t nami_read_frame(FrameReader* reader, Frame* frame)
{
	if (reader->type == SOCKET_TYPE) {
		ssize_t samplesRead = read(reader->socket_fd, frame->data, frame->size);
		if (samplesRead < 0) {
			samplesRead = 0;
		}
		return frame->used = samplesRead;
	} else if (reader->type == FILE_TYPE) {
		size_t samplesRead = fread(frame->data, nami_frame_sample_size(frame), frame->size, reader->file);
		return frame->used = samplesRead;
	}

	return 0;
}
