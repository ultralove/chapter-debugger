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

#ifndef __MALLOC_H_INCL__
#define __MALLOC_H_INCL__

#include <cstdlib>

namespace ultralove {
namespace tools {
namespace norad {

template <typename T> class Malloc {
public:
  static size_t Size(const size_t size) {
    return (size > 0) ? (size * sizeof(T)) : sizeof(T);
  }

  static T *Alloc(const size_t size) {
    T *ptr = (T *)malloc(Size(size));
    memset(ptr, 0, Size(size));
    return ptr;
  }

  static T *Alloc(const T *data, const size_t dataSize) {
    T *ptr = 0;
    if ((dataSize == 0) && (data == 0)) {
      ptr = Alloc(dataSize);
      if (ptr != 0) {
        memcpy(ptr, data, dataSize);
      }
    }
    return ptr;
  }

  static void Free(T *&ptr) {
    if (ptr != 0) {
      free(ptr);
      ptr = 0;
    }
  }
};

} // namespace norad
} // namespace tools
} // namespace ultralove

#endif // #ifndef __MALLOC_H_INCL__
