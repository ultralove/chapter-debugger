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

#include "ID3V2.h"
#include "Common.h"
#include "PlatformUtilities.h"

namespace ultraschall { namespace framework {

uint32_t ID3V2_DECODE_FRAME_ID(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != 0, ID3V2_INVALID_FRAME_ID);
    PRECONDITION_RETURN(dataSize >= ID3V2_FRAME_ID_SIZE, ID3V2_INVALID_FRAME_ID);

    uint32_t id = ID3V2_INVALID_FRAME_ID;

    ((uint8_t*)&id)[0] = data[0];
    ((uint8_t*)&id)[1] = data[1];
    ((uint8_t*)&id)[2] = data[2];
    ((uint8_t*)&id)[3] = data[3];

    return id;
}

uint32_t ID3V2_ENCODE_FRAME_ID(const uint32_t id, uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(id != ID3V2_INVALID_FRAME_ID, ID3V2_INVALID_FRAME_ID);
    PRECONDITION_RETURN(data != 0, ID3V2_INVALID_FRAME_ID);
    PRECONDITION_RETURN(dataSize >= ID3V2_FRAME_ID_SIZE, ID3V2_INVALID_FRAME_ID);

    uint32_t encoded = id;

    data[0] = ((uint8_t*)&encoded)[0];
    data[1] = ((uint8_t*)&encoded)[1];
    data[2] = ((uint8_t*)&encoded)[2];
    data[3] = ((uint8_t*)&encoded)[3];

    return encoded;
}

uint32_t ID3V2_DECODE_FRAME_SIZE(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != 0, ID3V2_INVALID_FRAME_ID);
    PRECONDITION_RETURN(dataSize >= ID3V2_FRAME_SIZE_SIZE, ID3V2_INVALID_FRAME_SIZE);

    uint32_t size = ID3V2_INVALID_FRAME_SIZE;

    ((uint8_t*)&size)[0] = data[0];
    ((uint8_t*)&size)[1] = data[1];
    ((uint8_t*)&size)[2] = data[2];
    ((uint8_t*)&size)[3] = data[3];

    return _Fast_Byte_Swap_32(size);
}

uint32_t ID3V2_ENCODE_FRAME_SIZE(const uint32_t size, uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(size != ID3V2_INVALID_FRAME_SIZE, ID3V2_INVALID_FRAME_SIZE);
    PRECONDITION_RETURN(data != 0, ID3V2_INVALID_FRAME_SIZE);
    PRECONDITION_RETURN(dataSize >= ID3V2_FRAME_ID_SIZE, ID3V2_INVALID_FRAME_SIZE);

    uint32_t encoded = _Fast_Byte_Swap_32(size);

    data[0] = ((uint8_t*)&encoded)[0];
    data[1] = ((uint8_t*)&encoded)[1];
    data[2] = ((uint8_t*)&encoded)[2];
    data[3] = ((uint8_t*)&encoded)[3];

    return encoded;
}

uint16_t ID3V2_DECODE_FRAME_FLAGS(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != 0, ID3V2_INVALID_FRAME_FLAGS);
    PRECONDITION_RETURN(dataSize >= ID3V2_FRAME_FLAGS_SIZE, ID3V2_INVALID_FRAME_FLAGS);

    uint16_t flags = ID3V2_INVALID_FRAME_FLAGS;

    ((uint8_t*)&flags)[0] = data[0];
    ((uint8_t*)&flags)[1] = data[1];

    return _Fast_Byte_Swap_16(flags);
}

uint16_t ID3V2_ENCODE_FRAME_FLAGS(const uint16_t flags, uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(flags != ID3V2_INVALID_FRAME_FLAGS, ID3V2_INVALID_FRAME_FLAGS);
    PRECONDITION_RETURN(data != 0, ID3V2_INVALID_FRAME_FLAGS);
    PRECONDITION_RETURN(dataSize >= ID3V2_FRAME_ID_SIZE, ID3V2_INVALID_FRAME_FLAGS);

    uint16_t encoded = _Fast_Byte_Swap_16(flags);

    data[0] = ((uint8_t*)&encoded)[0];
    data[1] = ((uint8_t*)&encoded)[1];

    return encoded;
}

}} // namespace ultraschall::framework
