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

#include "ID3V2_FrameData.h"
#include "ID3V2_Frame.h"

namespace ultraschall { namespace framework {

ID3V2_FrameData::ID3V2_FrameData(const uint8_t* data, const size_t dataSize, const size_t sequence) :
    SequentialStream(data, dataSize), sequence_(sequence)
{}

bool ID3V2_FrameData::operator==(const ID3V2_FrameData& rhs) const
{
    return SequentialStream::operator==(rhs) && (sequence_ == rhs.sequence_);
}

bool ID3V2_FrameData::operator<(const ID3V2_FrameData& rhs) const
{
    return sequence_ < rhs.sequence_;
}

uint32_t ID3V2_FrameData::Id() const
{
    PRECONDITION_RETURN(Items() != 0, ID3V2_INVALID_FRAME_ID);
    PRECONDITION_RETURN(ItemCount() >= (ID3V2_FRAME_ID_OFFSET + ID3V2_FRAME_ID_SIZE), ID3V2_INVALID_FRAME_ID);

    uint32_t id = ID3V2_INVALID_FRAME_ID;

    const size_t dataSize       = ID3V2_FRAME_ID_SIZE;
    uint8_t      data[dataSize] = {0};
    if(Read(ID3V2_FRAME_ID_OFFSET, data, dataSize) == dataSize)
    {
        id = ID3V2_DECODE_FRAME_ID(data, dataSize);
    }

    return id;
}

uint32_t ID3V2_FrameData::Size() const
{
    PRECONDITION_RETURN(Items() != 0, ID3V2_INVALID_FRAME_SIZE);
    PRECONDITION_RETURN(ItemCount() >= (ID3V2_FRAME_SIZE_OFFSET + ID3V2_FRAME_SIZE_SIZE), ID3V2_INVALID_FRAME_SIZE);

    uint32_t size = ID3V2_INVALID_FRAME_SIZE;

    const size_t dataSize       = ID3V2_FRAME_SIZE_SIZE;
    uint8_t      data[dataSize] = {0};
    if(Read(ID3V2_FRAME_SIZE_OFFSET, data, dataSize) == dataSize)
    {
        size = ID3V2_DECODE_FRAME_SIZE(data, dataSize);
    }

    return size;
}

uint16_t ID3V2_FrameData::Flags() const
{
    PRECONDITION_RETURN(Items() != 0, ID3V2_INVALID_FRAME_FLAGS);
    PRECONDITION_RETURN(ItemCount() >= (ID3V2_FRAME_FLAGS_OFFSET + ID3V2_FRAME_FLAGS_SIZE), ID3V2_INVALID_FRAME_FLAGS);

    uint16_t flags = ID3V2_INVALID_FRAME_FLAGS;

    const size_t dataSize       = ID3V2_FRAME_FLAGS_SIZE;
    uint8_t      data[dataSize] = {0};
    if(Read(ID3V2_FRAME_FLAGS_OFFSET, data, dataSize) == dataSize)
    {
        flags = ID3V2_DECODE_FRAME_FLAGS(data, dataSize);
    }

    return flags;
}

SequentialStream* ID3V2_FrameData::RawData() const
{
    PRECONDITION_RETURN(Items() != 0, 0);
    PRECONDITION_RETURN(ItemCount() > (ID3V2_FRAME_FLAGS_OFFSET + ID3V2_FRAME_FLAGS_SIZE), 0);

    const size_t dataSize = Size(); // just call this once
    PRECONDITION_RETURN(dataSize != ID3V2_INVALID_FRAME_SIZE, 0);
    PRECONDITION_RETURN(dataSize > 0, 0);

    const uint8_t* data = Items();
    return new SequentialStream(&data[ID3V2_FRAME_DATA_OFFSET], dataSize);
}

}} // namespace ultraschall::framework
