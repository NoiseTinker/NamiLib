/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#ifndef __FRAMEWRITER_H__
#define __FRAMEWRITER_H__

#include "Frame.h"

openFrameWriter(FrameWriter* frameWriter);

closeFrameWriter(FrameWriter* frameWriter);

writeFrame(FrameWriter* frameWriter, Frame* frame);

#endif

