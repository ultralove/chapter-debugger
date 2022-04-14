////////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) ultralove contributors (https://github.com/ultralove)
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

#include "CommentsFrame.h"

namespace ultralove { namespace tools { namespace chapdbg {

static FrameResource<CommentsFrame> registry1("COMM");
static FrameResource<CommentsFrame> registry2("USLT");

CommentsFrame::~CommentsFrame()
{
   SafeDeleteArray(data_);
   dataSize_ = 0;
}

Frame* CommentsFrame::Create()
{
   return new CommentsFrame();
}

bool CommentsFrame::ConfigureData(const uint8_t* data, const size_t dataSize)
{
   PRECONDITION_RETURN(data != nullptr, false);
   PRECONDITION_RETURN(dataSize >= ID3V2_TEXT_ENCODING_SIZE, false);
   PRECONDITION_RETURN(IsValid() == true, false);

   encoding_ = ID3V2_DECODE_TEXT_ENCODING(&data[ID3V2_TEXT_ENCODING_OFFSET], ID3V2_TEXT_ENCODING_SIZE);
   return AllocStringData(&data[ID3V2_TEXT_OFFSET], dataSize - ID3V2_TEXT_ENCODING_SIZE);
}

bool CommentsFrame::AllocStringData(const uint8_t* data, const size_t dataSize)
{
   PRECONDITION_RETURN(data != nullptr, false);
   PRECONDITION_RETURN(dataSize >= 0, false);

   bool allocated = false;

   SafeDeleteArray(data_);
   dataSize_ = 0;

   data_     = new uint8_t[dataSize + 1];
   if (data_ != nullptr) {
      dataSize_ = dataSize;
      memcpy(data_, data, dataSize_);
      data_[dataSize_] = 0;

      allocated        = true;
   }

   return allocated;
}

}}} // namespace ultralove::tools::chapdbg
