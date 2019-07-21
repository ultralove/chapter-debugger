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

#ifndef __ULTRASCHALL_SEQUENTIAL_STREAM_H_INCL__
#define __ULTRASCHALL_SEQUENTIAL_STREAM_H_INCL__

#include <cstdint>

namespace ultraschall { namespace framework {

class SequentialStream
{
public:
    SequentialStream();
    SequentialStream(const uint8_t* items, const size_t itemCount);

    virtual ~SequentialStream();

    SequentialStream(const SequentialStream& rhs);
    SequentialStream& operator=(const SequentialStream& rhs);

    SequentialStream(SequentialStream&& rhs) noexcept;
    SequentialStream& operator=(SequentialStream&& rhs) noexcept;

    bool operator==(const SequentialStream& rhs) const;

    const uint8_t* Items(const size_t itemOffset = 0) const;
    size_t         ItemCount() const;
    bool           Valid() const;

    size_t        Write(const size_t itemOffset, const uint8_t* items, const size_t itemCount);
    inline size_t SequentialStream::Write(const uint8_t* items, const size_t itemCount);

    size_t        Read(const size_t itemOffset, uint8_t* items, const size_t itemCount) const;
    inline size_t SequentialStream::Read(uint8_t* items, const size_t itemCount) const;

    void Reset();

private:
    uint8_t* items_     = 0;
    size_t   itemCount_ = 0;

    void FastAllocItems(const size_t itemCount = 0);
    void FastReplaceItems(const uint8_t* items, const size_t itemCount);
};

inline size_t SequentialStream::ItemCount() const
{
    return itemCount_;
}

inline bool SequentialStream::Valid() const
{
    return (items_ != 0) && (itemCount_ > 0);
}

inline size_t SequentialStream::Write(const uint8_t* items, const size_t itemCount)
{
    return Write(0, items, itemCount);
}

inline size_t SequentialStream::Read(uint8_t* items, const size_t itemCount) const
{
    return Read(0, items, itemCount);
}

}} // namespace ultraschall::framework

#endif // #ifdef __ULTRASCHALL_SEQUENTIAL_STREAM_H_INCL__
