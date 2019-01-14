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

//#include <ostream>
//#include <sstream>
#include <cstdio>

#include "GUID.h"

#ifdef _WIN32
#include <windows.h>
#endif // #ifdef _WIN32

namespace ultraschall { namespace framework {

std::ostream& operator<<(std::ostream& os, const GUID& rhs)
{
    os << rhs.AsString();
    return os;
}

GUID::GUID()
{
#ifdef _WIN32
    UUID    uuid = {0};
    HRESULT hr   = UuidCreate(&uuid);
    if(SUCCEEDED(hr))
    {
        for(size_t i = 0; i < sizeof(UUID); i++)
        {
            guid_.push_back(((uint8_t*)&uuid)[i]);
        }
    }
#endif // #ifdef _WIN32
}

GUID::~GUID()
{
    guid_.clear();
}

std::string GUID::AsString() const
{
#ifdef _WIN32
    char buffer[38] = {0};
    sprintf(
        buffer, "%2.2X%2.2X%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X", guid_[0], guid_[1], guid_[2], guid_[3], guid_[4],
        guid_[5], guid_[6], guid_[7], guid_[8], guid_[9], guid_[10], guid_[11], guid_[12], guid_[13], guid_[14], guid_[15]);
    // std::ostringstream os;
    // os << guid_[0] << guid_[1] << guid_[2] << guid_[3];
    // os << "-";
    // os << guid_[4] << guid_[5];
    // os << "-";
    // os << guid_[6] << guid_[7];
    // os << "-";
    // os << guid_[8] << guid_[9];
    // os << "-";
    // os << guid_[10] << guid_[11] << guid_[12] << guid_[13] << guid_[14] << guid_[15];

    return std::string(buffer);

#endif // #ifdef _WIN32
}

}} // namespace ultraschall::framework
