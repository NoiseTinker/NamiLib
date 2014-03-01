/*
* Copyright 2014 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <unistd.h>

#include <stdio.h> // test

#include "FrameRecorder.h"

bool nami_open_recorder(FrameRecorder* recorder, FrameRecorderOptions options)
{
	recorder->type = options.type;

	if (recorder->type == SOCKET) {
		recorder->socket_fd = options.socket_fd;
		if (recorder->socket_fd < 0) {
			return false;
		}
	} else if (recorder->type == PORTAUDIO) {
		// open audio
	}

	return true;
}

void nami_close_recorder(FrameRecorder* recorder)
{
	if (recorder->type == SOCKET) {
		shutdown(recorder->socket_fd, SHUT_RDWR);
		close(recorder->socket_fd);
	} else if (recorder->type == PORTAUDIO) {
		// close audio
	}
}

size_t nami_record_frame(FrameRecorder* recorder, Frame* frame)
{
	if (recorder->type == SOCKET) {
		ssize_t samplesRead = read(recorder->socket_fd, frame->data, frame->size);
		if (samplesRead < 0) {
			samplesRead = 0;
		}
		return frame->used = samplesRead;
	} else if (recorder->type == PORTAUDIO) {
		// read from audio
	}

	return 0;
}
