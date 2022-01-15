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

#ifndef __FRAME_CONTROLLER_H_INCL__
#define __FRAME_CONTROLLER_H_INCL__

#include "BinaryStream.h"
#include "Common.h"
#include "Frame.h"

namespace ultraschall { namespace tools { namespace chapdbg {

class FrameController
{
public:
   static size_t DumpRawFrames(const BinaryStream& stream);

   FrameList ParseFrames(const BinaryStream& stream);

private:
   static bool CompareRawFrameId(const uint32_t rawFrameId, const char* frameId, const size_t frameIdSize);
   static size_t ComputeSubframeOffset(const uint8_t* data, const size_t dataSize);

   static void DumpRawHeader(const uint8_t* data, const size_t dataSize);
   static size_t DumpRawFrame(const size_t indentLevel, const uint8_t* data, const size_t dataSize);
};

}}} // namespace ultraschall::tools::chapdbg

#endif // #ifndef __FRAME_CONTROLLER_H_INCL__
