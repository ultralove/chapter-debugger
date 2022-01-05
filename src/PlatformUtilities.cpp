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

#include "PlatformUtilities.h"

namespace ultraschall { namespace tools { namespace chapdbg {

uint32_t _Fast_Sync_Int_Decode_32(const uint32_t value)
{
    uint32_t a, b, c, d, result = 0x0;
    a      = value & 0xFF;
    b      = (value >> 8) & 0xFF;
    c      = (value >> 16) & 0xFF;
    d      = (value >> 24) & 0xFF;

    result = result | a;
    result = result | (b << 7);
    result = result | (c << 14);
    result = result | (d << 21);

    return result;
}

uint32_t _Fast_Sync_Int_Encode_32(const uint32_t value)
{
    uint32_t in = value;
    uint32_t out, mask = 0x7F;

    while (mask ^ 0x7FFFFFFF) {
        out = in & ~mask;
        out <<= 1;
        out |= in & mask;
        mask = ((mask + 1) << 8) - 1;
        in   = out;
    }

    return out;
}

}}} // namespace ultraschall::tools::chapdbg
