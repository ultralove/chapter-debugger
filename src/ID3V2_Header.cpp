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

#include "ID3V2_Header.h"

namespace ultraschall { namespace framework {

uint32_t DECODE_ID3V2_FILE_SIZE(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != 0, ID3V2_INVALID_SIZE);
    PRECONDITION_RETURN(dataSize >= ID3V2_HEADER_SIZE, ID3V2_INVALID_SIZE);

    uint8_t buffer[4] = {0};
    buffer[0]         = ((data[0] >> 3) & 15);
    buffer[1]         = ((data[1] >> 2) & 31) | ((data[0] & 7) << 5);
    buffer[2]         = ((data[2] >> 1) & 63) | ((data[1] & 3) << 6);
    buffer[3]         = data[3] | ((data[2] & 1) << 7);

    // clang-format off
    return (uint32_t)(((uint64_t)buffer[0] << 24) | 
					  ((uint64_t)buffer[1] << 16) | 
		              ((uint64_t)buffer[2] << 8)  | 
		               (uint64_t)buffer[3]);
    // clang-format on
}

uint32_t ENCODE_ID3V2_FILE_SIZE(const uint32_t size, uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(size != ID3V2_INVALID_SIZE, ID3V2_INVALID_SIZE);
    PRECONDITION_RETURN(data != 0, ID3V2_INVALID_SIZE);
    PRECONDITION_RETURN(dataSize >= ID3V2_HEADER_SIZE, ID3V2_INVALID_SIZE);

    // FIXME
    return ID3V2_INVALID_SIZE;
}

ID3V2_Header::ID3V2_Header() {}

ID3V2_Header::ID3V2_Header(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION(data != 0);
    PRECONDITION(dataSize >= ID3V2_HEADER_SIZE);

    id_[0]    = data[0];
    id_[1]    = data[1];
    id_[2]    = data[2];
    version_  = data[3];
    revision_ = data[4];
    flags_    = data[5];
    size_     = DECODE_ID3V2_FILE_SIZE(&data[6], sizeof(uint32_t));
}

bool ID3V2_Header::IsValid() const
{
    // clang-format off
    const bool isInitialized = (id_ != ID3V2_INVALID_ID) && 
    						   (version_ != ID3V2_INVALID_VERSION) && 
    						   (revision_ != ID3V2_INVALID_REVISION) && 
    						   (flags_ != ID3V2_INVALID_FLAGS) && 
    						   (size_ != ID3V2_INVALID_SIZE);
    // clang-format on
    const bool isVersion2     = (2 == version_);
    const bool isRevision3or4 = (3 == revision_) || (4 == revision_);

    return isInitialized && isVersion2 && isRevision3or4;
}

}} // namespace ultraschall::framework
