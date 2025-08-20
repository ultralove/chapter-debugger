////////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) Ultralove Contributors (https://github.com/ultralove)
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

#ifndef __URL_LINK_FRAME_H_INCL__
#define __URL_LINK_FRAME_H_INCL__

#include "Frame.h"
#include "FrameResource.h"

namespace ultralove { namespace tools { namespace norad {
class URLLinkFrame : public Frame
{
public:
    virtual ~URLLinkFrame();

    static Frame* Create();

    virtual bool ConfigureData(const uint8_t* data, const size_t dataSize);

private:
    uint8_t* data_     = 0;
    size_t   dataSize_ = ID3V2_INVALID_TEXT_SIZE;

    bool AllocStringData(const uint8_t* data, const size_t dataSize);
};
}}} // namespace ultralove::tools::norad

#endif // #ifndef __URL_LINK_FRAME_H_INCL__
