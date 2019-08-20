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

#ifndef __ULTRASCHALL_ID3V2_TEXT_FRAME_H_INCL__
#define __ULTRASCHALL_ID3V2_TEXT_FRAME_H_INCL__

#include "Common.h"
#include "ID3V2_Frame.h"

namespace ultraschall { namespace framework {

class ID3V2_TEXT_Frame : public ID3V2_Frame
{
public:
    virtual ~ID3V2_TEXT_Frame();

    static ID3V2_Frame* Create(const uint8_t* data, const size_t dataSize);

    virtual bool Serialize(uint8_t*& data, const size_t& dataSize) const;

    virtual bool Deserialize(const uint8_t* data, const size_t dataSize);

private:
    ID3V2_TEXT_Frame(const uint8_t* data, const size_t dataSize);

    uint8_t encoding_;
};

}} // namespace ultraschall::framework

#endif // #ifndef __ULTRASCHALL_ID3V2_TEXT_FRAME_H_INCL__
