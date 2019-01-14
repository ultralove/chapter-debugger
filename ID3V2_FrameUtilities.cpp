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

#include <cstdio>
#include <algorithm>

#include "ID3V2_FrameUtilities.h"
#include "StringUtilities.h"

namespace ultraschall { namespace framework {

size_t DumpHeader(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != 0, ID3V2_INVALID_SIZE_VALUE);
    PRECONDITION_RETURN(dataSize > ID3V2_HEADER_SIZE, ID3V2_INVALID_SIZE_VALUE);

    return ID3V2_INVALID_SIZE_VALUE;
}

size_t DumpExtendedHeader(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != 0, ID3V2_INVALID_SIZE_VALUE);
    PRECONDITION_RETURN(dataSize > ID3V2_HEADER_SIZE, ID3V2_INVALID_SIZE_VALUE);

    return ID3V2_INVALID_SIZE_VALUE;
}

size_t DumpFrame(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != 0, ID3V2_INVALID_SIZE_VALUE);
    PRECONDITION_RETURN(dataSize >= ID3V2_FRAME_HEADER_SIZE, ID3V2_INVALID_SIZE_VALUE);

    static const uint32_t ID3V2_MAX_DATA_DISPLAY_SIZE = 1024;
    static const size_t   ID3V2_MAX_DATA_ROW_SIZE     = 32;

	printf("Guid:   %s\n", GUID().AsString().c_str());

	const uint32_t        id                          = ID3V2_DECODE_FRAME_ID(ID3V2_DATA_OFFSET(data, ID3V2_FRAME_ID_OFFSET), ID3V2_FRAME_ID_SIZE);
    printf("Id:     %c%c%c%c\n", ((uint8_t*)&id)[0], ((uint8_t*)&id)[1], ((uint8_t*)&id)[2], ((uint8_t*)&id)[3]);

    const uint32_t size = ID3V2_DECODE_FRAME_SIZE(ID3V2_DATA_OFFSET(data, ID3V2_FRAME_SIZE_OFFSET), ID3V2_FRAME_SIZE_SIZE);
    printf("Size:   0x%8.8x (%ld)\n", size, size);

    const uint16_t flags = ID3V2_DECODE_FRAME_FLAGS(ID3V2_DATA_OFFSET(data, ID3V2_FRAME_FLAGS_OFFSET), ID3V2_FRAME_FLAGS_SIZE);
    printf("Flags:  0x%4.4x\n", flags);

    printf("Data:\n");
    HexDump(ID3V2_DATA_OFFSET(data, ID3V2_FRAME_DATA_OFFSET), std::min(size, ID3V2_MAX_DATA_DISPLAY_SIZE), ID3V2_MAX_DATA_ROW_SIZE);

	printf("\n");

    return ID3V2_FRAME_HEADER_SIZE + size; 
}

}} // namespace ultraschall::framework

