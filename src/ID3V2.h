////////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) ultralove contributors (https://github.com/ultralove)
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

#ifndef __ID3V2_H_INCL__
#define __ID3V2_H_INCL__

#include <stddef.h>
#include <stdint.h>

namespace ultralove { namespace tools { namespace chapdbg {

static const size_t ID3V2_INVALID_SIZE_VALUE = static_cast<size_t>(-1);
#define ID3V2_DATA_OFFSET(a, b) (&(a)[(b)])

static const size_t ID3V2_INVALID_HEADER         = ID3V2_INVALID_SIZE_VALUE;

static const uint32_t ID3V2_INVALID_FILE_ID      = 0xffffffff;
static const uint8_t ID3V2_INVALID_FILE_VERSION  = 0xff;
static const uint8_t ID3V2_INVALID_FILE_REVISION = 0xff;
static const uint8_t ID3V2_INVALID_FILE_FLAGS    = 0xff;
static const uint32_t ID3V2_INVALID_FILE_SIZE    = 0xffffffff;

static const size_t ID3V2_FILE_ID_SIZE           = sizeof(uint8_t) * 3;
static const size_t ID3V2_FILE_VERSION_SIZE      = sizeof(uint8_t);
static const size_t ID3V2_FILE_REVISION_SIZE     = sizeof(uint8_t);
static const size_t ID3V2_FILE_FLAGS_SIZE        = sizeof(uint8_t);
static const size_t ID3V2_FILE_SIZE_SIZE         = sizeof(uint32_t);

typedef struct _tagID3V2_FILE_HEADER
{
   uint8_t id[ID3V2_FILE_ID_SIZE];
   uint8_t version;
   uint8_t revision;
   uint8_t flags;
   uint32_t size;
} ID3V2_FILE_HEADER, *PID3V2_FILE_HEADER, **PPID3V2_FILE_HEADER;

static const size_t ID3V2_FILE_HEADER_SIZE =
   ID3V2_FILE_ID_SIZE + ID3V2_FILE_VERSION_SIZE + ID3V2_FILE_REVISION_SIZE + ID3V2_FILE_FLAGS_SIZE + ID3V2_FILE_SIZE_SIZE;
static const size_t ID3V2_FILE_HEADER_OFFSET   = 0;

static const size_t ID3V2_FILE_ID_OFFSET       = 0;
static const size_t ID3V2_FILE_VERSION_OFFSET  = ID3V2_FILE_ID_OFFSET + ID3V2_FILE_ID_SIZE;
static const size_t ID3V2_FILE_REVISION_OFFSET = ID3V2_FILE_VERSION_OFFSET + ID3V2_FILE_VERSION_SIZE;
static const size_t ID3V2_FILE_FLAGS_OFFSET    = ID3V2_FILE_REVISION_OFFSET + ID3V2_FILE_REVISION_SIZE;
static const size_t ID3V2_FILE_SIZE_OFFSET     = ID3V2_FILE_FLAGS_OFFSET + ID3V2_FILE_FLAGS_SIZE;
static const size_t UD3V2_FILE_DATA_OFFSET     = ID3V2_FILE_SIZE_OFFSET + ID3V2_FILE_SIZE_SIZE;

uint32_t ID3V2_DECODE_FILE_ID(const uint8_t* data, const size_t dataSize);
uint32_t ID3V2_ENCODE_FILE_ID(const uint8_t* id, uint8_t* data, const size_t dataSize);

uint8_t ID3V2_DECODE_FILE_VERSION(const uint8_t* data, const size_t dataSize);
uint8_t ID3V2_ENCODE_FILE_VERSION(const uint8_t version, uint8_t* data, const size_t dataSize);

uint8_t ID3V2_DECODE_FILE_REVISION(const uint8_t* data, const size_t dataSize);
uint8_t ID3V2_ENCODE_FILE_REVISION(const uint8_t revision, uint8_t* data, const size_t dataSize);

uint8_t ID3V2_DECODE_FILE_FLAGS(const uint8_t* data, const size_t dataSize);
uint8_t ID3V2_ENCODE_FILE_FLAGS(const uint8_t flags, const uint8_t* data, const size_t dataSize);

uint32_t ID3V2_DECODE_FILE_SIZE(const uint8_t* data, const size_t dataSize);
uint32_t ID3V2_ENCODE_FILE_SIZE(const uint32_t size, const uint8_t* data, const size_t dataSize);

size_t ID3V2_VALIDATE_FILE_HEADER(const uint8_t* data, const size_t dataSize);

static const size_t ID3V2_INVALID_FRAME         = ID3V2_INVALID_SIZE_VALUE;

static const uint32_t ID3V2_INVALID_FRAME_ID    = 0xffffffff;
static const uint32_t ID3V2_INVALID_FRAME_SIZE  = 0xffffffff;
static const uint16_t ID3V2_INVALID_FRAME_FLAGS = 0xffff;

static const size_t ID3V2_FRAME_ID_SIZE         = sizeof(uint32_t);
static const size_t ID3V2_FRAME_SIZE_SIZE       = sizeof(uint32_t);
static const size_t ID3V2_FRAME_FLAGS_SIZE      = sizeof(uint16_t);

typedef struct _tagID3V2_FRAME_HEADER
{
   uint32_t id;
   uint32_t size;
   uint16_t flags;
} ID3V2_FRAME_HEADER, *PID3V2_FRAME_HEADER, **PPID3V2_FRAME_HEADER;

typedef struct _tagID3V2_FRAME
{
   ID3V2_FRAME_HEADER header;
   uint8_t* data;
   size_t dataSize;
} ID3V2_FRAME, *PID3V2_FRAME, **PPID3V2_FRAME;

static const size_t ID3V2_FRAME_HEADER_SIZE   = ID3V2_FRAME_ID_SIZE + ID3V2_FRAME_SIZE_SIZE + ID3V2_FRAME_FLAGS_SIZE;
static const size_t ID3V2_FRAME_HEADER_OFFSET = ID3V2_FILE_HEADER_SIZE;

static const size_t ID3V2_FRAME_ID_OFFSET     = 0;
static const size_t ID3V2_FRAME_SIZE_OFFSET   = ID3V2_FRAME_ID_OFFSET + ID3V2_FRAME_ID_SIZE;
static const size_t ID3V2_FRAME_FLAGS_OFFSET  = ID3V2_FRAME_SIZE_OFFSET + ID3V2_FRAME_SIZE_SIZE;
static const size_t ID3V2_FRAME_DATA_OFFSET   = ID3V2_FRAME_FLAGS_OFFSET + ID3V2_FRAME_FLAGS_SIZE;

uint32_t ID3V2_DECODE_FRAME_ID(const uint8_t* data, const size_t dataSize);
uint32_t ID3V2_ENCODE_FRAME_ID(const uint32_t id, uint8_t* data, const size_t dataSize);

uint32_t ID3V2_DECODE_FRAME_SIZE(const uint8_t* data, const size_t dataSize);
uint32_t ID3V2_ENCODE_FRAME_SIZE(const uint32_t size, uint8_t* data, const size_t dataSize);

uint16_t ID3V2_DECODE_FRAME_FLAGS(const uint8_t* data, const size_t dataSize);
uint16_t ID3V2_ENCODE_FRAME_FLAGS(const uint16_t flags, uint8_t* data, const size_t dataSize);

size_t ID3V2_VALIDATE_FRAME_HEADER(const uint8_t* data, const size_t dataSize);

static const uint8_t ID3V2_ISO_8859_1_TEXT_ENCODING = 0x00;
static const uint8_t ID3V2_UTF_16_TEXT_ENCODING     = 0x01;
static const uint8_t ID3V2_UTF_16BE_TEXT_ENCODING   = 0x02;
static const uint8_t ID3V2_UTF_8_TEXT_ENCODING      = 0x03;
static const uint8_t ID3V2_INVALID_TEXT_ENCODING    = 0xff;

static const size_t ID3V2_TEXT_ENCODING_SIZE        = sizeof(uint8_t);
static const uint8_t ID3V2_TEXT_ENCODING_OFFSET     = 0;

static const size_t ID3V2_INVALID_TEXT_SIZE         = ID3V2_INVALID_SIZE_VALUE;
static const size_t ID3V2_TEXT_OFFSET               = ID3V2_TEXT_ENCODING_OFFSET + ID3V2_TEXT_ENCODING_SIZE;

typedef struct _tagID3V2_STRING
{
   uint8_t encoding;
   size_t dataSize;
   uint8_t* data;
} ID3V2_STRING, *PID3V2_STRING, **PPID3V2_STRING;

uint8_t ID3V2_DECODE_TEXT_ENCODING(const uint8_t* data, const size_t dataSize);
uint8_t ID3V2_ENCODE_TEXT_ENCODING(const uint8_t encoding, uint8_t* data, const size_t dataSize);

}}} // namespace ultralove::tools::chapdbg

#endif // #ifndef __ID3V2_H_INCL__
