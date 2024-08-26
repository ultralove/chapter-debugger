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

#ifndef __ID3V2_HEADER_H_INCL__
#define __ID3V2_HEADER_H_INCL__

#include "Common.h"
#include "ID3V2.h"

namespace ultralove {
namespace tools {
namespace norad {

class ID3V2_Header {
public:
  ID3V2_Header();
  ID3V2_Header(const uint8_t *data, const size_t dataSize);

  inline const std::vector<uint8_t> &Id() const;
  inline uint8_t Version() const;
  inline uint8_t Revision() const;
  inline uint8_t Flags() const;
  inline uint32_t Size() const;

  bool IsValid() const;

private:
  std::vector<uint8_t> id_ = ID3V2_INVALID_ID;
  uint8_t version_ = ID3V2_INVALID_VERSION;
  uint8_t revision_ = ID3V2_INVALID_REVISION;
  uint8_t flags_ = ID3V2_INVALID_FLAGS;
  uint32_t size_ = ID3V2_INVALID_SIZE;
};

inline const std::vector<uint8_t> &ID3V2_Header::Id() const {
  PRECONDITION_RETURN(IsValid() == true, ID3V2_INVALID_ID);
  return id_;
}

inline uint8_t ID3V2_Header::Version() const {
  PRECONDITION_RETURN(IsValid() == true, ID3V2_INVALID_VERSION);
  return version_;
}

inline uint8_t ID3V2_Header::Revision() const {
  PRECONDITION_RETURN(IsValid() == true, ID3V2_INVALID_REVISION);
  return revision_;
}

inline uint8_t ID3V2_Header::Flags() const {
  PRECONDITION_RETURN(IsValid() == true, ID3V2_INVALID_FLAGS);
  return flags_;
}

inline uint32_t ID3V2_Header::Size() const {
  PRECONDITION_RETURN(IsValid() == true, ID3V2_INVALID_SIZE);
  return size_;
}

} // namespace norad
} // namespace tools
} // namespace ultralove

#endif // #ifndef __ID3V2_HEADER_H_INCL__
