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

#include "StringUtilities.h"

#include "Common.h"

namespace ultraschall { namespace tools { namespace chapdbg {

void HexDump(const uint8_t* data, const size_t dataSize, const size_t rowSize)
{
    HexDump(0, data, dataSize, rowSize);
}

void HexDump(const size_t identLevel, const uint8_t* data, const size_t dataSize, const size_t rowSize)
{
    PRECONDITION(data != 0);
    PRECONDITION(dataSize > 0);
    PRECONDITION(rowSize > 0);

    size_t offset = 0;
    while (offset < dataSize) {
        std::cout << IndentString(identLevel);

        for (size_t i = 0; i < rowSize; i++) {
            if ((offset + i) < dataSize) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)data[offset + i] << " ";
            }
            else {
                std::cout << "   ";
            }
        }

        std::cout << "| ";

        const size_t chunkSize = ((dataSize - offset) < rowSize) ? (dataSize - offset) : rowSize;
        for (size_t j = 0; j < chunkSize; j++) {
            if (std::isprint(data[offset + j])) {
                std::cout << data[offset + j];
            }
            else {
                std::cout << ".";
            }
        }

        offset += chunkSize;
        std::cout << std::endl;
    }
}

std::string IndentString(const size_t indentLevel)
{
    return std::string(indentLevel * 4, ' ');
}

String::String() {}

String::~String()
{
    Clear();
}

void String::Clear()
{
    SafeDeleteArray(data_);
    dataSize_ = INVALID_STRING_SIZE;
    encoding_ = ENCODING::INVALID_CHARACTER_ENCODING;
}

}}} // namespace ultraschall::tools::chapdbg
