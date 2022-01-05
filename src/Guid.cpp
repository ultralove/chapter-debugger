////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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

#include "Guid.h"

#include "Common.h"

#include <cstdint>
#include <cstdlib>

#ifdef _WIN32
    #include <rpc.h>
    #include <windows.h>
void InitializeGuid(uint8_t* data, const size_t dataSize)
{
    PRECONDITION(data != nullptr);
    PRECONDITION(dataSize >= sizeof(UUID));

    UUID uuid         = {0};
    RPC_STATUS status = UuidCreate(&uuid);
    if (RPC_S_OK == status) {
        memcpy(data, &uuid, dataSize);
    }
}
#elif __APPLE__
    #include <CoreFoundation/CoreFoundation.h>
void InitializeGuid(uint8_t* data, const size_t dataSize)
{
    CFUUIDRef uuidRef = CFUUIDCreate(nullptr);
}
#else
    #error "Unsupported platform"
#endif

namespace ultraschall { namespace tools { namespace chapdbg {

struct Guid::Impl
{
    uint8_t data_[16];

    Impl() : data_{0} {}

    ~Impl()
    {
        memset(data_, 0, sizeof(uint8_t) * 16);
    }

    Impl(const Impl& rhs) : data_{0}
    {
        *this = rhs;
    }

    Impl& operator=(const Impl& rhs)
    {
        if (this != &rhs) {
            memcpy(data_, rhs.data_, sizeof(uint8_t) * 16);
        }

        return *this;
    }

    bool operator==(const Impl& rhs) const
    {
        return memcmp(data_, rhs.data_, sizeof(uint8_t) * 16) == 0;
    }

    bool operator<(const Impl& rhs) const
    {
        return memcmp(data_, rhs.data_, sizeof(uint8_t) * 16) < 0;
    }
};

Guid::Guid() : impl_(new Guid::Impl()) {}

Guid::~Guid()
{
    SafeDelete(impl_);
}

Guid::Guid(const Guid& rhs) : impl_(nullptr)
{
    *this = rhs;
}

Guid& Guid::operator=(const Guid& rhs)
{
    if (this != &rhs) {
        SafeDelete(impl_);
        impl_ = new Impl(*rhs.impl_);
    }

    return *this;
}

bool Guid::operator==(const Guid& rhs) const
{
    return impl_->operator==(*rhs.impl_);
}

bool Guid::operator<(const Guid& rhs) const
{
    return impl_->operator<(*rhs.impl_);
}

Guid Guid::New()
{
    Guid guid;
    InitializeGuid(guid.impl_->data_, sizeof(uint8_t) * 16);
    return guid;
}

const Guid& Guid::Null()
{
    static Guid self;
    return self;
}

}}} // namespace ultraschall::tools::chapdbg
