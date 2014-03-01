/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#ifndef __FRAMEREADER_H__
#define __FRAMEREADER_H__

#include "Frame.h"
#include <stdio.h>
#include <stdbool.h>

enum SourceType {
        FILE_TYPE,
        SOCKET_TYPE
};

typedef struct {
	enum SourceType type;
	/* socket input */
	int socket_fd;
	/* file input */
	char* filename;
} FrameReaderOptions;

typedef struct {
	enum SourceType type;
	/* socket input */
	int socket_fd;
	/* file input */
	FILE* file;
} FrameReader;

bool nami_open_reader(FrameReader* reader, FrameReaderOptions options);

bool nami_close_reader(FrameReader* reader);

size_t nami_read_frame(FrameReader* reader, Frame* frame);

#endif
