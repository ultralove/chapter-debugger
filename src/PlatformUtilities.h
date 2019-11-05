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

#ifndef __ULTRASCHALL_CORE_PLATFORM_UTILITIES_H_INCL__
#define __ULTRASCHALL_CORE_PLATFORM_UTILITIES_H_INCL__

namespace ultraschall {

#ifdef _MSC_VER
#define _Fast_Byte_Swap_16(x) _byteswap_ushort(x)
#define _Fast_Byte_Swap_32(x) _byteswap_ulong(x)
#define _Fast_Byte_Swap_64(x) _byteswap_uint64(x)
#else
#ifdef __GCC__
#define _Fast_Byte_Swap_16(x) __builtin_bswap16(x)
#define _Fast_Byte_Swap_32(x) __builtin_bswap32(x)
#define _Fast_Byte_Swap_64(x) __builtin_bswap64(x)
#endif // #ifdef __GCC__
#endif // #ifdef _MSC_VER

} // namespace ultraschall

#endif // #ifndef __ULTRASCHALL_CORE_PLATFORM_UTILITIES_H_INCL__
