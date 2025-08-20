////////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) Ultralove Contributors (https://github.com/ultralove)
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

#ifndef __FAST_ROUTINES_H_INCL__
#define __FAST_ROUTINES_H_INCL__

#include <cstdint>
#include <cstdlib>

#ifdef __MSCVER
    #define _Fast_Byte_Swap_16(x) _byteswap_ushort(x)
    #define _Fast_Byte_Swap_32(x) _byteswap_ulong(x)
    #define _Fast_Byte_Swap_64(x) _byteswap_uint64(x)
#else
    #define _Fast_Byte_Swap_16(x) __builtin_bswap16(x)
    #define _Fast_Byte_Swap_32(x) __builtin_bswap32(x)
    #define _Fast_Byte_Swap_64(x) __builtin_bswap64(x)
#endif

namespace ultralove { namespace chapdbg {
uint32_t _Fast_Unsynchronize_32(const uint32_t value);
uint32_t _Fast_Synchronize_32(const uint32_t value);

/*
 * Unicode encoding conversion functions and their macros.
 */
#define UCONV_IN_BIG_ENDIAN 0x0001
#define UCONV_OUT_BIG_ENDIAN 0x0002
#define UCONV_IN_SYSTEM_ENDIAN 0x0004
#define UCONV_OUT_SYSTEM_ENDIAN 0x0008
#define UCONV_IN_LITTLE_ENDIAN 0x0010
#define UCONV_OUT_LITTLE_ENDIAN 0x0020
#define UCONV_IGNORE_NULL 0x0040
#define UCONV_IN_ACCEPT_BOM 0x0080
#define UCONV_OUT_EMIT_BOM 0x0100

uint32_t _Fast_Conv_UTF16_To_UTF32(const uint16_t*, size_t*, uint32_t*, size_t*, int);
uint32_t _Fast_Conv_UTF16_To_UTF8(const uint16_t*, size_t*, uint8_t*, size_t*, int);
uint32_t _Fast_Conv_UTF32_To_UTF16(const uint32_t*, size_t*, uint16_t*, size_t*, int);
uint32_t _Fast_Conv_UTF32_To_UTF8(const uint32_t*, size_t*, uint8_t*, size_t*, int);
uint32_t _Fast_Conv_UTF8_To_UTF16(const uint8_t*, size_t*, uint16_t*, size_t*, int);
uint32_t _Fast_Conv_UTF8_To_UTF32(const uint8_t*, size_t*, uint32_t*, size_t*, int);
}} // namespace ultralove::chapdbg

#endif // #ifndef __FAST_ROUTINES_H_INCL__
