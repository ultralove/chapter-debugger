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

namespace ultraschall { namespace framework {

void HexDump(const uint8_t* data, const size_t dataSize, const size_t rowSize)
{
    PRECONDITION(data != 0);
    PRECONDITION(dataSize > 0);
    PRECONDITION(rowSize > 0);

    size_t offset = 0;
    while(offset < dataSize)
    {
        // const size_t chunkSize = ((dataSize - offset) < rowSize) ? (dataSize - offset) : rowSize;
        // for(size_t i = 0; i < chunkSize; i++)
        //{
        //    printf("%2.2x ", data[offset + i]);
        //}

        for(size_t i = 0; i < rowSize; i++)
        {
            if((offset + i) < dataSize)
            {
                printf("%2.2x ", data[offset + i]);
            }
            else
            {
                printf("   ");
            }
        }

        printf("| ");

        const size_t chunkSize = ((dataSize - offset) < rowSize) ? (dataSize - offset) : rowSize;
        for(size_t j = 0; j < chunkSize; j++)
        {
            if(isprint(data[offset + j]))
            {
                printf("%c", data[offset + j]);
            }
            else
            {
                printf(".");
            }
        }

        printf("\n");

        offset += chunkSize;
    }
}

}} // namespace ultraschall::framework
