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

#include "BinaryStream.h"
#include "Common.h"

namespace ultralove { namespace tools { namespace norad {

BinaryStream::BinaryStream() {}

BinaryStream::~BinaryStream()
{
   Reset();
}

BinaryStream::BinaryStream(const uint8_t* items, const size_t itemCount)
{
   Write(items, itemCount);
}

BinaryStream::BinaryStream(const BinaryStream& rhs)
{
   *this = rhs;
}

BinaryStream& BinaryStream::operator=(const BinaryStream& rhs)
{
   if (this != &rhs)
   {
      Write(rhs.Data(), rhs.Size());
   }

   return *this;
}

BinaryStream::BinaryStream(BinaryStream&& rhs) noexcept :
   items_(std::exchange(rhs.items_, static_cast<uint8_t*>(0))), itemCount_(std::exchange(rhs.itemCount_, 0))
{}

BinaryStream& BinaryStream::operator=(BinaryStream&& rhs) noexcept
{
   if (this != &rhs)
   {
      delete[] items_;
      items_     = std::exchange(rhs.items_, static_cast<uint8_t*>(0));
      itemCount_ = std::exchange(rhs.itemCount_, 0);
   }

   return *this;
}

bool BinaryStream::operator==(const BinaryStream& rhs) const
{
   return (Data() == rhs.Data()) && (Size() == rhs.Size());
}

inline const uint8_t* BinaryStream::Data(const size_t itemOffset) const
{
   PRECONDITION_RETURN(items_ != 0, 0);
   PRECONDITION_RETURN(itemOffset < itemCount_, 0);

   return &items_[itemOffset];
}

size_t BinaryStream::Write(const size_t itemOffset, const uint8_t* items, const size_t itemCount)
{
   PRECONDITION_RETURN(items != 0, false);
   PRECONDITION_RETURN(itemCount > 0, false);

   size_t itemsWritten = 0;

   if (Valid() == false)
   {
      AllocItems(itemCount);
   }
   else if ((itemOffset + itemCount) > itemCount_)
   {
      uint8_t* currentItems     = items_;
      size_t   currentItemCount = itemCount_;

      AllocItems(itemCount);
      ReplaceItems(currentItems, currentItemCount);

      SafeDeleteArray(currentItems);
      currentItemCount = 0;
   }

   if ((Valid() == true) && (itemCount_ >= (itemOffset + itemCount)))
   {
      memcpy(&items_[itemOffset * sizeof(uint8_t)], items, itemCount * sizeof(uint8_t));
      itemsWritten = itemCount;
   }

   return itemsWritten;
}

size_t BinaryStream::Read(const size_t itemOffset, uint8_t* items, const size_t itemCount) const
{
   PRECONDITION_RETURN(items_ != 0, 0);
   PRECONDITION_RETURN(itemCount_ > 0, 0);
   PRECONDITION_RETURN(items != 0, 0);
   PRECONDITION_RETURN(itemCount > 0, 0);

   const size_t resultItemCount = ((itemOffset + itemCount) <= itemCount_) ? itemCount : (itemCount_ - itemOffset);
   memcpy(items, &items_[itemOffset * sizeof(uint8_t)], resultItemCount * sizeof(uint8_t));
   return resultItemCount;
}

void BinaryStream::Reset()
{
   itemCount_ = 0;
   SafeDeleteArray(items_);
}

void BinaryStream::AllocItems(const size_t itemCount)
{
   Reset();

   if (itemCount > 0)
   {
      items_ = new uint8_t[itemCount * sizeof(uint8_t)];
      if (items_ != 0)
      {
         itemCount_ = itemCount;
      }
   }
}

void BinaryStream::ReplaceItems(const uint8_t* items, const size_t itemCount)
{
   PRECONDITION(items_ != 0);
   PRECONDITION(itemCount_ <= itemCount);

   memcpy(items_, items, itemCount * sizeof(uint8_t));
}

}}} // namespace ultralove::tools::norad
