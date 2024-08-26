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

#include "FastRoutines.h"

#include <sys/errno.h>

namespace ultralove { namespace tools { namespace norad {

uint32_t _Fast_Unsynchronize_32(const uint32_t value)
{
   uint32_t result = 0;

   uint32_t first  = value & 0xFF;
   uint32_t second = (value >> 8) & 0xFF;
   uint32_t third  = (value >> 16) & 0xFF;
   uint32_t fourth = (value >> 24) & 0xFF;
   result          = result | first;
   result          = result | (second << 7);
   result          = result | (third << 14);
   result          = result | (fourth << 21);

   return result;
}

uint32_t _Fast_Synchronize_32(const uint32_t value)
{
   uint32_t result = 0;

   uint32_t valueBuffer = value;
   uint32_t valueMask   = 0x7F;

   while (valueMask ^ 0x7FFF'FFFF)
   {
      result = valueBuffer & ~valueMask;
      result <<= 1;
      result |= valueBuffer & valueMask;
      valueMask   = ((valueMask + 1) << 8) - 1;
      valueBuffer = result;
   }

   return result;
}

/*
 * The max and min values of high and low surrogate pairs of UTF-16,
 * UTF-16 bit shift value, bit mask, and starting value outside of BMP.
 */
#define UCONV_U16_HI_MIN       (0xd800U)
#define UCONV_U16_HI_MAX       (0xdbffU)
#define UCONV_U16_LO_MIN       (0xdc00U)
#define UCONV_U16_LO_MAX       (0xdfffU)
#define UCONV_U16_BIT_SHIFT    (0x0400U)
#define UCONV_U16_BIT_MASK     (0x0f'ffffU)
#define UCONV_U16_START        (0x01'0000U)

/* The maximum value of Unicode coding space and ASCII coding space. */
#define UCONV_UNICODE_MAX      (0x10'ffffU)
#define UCONV_ASCII_MAX        (0x7fU)

/* The mask values for input and output endians. */
#define UCONV_IN_ENDIAN_MASKS  (UCONV_IN_BIG_ENDIAN | UCONV_IN_LITTLE_ENDIAN)
#define UCONV_OUT_ENDIAN_MASKS (UCONV_OUT_BIG_ENDIAN | UCONV_OUT_LITTLE_ENDIAN)

/* Native and reversed endian macros. */
#ifndef _ZFS_BIG_ENDIAN
   #define UCONV_IN_NAT_ENDIAN  UCONV_IN_BIG_ENDIAN
   #define UCONV_IN_REV_ENDIAN  UCONV_IN_LITTLE_ENDIAN
   #define UCONV_OUT_NAT_ENDIAN UCONV_OUT_BIG_ENDIAN
   #define UCONV_OUT_REV_ENDIAN UCONV_OUT_LITTLE_ENDIAN
#else
   #define UCONV_IN_NAT_ENDIAN  UCONV_IN_LITTLE_ENDIAN
   #define UCONV_IN_REV_ENDIAN  UCONV_IN_BIG_ENDIAN
   #define UCONV_OUT_NAT_ENDIAN UCONV_OUT_LITTLE_ENDIAN
   #define UCONV_OUT_REV_ENDIAN UCONV_OUT_BIG_ENDIAN
#endif /* _BIG_ENDIAN */

/* The Byte Order Mark (BOM) character in normal and reversed byte orderings. */
#define UCONV_BOM_NORMAL     (0xfeffU)
#define UCONV_BOM_SWAPPED    (0xfffeU)
#define UCONV_BOM_SWAPPED_32 (0xfffe'0000U)

/* UTF-32 boundaries based on UTF-8 character byte lengths. */
#define UCONV_U8_ONE_BYTE    (0x7fU)
#define UCONV_U8_TWO_BYTES   (0x7ffU)
#define UCONV_U8_THREE_BYTES (0xffffU)
#define UCONV_U8_FOUR_BYTES  (0x10'ffffU)

/* The common minimum and maximum values at the UTF-8 character bytes. */
#define UCONV_U8_BYTE_MIN    (0x80U)
#define UCONV_U8_BYTE_MAX    (0xbfU)

/*
 * The following "6" and "0x3f" came from "10xx xxxx" bit representation of
 * UTF-8 character bytes.
 */
#define UCONV_U8_BIT_SHIFT   6
#define UCONV_U8_BIT_MASK    0x3f

/*
 * The following vector shows remaining bytes in a UTF-8 character.
 * Index will be the first byte of the character.
 */
static const uint8_t remaining_bytes_tbl[0x100] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

   /*	C0  C1  C2  C3  C4  C5  C6  C7  C8  C9  CA  CB  CC  CD  CE  CF */
   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

   /*	D0  D1  D2  D3  D4  D5  D6  D7  D8  D9  DA  DB  DC  DD  DE  DF */
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

   /*	E0  E1  E2  E3  E4  E5  E6  E7  E8  E9  EA  EB  EC  ED  EE  EF */
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,

   /*	F0  F1  F2  F3  F4  F5  F6  F7  F8  F9  FA  FB  FC  FD  FE  FF */
   3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/*
 * The following is a vector of bit-masks to get used bits in
 * the first byte of a UTF-8 character.  Index is remaining bytes at above of
 * the character.
 */
static const uint8_t u8_masks_tbl[6] = {0x00, 0x1f, 0x0f, 0x07, 0x03, 0x01};

/*
 * The following two vectors are to provide valid minimum and
 * maximum values for the 2'nd byte of a multibyte UTF-8 character for
 * better illegal sequence checking. The index value must be the value of
 * the first byte of the UTF-8 character.
 */
static const uint8_t valid_min_2nd_byte[0x100] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

   /*	C0    C1    C2    C3    C4    C5    C6    C7 */
   0, 0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,

   /*	C8    C9    CA    CB    CC    CD    CE    CF */
   0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,

   /*	D0    D1    D2    D3    D4    D5    D6    D7 */
   0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,

   /*	D8    D9    DA    DB    DC    DD    DE    DF */
   0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,

   /*	E0    E1    E2    E3    E4    E5    E6    E7 */
   0xa0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,

   /*	E8    E9    EA    EB    EC    ED    EE    EF */
   0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,

   /*	F0    F1    F2    F3    F4    F5    F6    F7 */
   0x90, 0x80, 0x80, 0x80, 0x80, 0, 0, 0,

   0, 0, 0, 0, 0, 0, 0, 0};

static const uint8_t valid_max_2nd_byte[0x100] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

