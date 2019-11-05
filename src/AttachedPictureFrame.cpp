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

#include "AttachedPictureFrame.h"

namespace ultraschall { namespace core { namespace id3v2 {

static FrameResource<AttachedPictureFrame> registry1("APIC");

AttachedPictureFrame::~AttachedPictureFrame()
{
  SafeDeleteArray(data_);
  dataSize_ = 0;
}

Frame* AttachedPictureFrame::Create()
{
    return new AttachedPictureFrame();
}

bool AttachedPictureFrame::ConfigureData(const uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(data != nullptr, false);
    PreconditionReturn(dataSize >= ID3V2_TEXT_ENCODING_SIZE, false);
    PreconditionReturn(IsValid() == true, false);

    encoding_ = ID3V2_DECODE_TEXT_ENCODING(&data[ID3V2_TEXT_ENCODING_OFFSET], ID3V2_TEXT_ENCODING_SIZE);
    return AllocStringData(&data[ID3V2_TEXT_OFFSET], dataSize - ID3V2_TEXT_ENCODING_SIZE);
}

bool AttachedPictureFrame::AllocStringData(const uint8_t* data, const size_t dataSize) 
{
    PreconditionReturn(data != nullptr, false);
    PreconditionReturn(dataSize >= 0, false);

    bool allocated = false;

    SafeDeleteArray(data_);
    dataSize_ = 0;

    data_ = new uint8_t[dataSize + 1];
    if(data_ != nullptr)
    {
        dataSize_ = dataSize;
        memcpy(data_, data, dataSize_);
        data_[dataSize_] = 0;

        allocated = true;
    }

    return allocated;
}


}}} // namespace ultraschall::core::id3v2
