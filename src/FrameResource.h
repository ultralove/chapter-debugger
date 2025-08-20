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

#ifndef __FRAME_RESOURCE_H_INCL__
#define __FRAME_RESOURCE_H_INCL__

#include "FrameFactory.h"

namespace ultralove { namespace tools { namespace norad {
template<class T> class FrameResource
{
public:
    FrameResource(const std::string& name)
    {
        PRECONDITION(name.size() >= ID3V2_FRAME_ID_SIZE);

        id_                        = ID3V2_DECODE_FRAME_ID(reinterpret_cast<const uint8_t*>(name.c_str()), ID3V2_FRAME_ID_SIZE);
        FrameFactory& frameFactory = FrameFactory::Instance();
        registered_                = frameFactory.RegisterFrame(id_, T::Create);
    }

    ~FrameResource()
    {
        if ((id_ != ID3V2_INVALID_FRAME_ID) && (true == registered_))
        {
            FrameFactory& frameFactory = FrameFactory::Instance();
            frameFactory.UnregisterFrame(id_);
        }
    }

private:
    uint32_t id_         = ID3V2_INVALID_FRAME_ID;
    bool     registered_ = false;
};
}}} // namespace ultralove::tools::norad

#endif // #ifndef __FRAME_RESOURCE_H_INCL__
