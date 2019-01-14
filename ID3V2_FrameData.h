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

#ifndef __ULTRASCHALL_ID3V2_FRAME_DATA_H_INCL__
#define __ULTRASCHALL_ID3V2_FRAME_DATA_H_INCL__

#include "Common.h"
#include "SequentialStream.h"
#include "ID3V2.h"

namespace ultraschall { namespace framework {

static const size_t ID3V2_INVALID_FRAME_SEQUENCE = ID3V2_INVALID_SIZE_VALUE;

class ID3V2_FrameData : public SequentialStream
{
public:
    ID3V2_FrameData(const uint8_t* data, const size_t dataSize, const size_t sequence = ID3V2_INVALID_FRAME_SEQUENCE);

    inline size_t             Sequence() const;
    inline void               Sequence(const size_t sequence);

    uint32_t                  Id() const;
    uint32_t                  Size() const;
    uint16_t                  Flags() const;
    SequentialStream* RawData() const;

    bool operator==(const ID3V2_FrameData& rhs) const;
    bool operator<(const ID3V2_FrameData& rhs) const;

private:
    size_t sequence_ = ID3V2_INVALID_FRAME_SEQUENCE;
};

inline size_t ID3V2_FrameData::Sequence() const
{
    return sequence_;
}

inline void ID3V2_FrameData::Sequence(const size_t sequence)
{
    sequence_ = sequence;
}

}} // namespace ultraschall::framework

#endif // #ifndef __ULTRASCHALL_ID3V2_FRAME_DATA_H_INCL__
