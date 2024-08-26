////////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) Ultralove Contributors (https://github.com/ultralove)
//
// The MIT License (MIT)
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
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __GUID_H_INCL__
#define __GUID_H_INCL__

namespace ultralove {
namespace tools {
namespace norad {

class Guid {
public:
  ~Guid();

  Guid(const Guid &rhs);
  Guid &operator=(const Guid &rhs);

  bool operator==(const Guid &rhs) const;
  bool operator<(const Guid &rhs) const;

  static Guid New();
  static const Guid &Null();

private:
  uint8_t data_[16];

  Guid();
};

} // namespace norad
} // namespace tools
} // namespace ultralove

#endif // #ifndef __GUID_H_INCL__
