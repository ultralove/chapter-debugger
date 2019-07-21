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

#include "ID3V2_COMM_Frame.h"
#include "ID3V2_FrameResource.h"

namespace ultraschall { namespace framework {

static ID3V2_FrameResource<ID3V2_COMM_Frame> resource("COMM");

ID3V2_COMM_Frame::ID3V2_COMM_Frame() {}

ID3V2_COMM_Frame::~ID3V2_COMM_Frame() {}

ID3V2_Frame* ID3V2_COMM_Frame::Create()
{
    ID3V2_FRAME_FACTORY_ENTRY();
    return new ID3V2_COMM_Frame();
    ID3V2_FRAME_FACTORY_EXIT();
}

size_t ID3V2_COMM_Frame::Decode(const uint8_t* data, const size_t dataSize)
{
    return ID3V2_INVALID_SIZE_VALUE;
}

size_t ID3V2_COMM_Frame::Encode(uint8_t* data, const size_t dataSize) const
{
    return ID3V2_INVALID_SIZE_VALUE;
}

}} // namespace ultraschall::framework
