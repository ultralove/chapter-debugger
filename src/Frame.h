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

#ifndef __FRAME_H_INCL__
#define __FRAME_H_INCL__

#include "Common.h"
#include "Guid.h"
#include "ID3V2.h"
#include "IFrame.h"
#include "Malloc.h"

namespace ultralove { namespace tools { namespace norad {

class Frame : public IFrame
{
public:
   static bool IsValid(const uint8_t* data, const size_t dataSize);
   bool        IsValid() const;

   inline uint32_t Id() const;
   inline uint32_t Size() const;
   inline uint16_t Flags() const;

   virtual bool ConfigureHeader(const uint8_t* data, const size_t dataSize);

protected:
   void SetId(const uint32_t id);
   void SetSize(const uint32_t size);
   void SetFlags(const uint16_t flags);

private:
   uint32_t id_    = ID3V2_INVALID_FRAME_ID;
   uint32_t size_  = ID3V2_INVALID_FRAME_SIZE;
   uint16_t flags_ = ID3V2_INVALID_FRAME_FLAGS;
};

inline uint32_t Frame::Id() const
{
   PRECONDITION_RETURN(IsValid() == true, ID3V2_INVALID_FRAME_ID);
   return id_;
}

inline uint32_t Frame::Size() const
{
   PRECONDITION_RETURN(IsValid() == true, ID3V2_INVALID_FRAME_SIZE);
   return size_;
}

inline uint16_t Frame::Flags() const
{
   PRECONDITION_RETURN(IsValid() == true, ID3V2_INVALID_FRAME_FLAGS);
   return flags_;
}

typedef std::set<Frame*>       FrameList;
typedef std::map<Guid, Frame*> FrameDictionary;

}}} // namespace ultralove::tools::norad

#endif // #ifndef __FRAME_H_INCL__
