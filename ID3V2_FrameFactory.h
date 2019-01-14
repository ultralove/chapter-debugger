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

#ifndef __ULTRASCHALL_ID3V2_FRAME_FACTORY_H_INCL__
#define __ULTRASCHALL_ID3V2_FRAME_FACTORY_H_INCL__

#include "Common.h"
#include "ID3V2_Frame.h"
#include "ID3V2_FrameData.h"

namespace ultraschall { namespace framework {

class ID3V2_FrameFactory
{
public:
    typedef ID3V2_Frame* (*CREATE_FRAME_FUNCTION)();

    bool RegisterFrame(const uint32_t id, CREATE_FRAME_FUNCTION factoryFunction);

    void UnregisterFrame(const uint32_t id);

    virtual ~ID3V2_FrameFactory();

    static ID3V2_FrameFactory& Instance();

    ID3V2_Frame* CreateFrame(const uint32_t id, const uint32_t size, const uint16_t flags) const;

private:
    ID3V2_FrameFactory();

    typedef std::map<uint32_t, CREATE_FRAME_FUNCTION> FactoryFunctionDictionary;
    FactoryFunctionDictionary                         factoryFunctions_;
    mutable std::recursive_mutex                      factoryFunctionsLock_;
};

}} // namespace ultraschall::id3v2

#endif // #ifndef __ULTRASCHALL_ID3V2_FRAME_FACTORY_H_INCL____
