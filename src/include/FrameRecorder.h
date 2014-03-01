/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* A recorder of PCM frames from default audio input or socket.
*/

#ifndef __FRAMERECORDER_H__
#define __FRAMERECORDER_H__

#include "Frame.h"
#include <stdbool.h>

enum SourceType {
        PORTAUDIO,
        SOCKET
};

typedef struct {
	enum SourceType type;
	/* socket input */
	int socket_fd;
	/* portaudio input */
	int sample_rate;
	int nbr_channels;
	int frame_size;
} FrameRecorderOptions;

typedef struct {
	enum SourceType type;
	/* socket input */
	int socket_fd;
} FrameRecorder;

bool nami_open_recorder(FrameRecorder* recorder, FrameRecorderOptions options);

void nami_close_recorder(FrameRecorder* recorder);

size_t nami_record_frame(FrameRecorder* recorder, Frame* frame);

#endif
