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

#include "ID3V2_FrameController.h"
#include "ID3V2_FrameUtilities.h"

namespace ultraschall { namespace framework {

size_t ID3V2_FrameController::DumpRawFrames(const SequentialStream& stream)
{
    PRECONDITION_RETURN(stream.Items() != 0, ID3V2_INVALID_SIZE_VALUE);
    PRECONDITION_RETURN(stream.ItemCount() > 0, ID3V2_INVALID_SIZE_VALUE);

    size_t offset  = ID3V2_HEADER_SIZE;
    bool   isValid = ID3V2_Frame::IsValid(stream.Items(offset), stream.ItemCount() - offset);
    while((true == isValid) && (offset < stream.ItemCount()))
    {
        offset += DumpFrame(stream.Items(offset), stream.ItemCount());
        isValid = ID3V2_Frame::IsValid(stream.Items(offset), stream.ItemCount() - offset);
    }

    return offset;
}

size_t ID3V2_FrameController::DumpFrames(const SequentialStream& stream)
{
    return -1;
}

}} // namespace ultraschall::framework
