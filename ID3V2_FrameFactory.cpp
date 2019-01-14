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

#include "ID3V2_FrameFactory.h"
#include "ID3V2_Frame.h"

namespace ultraschall { namespace framework {

ID3V2_FrameFactory::ID3V2_FrameFactory() {}

ID3V2_FrameFactory::~ID3V2_FrameFactory()
{
    std::lock_guard<std::recursive_mutex> lock(factoryFunctionsLock_);
    factoryFunctions_.clear();
}

bool ID3V2_FrameFactory::RegisterFrame(const uint32_t id, CREATE_FRAME_FUNCTION factoryFunction)
{
    PRECONDITION_RETURN(id != ID3V2_INVALID_FRAME_ID, false);
    PRECONDITION_RETURN(factoryFunction != 0, false);

    std::lock_guard<std::recursive_mutex> lock(factoryFunctionsLock_);

    bool                                            registered              = false;
    const FactoryFunctionDictionary::const_iterator factoryFunctionIterator = factoryFunctions_.find(id);
    if(factoryFunctionIterator == factoryFunctions_.end())
    {
        registered = factoryFunctions_.insert(std::pair<uint32_t, CREATE_FRAME_FUNCTION>(id, factoryFunction)).second;
    }

    return registered;
}

void ID3V2_FrameFactory::UnregisterFrame(const uint32_t id)
{
    std::lock_guard<std::recursive_mutex> lock(factoryFunctionsLock_);

    const FactoryFunctionDictionary::const_iterator factoryFunctionIterator = factoryFunctions_.find(id);
    if(factoryFunctionIterator != factoryFunctions_.end())
    {
        factoryFunctions_.erase(factoryFunctionIterator);
    }
}

ID3V2_FrameFactory& ID3V2_FrameFactory::Instance()
{
    static ID3V2_FrameFactory self;
    return self;
}

ID3V2_Frame* ID3V2_FrameFactory::CreateFrame(const uint32_t id, const uint32_t size, const uint16_t flags) const
{
    PRECONDITION_RETURN(id != ID3V2_INVALID_FRAME_ID, 0);
    PRECONDITION_RETURN(size != ID3V2_INVALID_FRAME_SIZE, 0);
    PRECONDITION_RETURN(flags != ID3V2_INVALID_FRAME_FLAGS, 0);

    std::lock_guard<std::recursive_mutex> lock(factoryFunctionsLock_);

    ID3V2_Frame*                                   newFrame                = 0;
    const FactoryFunctionDictionary::const_iterator factoryFunctionIterator = factoryFunctions_.find(id);
    if(factoryFunctionIterator != factoryFunctions_.end())
    {
        CREATE_FRAME_FUNCTION factoryFunction = factoryFunctionIterator->second;
        if(factoryFunction != 0)
        {
            newFrame = (*factoryFunction)();
        }
    }

    return newFrame;
}

}} // namespace ultraschall::framework
