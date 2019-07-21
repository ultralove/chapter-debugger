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

#ifndef __ID3V2_FRAME_RESOURCE_H_INCL__
#define __ID3V2_FRAME_RESOURCE_H_INCL__

#include "ID3V2_FrameFactory.h"

namespace ultraschall { namespace framework {

template<class T> class ID3V2_FrameResource
{
public:
    ID3V2_FrameResource(const std::string& name)
    {
        PRECONDITION(name.empty() == false);

        id_                              = ID3V2_DECODE_FRAME_ID(reinterpret_cast<const uint8_t*>(name.c_str()), ID3V2_FRAME_ID_SIZE);
        ID3V2_FrameFactory& frameFactory = ID3V2_FrameFactory::Instance();
        registered_                      = frameFactory.RegisterFrame(id_, T::Create);
    }

    ~ID3V2_FrameResource()
    {
        if((id_ != ID3V2_INVALID_FRAME_ID) && (true == registered_))
        {
            ID3V2_FrameFactory& frameFactory = ID3V2_FrameFactory::Instance();
            frameFactory.UnregisterFrame(id_);
        }
    }

private:
    uint32_t id_         = ID3V2_INVALID_FRAME_ID;
    bool     registered_ = false;
};

}} // namespace ultraschall::framework

#endif // #ifndef __ID3V2_FRAME_RESOURCE_H_INCL__