   /*	C0    C1    C2    C3    C4    C5    C6    C7 */
   0, 0, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf,

   /*	C8    C9    CA    CB    CC    CD    CE    CF */
   0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf,

   /*	D0    D1    D2    D3    D4    D5    D6    D7 */
   0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf,

   /*	D8    D9    DA    DB    DC    DD    DE    DF */
   0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf,

   /*	E0    E1    E2    E3    E4    E5    E6    E7 */
   0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf,

   /*	E8    E9    EA    EB    EC    ED    EE    EF */
   0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x9f, 0xbf, 0xbf,

   /*	F0    F1    F2    F3    F4    F5    F6    F7 */
   0xbf, 0xbf, 0xbf, 0xbf, 0x8f, 0, 0, 0,

   0, 0, 0, 0, 0, 0, 0, 0};

static int check_endian(int flag, int* in, int* out)
{
   *in = flag & UCONV_IN_ENDIAN_MASKS;

   /* You cannot have both. */
   if (*in == UCONV_IN_ENDIAN_MASKS)
   {
      return (EBADF);
   }

   if (*in == 0)
   {
      *in = UCONV_IN_NAT_ENDIAN;
   }

   *out = flag & UCONV_OUT_ENDIAN_MASKS;

   /* You cannot have both. */
   if (*out == UCONV_OUT_ENDIAN_MASKS)
   {
      return (EBADF);
   }

   if (*out == 0)
   {
      *out = UCONV_OUT_NAT_ENDIAN;
   }

   return (0);
}

static bool check_bom16(const uint16_t* u16s, size_t u16l, int* in)
{
   if (u16l > 0)
   {
      if (*u16s == UCONV_BOM_NORMAL)
      {
         *in = UCONV_IN_NAT_ENDIAN;
         return (true);
      }
      if (*u16s == UCONV_BOM_SWAPPED)
      {
         *in = UCONV_IN_REV_ENDIAN;
         return (true);
      }
   }

   return (false);
}

static bool check_bom32(const uint32_t* u32s, size_t u32l, int* in)
{
   if (u32l > 0)
   {
      if (*u32s == UCONV_BOM_NORMAL)
      {
         *in = UCONV_IN_NAT_ENDIAN;
         return (true);
      }
      if (*u32s == UCONV_BOM_SWAPPED_32)
      {
         *in = UCONV_IN_REV_ENDIAN;
         return (true);
      }
   }

   return (false);
}

uint32_t _Fast_Conv_UTF16_To_UTF32(const uint16_t* u16s, size_t* utf16len, uint32_t* u32s, size_t* utf32len, int flag)
{
   int      inendian;
   int      outendian;
   size_t   u16l;
   size_t   u32l;
   uint32_t hi;
   uint32_t lo;
   bool     do_not_ignore_null;

   /*
    * Do preliminary validity checks on parameters and collect info on
    * endians.
    */
   if (u16s == NULL || utf16len == NULL)
   {
      return (EILSEQ);
   }

   if (u32s == NULL || utf32len == NULL)
   {
      return (E2BIG);
   }

   if (check_endian(flag, &inendian, &outendian) != 0)
   {
      return (EBADF);
   }

   /*
    * Initialize input and output parameter buffer indices and
    * temporary variables.
    */
   u16l = u32l        = 0;
   hi                 = 0;
   do_not_ignore_null = ((flag & UCONV_IGNORE_NULL) == 0);

   /*
    * Check on the BOM at the beginning of the input buffer if required
    * and if there is indeed one, process it.
    */
   if ((flag & UCONV_IN_ACCEPT_BOM) && check_bom16(u16s, *utf16len, &inendian))
   {
      u16l++;
   }

   /*
    * Reset inendian and outendian so that after this point, those can be
    * used as condition values.
    */
   inendian &= UCONV_IN_NAT_ENDIAN;
   outendian &= UCONV_OUT_NAT_ENDIAN;

   /*
    * If there is something in the input buffer and if necessary and
    * requested, save the BOM at the output buffer.
    */
   if (*utf16len > 0 && *utf32len > 0 && (flag & UCONV_OUT_EMIT_BOM))
   {
      u32s[u32l++] = (outendian) ? UCONV_BOM_NORMAL : UCONV_BOM_SWAPPED_32;
   }

   /*
    * Do conversion; if encounter a surrogate pair, assemble high and
    * low pair values to form a UTF-32 character. If a half of a pair
    * exists alone, then, either it is an illegal (EILSEQ) or
    * invalid (EINVAL) value.
    */
   for (; u16l < *utf16len; u16l++)
   {
      if (u16s[u16l] == 0 && do_not_ignore_null)
      {
         break;
      }

      lo = (uint32_t)((inendian) ? u16s[u16l] : _Fast_Byte_Swap_16(u16s[u16l]));

      if (lo >= UCONV_U16_HI_MIN && lo <= UCONV_U16_HI_MAX)
      {
         if (hi)
         {
            return (EILSEQ);
         }
         hi = lo;
         continue;
      }
      else if (lo >= UCONV_U16_LO_MIN && lo <= UCONV_U16_LO_MAX)
      {
         if (!hi)
         {
            return (EILSEQ);
         }
         lo = (((hi - UCONV_U16_HI_MIN) * UCONV_U16_BIT_SHIFT + lo - UCONV_U16_LO_MIN) & UCONV_U16_BIT_MASK) + UCONV_U16_START;
         hi = 0;
      }
      else if (hi)
      {
         return (EILSEQ);
      }

      if (u32l >= *utf32len)
      {
         return (E2BIG);
      }

      u32s[u32l++] = (outendian) ? lo : _Fast_Byte_Swap_32(lo);
   }

   /*
    * If high half didn't see low half, then, it's most likely the input
    * parameter is incomplete.
    */
   if (hi)
   {
      return (EINVAL);
   }

   /*
    * Save the number of consumed and saved characters. They do not
    * include terminating NULL character (U+0000) at the end of
    * the input buffer (even when UCONV_IGNORE_NULL isn't specified and
    * the input buffer length is big enough to include the terminating
    * NULL character).
    */
   *utf16len = u16l;
   *utf32len = u32l;

   return (0);
}

uint32_t _Fast_Conv_UTF16_To_UTF8(const uint16_t* u16s, size_t* utf16len, uint8_t* u8s, size_t* utf8len, int flag)
{
   int      inendian;
   int      outendian;
   size_t   u16l;
   size_t   u8l;
   uint32_t hi;
   uint32_t lo;
   bool     do_not_ignore_null;

   if (u16s == NULL || utf16len == NULL)
   {
      return (EILSEQ);
   }

   if (u8s == NULL || utf8len == NULL)
   {
      return (E2BIG);
   }

   if (check_endian(flag, &inendian, &outendian) != 0)
   {
      return (EBADF);
   }

   u16l = u8l         = 0;
   hi                 = 0;
   do_not_ignore_null = ((flag & UCONV_IGNORE_NULL) == 0);

   if ((flag & UCONV_IN_ACCEPT_BOM) && check_bom16(u16s, *utf16len, &inendian))
   {
      u16l++;
   }

   inendian &= UCONV_IN_NAT_ENDIAN;

   for (; u16l < *utf16len; u16l++)
   {
      if (u16s[u16l] == 0 && do_not_ignore_null)
      {
         break;
      }

      lo = (uint32_t)((inendian) ? u16s[u16l] : _Fast_Byte_Swap_16(u16s[u16l]));

      if (lo >= UCONV_U16_HI_MIN && lo <= UCONV_U16_HI_MAX)
      {
         if (hi)
         {
            return (EILSEQ);
         }
         hi = lo;
         continue;
      }
      else if (lo >= UCONV_U16_LO_MIN && lo <= UCONV_U16_LO_MAX)
      {
         if (!hi)
         {
            return (EILSEQ);
         }
         lo = (((hi - UCONV_U16_HI_MIN) * UCONV_U16_BIT_SHIFT + lo - UCONV_U16_LO_MIN) & UCONV_U16_BIT_MASK) + UCONV_U16_START;
         hi = 0;
      }
      else if (hi)
      {
         return (EILSEQ);
      }

      /*
       * Now we convert a UTF-32 character into a UTF-8 character.
       * Unicode coding space is between U+0000 and U+10FFFF;
       * anything bigger is an illegal character.
       */
      if (lo <= UCONV_U8_ONE_BYTE)
      {
         if (u8l >= *utf8len)
         {
            return (E2BIG);
         }
         u8s[u8l++] = (uint8_t)lo;
      }
      else if (lo <= UCONV_U8_TWO_BYTES)
      {
         if ((u8l + 1) >= *utf8len)
         {
            return (E2BIG);
         }
         u8s[u8l++] = (uint8_t)(0xc0 | ((lo & 0x07c0) >> 6));
         u8s[u8l++] = (uint8_t)(0x80 | (lo & 0x003f));
      }
      else if (lo <= UCONV_U8_THREE_BYTES)
      {
         if ((u8l + 2) >= *utf8len)
         {
            return (E2BIG);
         }
         u8s[u8l++] = (uint8_t)(0xe0 | ((lo & 0x0'f000) >> 12));
         u8s[u8l++] = (uint8_t)(0x80 | ((lo & 0x0'0fc0) >> 6));
         u8s[u8l++] = (uint8_t)(0x80 | (lo & 0x0'003f));
      }
      else if (lo <= UCONV_U8_FOUR_BYTES)
      {
         if ((u8l + 3) >= *utf8len)
         {
            return (E2BIG);
         }
         u8s[u8l++] = (uint8_t)(0xf0 | ((lo & 0x01c'0000) >> 18));
         u8s[u8l++] = (uint8_t)(0x80 | ((lo & 0x003'f000) >> 12));
         u8s[u8l++] = (uint8_t)(0x80 | ((lo & 0x000'0fc0) >> 6));
         u8s[u8l++] = (uint8_t)(0x80 | (lo & 0x000'003f));
      }
      else
      {
         return (EILSEQ);
      }
   }

   if (hi)
   {
      return (EINVAL);
   }

   *utf16len = u16l;
   *utf8len  = u8l;

   return (0);
}

uint32_t _Fast_Conv_UTF32_To_UTF16(const uint32_t* u32s, size_t* utf32len, uint16_t* u16s, size_t* utf16len, int flag)
{
   int      inendian;
   int      outendian;
   size_t   u16l;
   size_t   u32l;
   uint32_t hi;
   uint32_t lo;
   bool     do_not_ignore_null;

   if (u32s == NULL || utf32len == NULL)
   {
      return (EILSEQ);
   }

   if (u16s == NULL || utf16len == NULL)
   {
      return (E2BIG);
   }

   if (check_endian(flag, &inendian, &outendian) != 0)
   {
      return (EBADF);
   }

   u16l = u32l        = 0;
   do_not_ignore_null = ((flag & UCONV_IGNORE_NULL) == 0);

   if ((flag & UCONV_IN_ACCEPT_BOM) && check_bom32(u32s, *utf32len, &inendian))
   {
      u32l++;
   }

   inendian &= UCONV_IN_NAT_ENDIAN;
   outendian &= UCONV_OUT_NAT_ENDIAN;

   if (*utf32len > 0 && *utf16len > 0 && (flag & UCONV_OUT_EMIT_BOM))
   {
      u16s[u16l++] = (outendian) ? UCONV_BOM_NORMAL : UCONV_BOM_SWAPPED;
   }

   for (; u32l < *utf32len; u32l++)
   {
      if (u32s[u32l] == 0 && do_not_ignore_null)
      {
         break;
      }

      hi = (inendian) ? u32s[u32l] : _Fast_Byte_Swap_32(u32s[u32l]);

      /*
       * Anything bigger than the Unicode coding space, i.e.,
       * Unicode scalar value bigger than U+10FFFF, is an illegal
       * character.
       */
      if (hi > UCONV_UNICODE_MAX)
      {
         return (EILSEQ);
      }

      /*
       * Anything bigger than U+FFFF must be converted into
       * a surrogate pair in UTF-16.
       */
      if (hi >= UCONV_U16_START)
      {
         lo = ((hi - UCONV_U16_START) % UCONV_U16_BIT_SHIFT) + UCONV_U16_LO_MIN;
         hi = ((hi - UCONV_U16_START) / UCONV_U16_BIT_SHIFT) + UCONV_U16_HI_MIN;

         if ((u16l + 1) >= *utf16len)
         {
            return (E2BIG);
         }

         if (outendian)
         {
            u16s[u16l++] = (uint16_t)hi;
            u16s[u16l++] = (uint16_t)lo;
         }
         else
         {
            u16s[u16l++] = _Fast_Byte_Swap_16(((uint16_t)hi));
            u16s[u16l++] = _Fast_Byte_Swap_16(((uint16_t)lo));
         }
      }
      else
      {
         if (u16l >= *utf16len)
         {
            return (E2BIG);
         }
         u16s[u16l++] = (outendian) ? (uint16_t)hi : _Fast_Byte_Swap_16(((uint16_t)hi));
      }
   }

   *utf16len = u16l;
   *utf32len = u32l;

   return (0);
}

uint32_t _Fast_Conv_UTF32_To_UTF8(const uint32_t* u32s, size_t* utf32len, uint8_t* u8s, size_t* utf8len, int flag)
{
   int      inendian;
   int      outendian;
   size_t   u32l;
   size_t   u8l;
   uint32_t lo;
   bool     do_not_ignore_null;

   if (u32s == NULL || utf32len == NULL)
   {
      return (EILSEQ);
   }

   if (u8s == NULL || utf8len == NULL)
   {
      return (E2BIG);
   }

   if (check_endian(flag, &inendian, &outendian) != 0)
   {
      return (EBADF);
   }

   u32l = u8l         = 0;
   do_not_ignore_null = ((flag & UCONV_IGNORE_NULL) == 0);

   if ((flag & UCONV_IN_ACCEPT_BOM) && check_bom32(u32s, *utf32len, &inendian))
   {
      u32l++;
   }

   inendian &= UCONV_IN_NAT_ENDIAN;

   for (; u32l < *utf32len; u32l++)
   {
      if (u32s[u32l] == 0 && do_not_ignore_null)
      {
         break;
      }

      lo = (inendian) ? u32s[u32l] : _Fast_Byte_Swap_32(u32s[u32l]);

      if (lo <= UCONV_U8_ONE_BYTE)
      {
         if (u8l >= *utf8len)
         {
            return (E2BIG);
         }
         u8s[u8l++] = (uint8_t)lo;
      }
      else if (lo <= UCONV_U8_TWO_BYTES)
      {
         if ((u8l + 1) >= *utf8len)
         {
            return (E2BIG);
         }
         u8s[u8l++] = (uint8_t)(0xc0 | ((lo & 0x07c0) >> 6));
         u8s[u8l++] = (uint8_t)(0x80 | (lo & 0x003f));
      }
      else if (lo <= UCONV_U8_THREE_BYTES)
      {
         if ((u8l + 2) >= *utf8len)
         {
            return (E2BIG);
         }
         u8s[u8l++] = (uint8_t)(0xe0 | ((lo & 0x0'f000) >> 12));
         u8s[u8l++] = (uint8_t)(0x80 | ((lo & 0x0'0fc0) >> 6));
         u8s[u8l++] = (uint8_t)(0x80 | (lo & 0x0'003f));
      }
      else if (lo <= UCONV_U8_FOUR_BYTES)
      {
         if ((u8l + 3) >= *utf8len)
         {
            return (E2BIG);
         }
         u8s[u8l++] = (uint8_t)(0xf0 | ((lo & 0x01c'0000) >> 18));
         u8s[u8l++] = (uint8_t)(0x80 | ((lo & 0x003'f000) >> 12));
         u8s[u8l++] = (uint8_t)(0x80 | ((lo & 0x000'0fc0) >> 6));
         u8s[u8l++] = (uint8_t)(0x80 | (lo & 0x000'003f));
      }
      else
      {
         return (EILSEQ);
      }
   }

   *utf32len = u32l;
   *utf8len  = u8l;

   return (0);
}

uint32_t _Fast_Conv_UTF8_To_UTF16(const uint8_t* u8s, size_t* utf8len, uint16_t* u16s, size_t* utf16len, int flag)
{
   int      inendian;
   int      outendian;
   size_t   u16l;
   size_t   u8l;
   uint32_t hi;
   uint32_t lo;
   int      remaining_bytes;
   int      first_b;
   bool     do_not_ignore_null;

   if (u8s == NULL || utf8len == NULL)
   {
      return (EILSEQ);
   }

   if (u16s == NULL || utf16len == NULL)
   {
      return (E2BIG);
   }

   if (check_endian(flag, &inendian, &outendian) != 0)
   {
      return (EBADF);
   }

   u16l = u8l         = 0;
   do_not_ignore_null = ((flag & UCONV_IGNORE_NULL) == 0);

   outendian &= UCONV_OUT_NAT_ENDIAN;

   if (*utf8len > 0 && *utf16len > 0 && (flag & UCONV_OUT_EMIT_BOM))
   {
      u16s[u16l++] = (outendian) ? UCONV_BOM_NORMAL : UCONV_BOM_SWAPPED;
   }

   for (; u8l < *utf8len;)
   {
      if (u8s[u8l] == 0 && do_not_ignore_null)
      {
         break;
      }

      /*
       * Collect a UTF-8 character and convert it to a UTF-32
       * character. In doing so, we screen out illegally formed
       * UTF-8 characters and treat such as illegal characters.
       * The algorithm at below also screens out anything bigger
       * than the U+10FFFF.
       *
       * See Unicode 3.1 UTF-8 Corrigendum and Unicode 3.2 for
       * more details on the illegal values of UTF-8 character
       * bytes.
       */
      hi = (uint32_t)u8s[u8l++];

      if (hi > UCONV_ASCII_MAX)
      {
         if ((remaining_bytes = remaining_bytes_tbl[hi]) == 0)
         {
            return (EILSEQ);
         }

         first_b = hi;
         hi      = hi & u8_masks_tbl[remaining_bytes];

         for (; remaining_bytes > 0; remaining_bytes--)
         {
            /*
             * If we have no more bytes, the current
             * UTF-8 character is incomplete.
             */
            if (u8l >= *utf8len)
            {
               return (EINVAL);
            }

            lo = (uint32_t)u8s[u8l++];

            if (first_b)
            {
               if (lo < valid_min_2nd_byte[first_b] || lo > valid_max_2nd_byte[first_b])
               {
                  return (EILSEQ);
               }
               first_b = 0;
            }
            else if (lo < UCONV_U8_BYTE_MIN || lo > UCONV_U8_BYTE_MAX)
            {
               return (EILSEQ);
            }
            hi = (hi << UCONV_U8_BIT_SHIFT) | (lo & UCONV_U8_BIT_MASK);
         }
      }

      if (hi >= UCONV_U16_START)
      {
         lo = ((hi - UCONV_U16_START) % UCONV_U16_BIT_SHIFT) + UCONV_U16_LO_MIN;
         hi = ((hi - UCONV_U16_START) / UCONV_U16_BIT_SHIFT) + UCONV_U16_HI_MIN;

         if ((u16l + 1) >= *utf16len)
         {
            return (E2BIG);
         }

         if (outendian)
         {
            u16s[u16l++] = (uint16_t)hi;
            u16s[u16l++] = (uint16_t)lo;
         }
         else
         {
            u16s[u16l++] = _Fast_Byte_Swap_16(((uint16_t)hi));
            u16s[u16l++] = _Fast_Byte_Swap_16(((uint16_t)lo));
         }
      }
      else
      {
         if (u16l >= *utf16len)
         {
            return (E2BIG);
         }

         u16s[u16l++] = (outendian) ? (uint16_t)hi : _Fast_Byte_Swap_16(((uint16_t)hi));
      }
   }

   *utf16len = u16l;
   *utf8len  = u8l;

   return (0);
}

uint32_t _Fast_Conv_UTF8_To_UTF32(const uint8_t* u8s, size_t* utf8len, uint32_t* u32s, size_t* utf32len, int flag)
{
   int      inendian;
   int      outendian;
   size_t   u32l;
   size_t   u8l;
   uint32_t hi;
   uint32_t c;
   int      remaining_bytes;
   int      first_b;
   bool     do_not_ignore_null;

   if (u8s == NULL || utf8len == NULL)
   {
      return (EILSEQ);
   }

   if (u32s == NULL || utf32len == NULL)
   {
      return (E2BIG);
   }

   if (check_endian(flag, &inendian, &outendian) != 0)
   {
      return (EBADF);
   }

   u32l = u8l         = 0;
   do_not_ignore_null = ((flag & UCONV_IGNORE_NULL) == 0);

   outendian &= UCONV_OUT_NAT_ENDIAN;

   if (*utf8len > 0 && *utf32len > 0 && (flag & UCONV_OUT_EMIT_BOM))
   {
      u32s[u32l++] = (outendian) ? UCONV_BOM_NORMAL : UCONV_BOM_SWAPPED_32;
   }

   for (; u8l < *utf8len;)
   {
      if (u8s[u8l] == 0 && do_not_ignore_null)
      {
         break;
      }

      hi = (uint32_t)u8s[u8l++];

      if (hi > UCONV_ASCII_MAX)
      {
         if ((remaining_bytes = remaining_bytes_tbl[hi]) == 0)
         {
            return (EILSEQ);
         }

         first_b = hi;
         hi      = hi & u8_masks_tbl[remaining_bytes];

         for (; remaining_bytes > 0; remaining_bytes--)
         {
            if (u8l >= *utf8len)
            {
               return (EINVAL);
            }

            c = (uint32_t)u8s[u8l++];

            if (first_b)
            {
               if (c < valid_min_2nd_byte[first_b] || c > valid_max_2nd_byte[first_b])
               {
                  return (EILSEQ);
               }
               first_b = 0;
            }
            else if (c < UCONV_U8_BYTE_MIN || c > UCONV_U8_BYTE_MAX)
            {
               return (EILSEQ);
            }
            hi = (hi << UCONV_U8_BIT_SHIFT) | (c & UCONV_U8_BIT_MASK);
         }
      }

      if (u32l >= *utf32len)
      {
         return (E2BIG);
      }

      u32s[u32l++] = (outendian) ? hi : _Fast_Byte_Swap_32(hi);
   }

   *utf32len = u32l;
   *utf8len  = u8l;

   return (0);
}

}}} // namespace ultralove::tools::norad
