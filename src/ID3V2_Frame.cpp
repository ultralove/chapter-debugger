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

#include "ID3V2_Frame.h"

namespace ultraschall { namespace framework {

ID3V2_Frame::ID3V2_Frame() : guid_(Guid::New()) {
}

bool ID3V2_Frame::ConfigureHeader(const uint32_t id, const uint32_t size, const uint16_t flags) 
{
    PRECONDITION_RETURN(id != ID3V2_INVALID_FRAME_ID, false);
    PRECONDITION_RETURN(size != ID3V2_INVALID_FRAME_ID, false);
    PRECONDITION_RETURN(flags != ID3V2_INVALID_FRAME_ID, false);

	PRECONDITION_RETURN(ID3V2_INVALID_FRAME_ID == id_, false);
    PRECONDITION_RETURN(ID3V2_INVALID_FRAME_SIZE == size_, false);
    PRECONDITION_RETURN(ID3V2_INVALID_FRAME_FLAGS == flags_, false);

	id_ = id;
    size_ = size;
    flags_ = flags;

	return IsValid();
}

bool ID3V2_Frame::IsValid(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != 0, false);
    PRECONDITION_RETURN(dataSize >= ID3V2_FRAME_HEADER_SIZE, false);

    // clang-format off
    const bool isConforming  = (isalnum(data[0]) != 0) && 
							   (isalnum(data[1]) != 0) && 
		                       (isalnum(data[2]) != 0) && 
							   (isalnum(data[3]) != 0);
    // clang-format on

    return isConforming;
}

bool ID3V2_Frame::IsValid() const
{
    // clang-format off
    const bool isInitialized = (id_ != ID3V2_INVALID_FRAME_ID) &
							   (size_ != ID3V2_INVALID_FRAME_SIZE) && 
		                       (flags_ != ID3V2_INVALID_FRAME_FLAGS);
    const bool isConforming  = (isalnum(((uint8_t*)&id_)[0]) != 0) && 
							   (isalnum(((uint8_t*)&id_)[1]) != 0) && 
		                       (isalnum(((uint8_t*)&id_)[2]) != 0) && 
							   (isalnum(((uint8_t*)&id_)[3]) != 0);
    // clang-format on

    return isInitialized && isConforming;
}

}} // namespace ultraschall::framework
