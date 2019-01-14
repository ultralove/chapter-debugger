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

#ifndef __ULTRASCHALL_ID3V2_H_INCL__
#define __ULTRASCHALL_ID3V2_H_INCL__

#include <cstdint>

namespace ultraschall { namespace framework {

static const size_t ID3V2_INVALID_SIZE_VALUE = static_cast<size_t>(-1);

#define ID3V2_DATA_OFFSET(a, b) (&(a)[(b)])

static const size_t ID3V2_HEADER_SIZE       = 10;




static const size_t ID3V2_FRAME_HEADER_SIZE = 10;

static const uint32_t ID3V2_INVALID_FRAME_ID    = 0xffffffff;
static const uint32_t ID3V2_INVALID_FRAME_SIZE  = 0xffffffff;
static const uint16_t ID3V2_INVALID_FRAME_FLAGS = 0xffff;

static const size_t ID3V2_FRAME_ID_SIZE    = sizeof(uint32_t);
static const size_t ID3V2_FRAME_SIZE_SIZE  = sizeof(uint32_t);
static const size_t ID3V2_FRAME_FLAGS_SIZE = sizeof(uint16_t);

static const size_t ID3V2_FRAME_ID_OFFSET    = 0;
static const size_t ID3V2_FRAME_SIZE_OFFSET  = 4;
static const size_t ID3V2_FRAME_FLAGS_OFFSET = 8;
static const size_t ID3V2_FRAME_DATA_OFFSET  = 10;

uint32_t ID3V2_DECODE_FRAME_ID(const uint8_t* data, const size_t dataSize);
uint32_t ID3V2_ENCODE_FRAME_ID(const uint32_t id, uint8_t* data, const size_t dataSize);

uint32_t ID3V2_DECODE_FRAME_SIZE(const uint8_t* data, const size_t dataSize);
uint32_t ID3V2_ENCODE_FRAME_SIZE(const uint32_t size, uint8_t* data, const size_t dataSize);

uint16_t ID3V2_DECODE_FRAME_FLAGS(const uint8_t* data, const size_t dataSize);
uint16_t ID3V2_ENCODE_FRAME_FLAGS(const uint16_t flags, uint8_t* data, const size_t dataSize);

}} // namespace ultraschall::framework

#endif // #ifndef __ULTRASCHALL_ID3V2_H_INCL__
