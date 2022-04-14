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

#include "FileUtilities.h"

#include "Common.h"

#include <fstream>

namespace ultralove { namespace tools { namespace chapdbg {

bool FileExists(const std::string& filename)
{
   bool fileExists = false;

   std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
   if (file.is_open() == true) {
      fileExists = true;
      file.close();
   }

   return fileExists;
}

BinaryStream ReadFile(const std::string& filename)
{
   PRECONDITION_RETURN(filename.empty() == false, BinaryStream());

   BinaryStream stream;
   std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
   if (file.is_open() == true) {
      const size_t dataSize = static_cast<size_t>(file.tellg());
      uint8_t* data         = new uint8_t[dataSize];
      if (data != 0) {
         file.seekg(std::ios::beg); // rewind fp
         file.read(reinterpret_cast<char*>(data), dataSize);
         if (file) // overwritten to return io status
         {
            if (stream.Write(data, dataSize) != dataSize) {
               stream.Reset();
            }
         }

         SafeDeleteArray(data);
      }

      file.close();
   }

   return stream;
}

}}} // namespace ultralove::tools::chapdbg
