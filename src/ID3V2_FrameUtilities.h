////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
//
// The MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __ULTRASCHALL_ID3V2_FRAME_UTILITIES_H_INCL__
#define __ULTRASCHALL_ID3V2_FRAME_UTILITIES_H_INCL__

#include "Common.h"

#include "ID3V2_Frame.h"
#include "ID3V2_FrameData.h"

namespace ultraschall { namespace framework {

size_t DumpHeader(const uint8_t* data, const size_t dataSize);

size_t DumpExtendedHeader(const uint8_t* data, const size_t dataSize);

size_t DumpFrame(const uint8_t* data, const size_t dataSize);

typedef std::deque<ID3V2_Frame*> ID3V2_FrameQueue;
static const ID3V2_FrameQueue    ID3V2_EMPTY_FRAME_QUEUE;
static const ID3V2_FrameQueue    ID3V2_INVALID_FRAME_QUEUE;

}} // namespace ultraschall::framework

#endif // #ifndef __ULTRASCHALL_ID3V2_FRAME_UTILITIES_H_INCL__
