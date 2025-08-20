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

#ifndef __COMMON_H_INCL__
#define __COMMON_H_INCL__

#include <algorithm>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <mutex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#ifndef _WIN32
    #define IN
    #define OUT
    #define INOUT
#endif // #ifndef _WIN32

#include "SharedObject.h"

#define PRECONDITION(a)                                                        \
  if (!(a)) {                                                                  \
    return;                                                                    \
  }

#define PRECONDITION_RETURN(a, b)                                              \
  if (!(a)) {                                                                  \
    return (b);                                                                \
  }

namespace ultralove { namespace chapdbg {
#define SafeRelease(a)                                                         \
  if ((a) != 0) {                                                              \
    a->Release();                                                              \
    a = 0;                                                                     \
  }

template<class T> inline void SafeDelete(T*& ptr)
{
    delete ptr;
    ptr = 0;
}

template<class T> inline void SafeDeleteArray(T*& ptr)
{
    delete[] ptr;
    ptr = 0;
}
}} // namespace ultralove::chapdbg

#endif // #ifndef __COMMON_H_INCL__
