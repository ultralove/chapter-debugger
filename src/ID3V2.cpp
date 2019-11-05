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

namespace ultraschall { namespace core { namespace id3v2 {

uint32_t ID3V2_DECODE_FILE_ID(const uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(data != 0, ID3V2_INVALID_FILE_ID);
    PreconditionReturn(dataSize >= ID3V2_FILE_HEADER_SIZE, ID3V2_INVALID_FILE_ID);

    uint32_t id = ID3V2_INVALID_FILE_ID;

    ((uint8_t*)&id)[0] = data[ID3V2_FILE_ID_OFFSET];
    ((uint8_t*)&id)[1] = data[ID3V2_FILE_ID_OFFSET + 1];
    ((uint8_t*)&id)[2] = data[ID3V2_FILE_ID_OFFSET + 2];

    return id;
}

uint32_t ID3V2_ENCODE_FILE_ID(const uint8_t* id, const uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(id != 0, ID3V2_INVALID_FILE_ID);
    PreconditionReturn(data != 0, ID3V2_INVALID_FILE_ID);
    PreconditionReturn(dataSize >= ID3V2_FILE_HEADER_SIZE, ID3V2_INVALID_FILE_ID);

    uint32_t encodedId = ID3V2_INVALID_FILE_ID;

    ((uint8_t*)&encodedId)[0] = id[ID3V2_FILE_ID_OFFSET];
    ((uint8_t*)&encodedId)[1] = id[ID3V2_FILE_ID_OFFSET + 1];
    ((uint8_t*)&encodedId)[2] = id[ID3V2_FILE_ID_OFFSET + 2];

    return encodedId;
}

uint8_t ID3V2_DECODE_FILE_VERSION(const uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(data != 0, ID3V2_INVALID_FILE_VERSION);
    PreconditionReturn(dataSize >= ID3V2_FILE_HEADER_SIZE, ID3V2_INVALID_FILE_VERSION);

    return data[ID3V2_FILE_VERSION_OFFSET];
}

uint8_t ID3V2_ENCODE_FILE_VERSION(const uint8_t version, uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(version != ID3V2_INVALID_FILE_VERSION, ID3V2_INVALID_FILE_VERSION);
    PreconditionReturn(data != 0, ID3V2_INVALID_FILE_VERSION);
    PreconditionReturn(dataSize >= ID3V2_FILE_HEADER_SIZE, ID3V2_INVALID_FILE_VERSION);

    data[ID3V2_FILE_VERSION_OFFSET] = version;

    return data[ID3V2_FILE_VERSION_OFFSET];
}

uint8_t ID3V2_DECODE_FILE_REVISION(const uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(data != 0, ID3V2_INVALID_FILE_REVISION);
    PreconditionReturn(dataSize >= ID3V2_FILE_HEADER_SIZE, ID3V2_INVALID_FILE_REVISION);

    return data[ID3V2_FILE_REVISION_OFFSET];
}

uint8_t ID3V2_ENCODE_FILE_REVISION(const uint8_t revision, uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(revision != ID3V2_INVALID_FILE_REVISION, ID3V2_INVALID_FILE_REVISION);
    PreconditionReturn(data != 0, ID3V2_INVALID_FILE_REVISION);
    PreconditionReturn(dataSize >= ID3V2_FILE_HEADER_SIZE, ID3V2_INVALID_FILE_REVISION);

    data[ID3V2_FILE_REVISION_OFFSET] = revision;

    return data[ID3V2_FILE_REVISION_OFFSET];
}

uint8_t ID3V2_DECODE_FILE_FLAGS(const uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(data != 0, ID3V2_INVALID_FILE_FLAGS);
    PreconditionReturn(dataSize >= ID3V2_FILE_HEADER_SIZE, ID3V2_INVALID_FILE_FLAGS);

    return data[ID3V2_FILE_FLAGS_OFFSET];
}

uint8_t ID3V2_ENCODE_FILE_FLAGS(const uint8_t flags, uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(flags != ID3V2_INVALID_FILE_FLAGS, ID3V2_INVALID_FILE_FLAGS);
    PreconditionReturn(data != 0, ID3V2_INVALID_FILE_FLAGS);
    PreconditionReturn(dataSize >= ID3V2_FILE_HEADER_SIZE, ID3V2_INVALID_FILE_FLAGS);

    data[ID3V2_FILE_FLAGS_OFFSET] = flags;

    return data[ID3V2_FILE_FLAGS_OFFSET];
}

uint32_t ID3V2_DECODE_FILE_SIZE(const uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(data != 0, ID3V2_INVALID_FILE_SIZE);
    PreconditionReturn(dataSize >= ID3V2_FILE_HEADER_SIZE, ID3V2_INVALID_FILE_SIZE);

    uint8_t encodedSize[4] = {0};
    encodedSize[0]         = ((data[0] >> 3) & 15);
    encodedSize[1]         = ((data[1] >> 2) & 31) | ((data[0] & 7) << 5);
    encodedSize[2]         = ((data[2] >> 1) & 63) | ((data[1] & 3) << 6);
    encodedSize[3]         = data[3] | ((data[2] & 1) << 7);

    return (uint32_t)(
        ((uint64_t)encodedSize[0] << 24) | ((uint64_t)encodedSize[1] << 16) | ((uint64_t)encodedSize[2] << 8)
        | (uint64_t)encodedSize[3]);
}

uint32_t ID3V2_ENCODE_FILE_SIZE(const uint32_t size, uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(size != ID3V2_INVALID_FILE_SIZE, ID3V2_INVALID_FILE_SIZE);
    PreconditionReturn(data != 0, ID3V2_INVALID_FILE_SIZE);
    PreconditionReturn(dataSize >= ID3V2_FILE_HEADER_SIZE, ID3V2_INVALID_FILE_SIZE);

    // FIXME
    return ID3V2_INVALID_FILE_SIZE;
}

//int syncint_encode(int value)
//{
//    int out, mask = 0x7F;
//
//    while(mask ^ 0x7FFFFFFF)
//    {
//        out = value & ~mask;
//        out <<= 1;
//        out |= value & mask;
//        mask  = ((mask + 1) << 8) - 1;
//        value = out;
//    }
//
//    return out;
//}
//
//int syncint_decode(int value)
//{
//    unsigned int a, b, c, d, result = 0x0;
//    a = value & 0xFF;
//    b = (value >> 8) & 0xFF;
//    c = (value >> 16) & 0xFF;
//    d = (value >> 24) & 0xFF;
//
//    result = result | a;
//    result = result | (b << 7);
//    result = result | (c << 14);
//    result = result | (d << 21);
//
//    return result;
//}

size_t ID3V2_VALIDATE_FILE_HEADER(const uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(data != 0, ID3V2_INVALID_HEADER);
    PreconditionReturn(dataSize >= ID3V2_FILE_HEADER_SIZE, ID3V2_INVALID_HEADER);

    size_t validBytes = ID3V2_INVALID_HEADER;

    const uint32_t id = ID3V2_DECODE_FILE_ID(data, dataSize);
    if(id != ID3V2_INVALID_FILE_ID)
    {
        const uint32_t version = ID3V2_DECODE_FILE_VERSION(data, dataSize);
        if(version != ID3V2_INVALID_FILE_VERSION)
        {
            const uint32_t revision = ID3V2_DECODE_FILE_REVISION(data, dataSize);
            if(revision != ID3V2_INVALID_FILE_REVISION)
            {
                const uint32_t flags = ID3V2_DECODE_FILE_FLAGS(data, dataSize);
                if(flags != ID3V2_INVALID_FILE_FLAGS)
                {
                    const uint32_t size = ID3V2_DECODE_FILE_SIZE(data, dataSize);
                    if(size != ID3V2_INVALID_FILE_SIZE)
                    {
                        validBytes = ID3V2_FILE_HEADER_SIZE;
                    }
                }
                else
                {
                    validBytes = ID3V2_FILE_FLAGS_OFFSET;
                }
            }
            else
            {
                validBytes = ID3V2_FILE_REVISION_OFFSET;
            }
        }
        else
        {
            validBytes = ID3V2_FILE_VERSION_OFFSET;
        }
    }
    else
    {
        validBytes = ID3V2_FILE_ID_OFFSET;
    }

    return validBytes;
}

uint32_t ID3V2_DECODE_FRAME_ID(const uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(data != 0, ID3V2_INVALID_FRAME_ID);
    PreconditionReturn(dataSize >= ID3V2_FRAME_ID_SIZE, ID3V2_INVALID_FRAME_ID);

    uint32_t id = ID3V2_INVALID_FRAME_ID;

    ((uint8_t*)&id)[0] = data[0];
    ((uint8_t*)&id)[1] = data[1];
    ((uint8_t*)&id)[2] = data[2];
    ((uint8_t*)&id)[3] = data[3];

    return id;
}

uint32_t ID3V2_ENCODE_FRAME_ID(const uint32_t id, uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(id != ID3V2_INVALID_FRAME_ID, ID3V2_INVALID_FRAME_ID);
    PreconditionReturn(data != 0, ID3V2_INVALID_FRAME_ID);
    PreconditionReturn(dataSize >= ID3V2_FRAME_ID_SIZE, ID3V2_INVALID_FRAME_ID);

    uint32_t encodedId = id;

    data[0] = ((uint8_t*)&encodedId)[0];
    data[1] = ((uint8_t*)&encodedId)[1];
    data[2] = ((uint8_t*)&encodedId)[2];
    data[3] = ((uint8_t*)&encodedId)[3];

    return encodedId;
}

uint32_t ID3V2_DECODE_FRAME_SIZE(const uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(data != 0, ID3V2_INVALID_FRAME_SIZE);
    PreconditionReturn(dataSize >= ID3V2_FRAME_SIZE_SIZE, ID3V2_INVALID_FRAME_SIZE);

    uint32_t size = ID3V2_INVALID_FRAME_SIZE;

    ((uint8_t*)&size)[0] = data[0];
    ((uint8_t*)&size)[1] = data[1];
    ((uint8_t*)&size)[2] = data[2];
    ((uint8_t*)&size)[3] = data[3];

    return _Fast_Byte_Swap_32(size);
}

uint32_t ID3V2_ENCODE_FRAME_SIZE(const uint32_t size, uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(size != ID3V2_INVALID_FRAME_SIZE, ID3V2_INVALID_FRAME_SIZE);
    PreconditionReturn(data != 0, ID3V2_INVALID_FRAME_SIZE);
    PreconditionReturn(dataSize >= ID3V2_FRAME_ID_SIZE, ID3V2_INVALID_FRAME_SIZE);

    uint32_t encodedSize = _Fast_Byte_Swap_32(size);

    data[0] = ((uint8_t*)&encodedSize)[0];
    data[1] = ((uint8_t*)&encodedSize)[1];
    data[2] = ((uint8_t*)&encodedSize)[2];
    data[3] = ((uint8_t*)&encodedSize)[3];

    return encodedSize;
}

uint16_t ID3V2_DECODE_FRAME_FLAGS(const uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(data != 0, ID3V2_INVALID_FRAME_FLAGS);
    PreconditionReturn(dataSize >= ID3V2_FRAME_FLAGS_SIZE, ID3V2_INVALID_FRAME_FLAGS);

    uint16_t flags = ID3V2_INVALID_FRAME_FLAGS;

    ((uint8_t*)&flags)[0] = data[0];
    ((uint8_t*)&flags)[1] = data[1];

    return _Fast_Byte_Swap_16(flags);
}

uint16_t ID3V2_ENCODE_FRAME_FLAGS(const uint16_t flags, uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(flags != ID3V2_INVALID_FRAME_FLAGS, ID3V2_INVALID_FRAME_FLAGS);
    PreconditionReturn(data != 0, ID3V2_INVALID_FRAME_FLAGS);
    PreconditionReturn(dataSize >= ID3V2_FRAME_ID_SIZE, ID3V2_INVALID_FRAME_FLAGS);

    uint16_t encodedFlags = _Fast_Byte_Swap_16(flags);

    data[0] = ((uint8_t*)&encodedFlags)[0];
    data[1] = ((uint8_t*)&encodedFlags)[1];

    return encodedFlags;
}

size_t ID3V2_VALIDATE_FRAME_HEADER(const uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(data != 0, ID3V2_INVALID_FRAME);
    PreconditionReturn(dataSize >= ID3V2_FRAME_HEADER_SIZE, ID3V2_INVALID_FRAME);

    size_t validBytes = ID3V2_INVALID_FRAME;

    const uint32_t id = ID3V2_DECODE_FRAME_ID(data, dataSize);
    if(id != ID3V2_INVALID_FRAME_ID)
    {
        const uint32_t size = ID3V2_DECODE_FRAME_SIZE(data, dataSize);
        if(size != ID3V2_INVALID_FRAME_SIZE)
        {
            const uint16_t flags = ID3V2_DECODE_FRAME_FLAGS(data, dataSize);
            if(flags != ID3V2_INVALID_FRAME_FLAGS)
            {
                validBytes = ID3V2_FRAME_HEADER_SIZE;
            }
        }
        else
        {
            validBytes = ID3V2_FRAME_SIZE_OFFSET;
        }
    }
    else
    {
        validBytes = ID3V2_FRAME_ID_OFFSET;
    }

    return validBytes;
}

uint8_t ID3V2_DECODE_TEXT_ENCODING(const uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(data != nullptr, ID3V2_INVALID_TEXT_ENCODING);
    PreconditionReturn(
        dataSize >= (ID3V2_TEXT_ENCODING_OFFSET + ID3V2_TEXT_ENCODING_SIZE), ID3V2_INVALID_TEXT_ENCODING);

    return data[ID3V2_TEXT_ENCODING_OFFSET];
}

uint8_t ID3V2_DECODE_TEXT_ENCODING (const uint8_t encoding, uint8_t* data, const size_t dataSize) {
    PreconditionReturn(encoding != ID3V2_INVALID_TEXT_ENCODING, ID3V2_INVALID_TEXT_ENCODING);
    PreconditionReturn(data != nullptr, ID3V2_INVALID_TEXT_ENCODING);
    PreconditionReturn(
        dataSize >= (ID3V2_TEXT_ENCODING_OFFSET + ID3V2_TEXT_ENCODING_SIZE), ID3V2_INVALID_TEXT_ENCODING);

    data[ID3V2_TEXT_ENCODING_OFFSET] = encoding;

    return data[ID3V2_TEXT_ENCODING_OFFSET];
}

}}} // namespace ultraschall::core::id3v2
