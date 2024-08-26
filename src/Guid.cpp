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

#include "Guid.h"

#include "Common.h"

#include <cstdint>
#include <cstdlib>

#ifdef _WIN32
#include <rpc.h>
#include <windows.h>
#elif __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#else
#error "Unsupported platform"
#endif

#ifdef _WIN32
static void InitializeGuid(uint8_t *data, const size_t dataSize) {
  PRECONDITION(data != 0);
  PRECONDITION(dataSize >= sizeof(UUID));

  UUID uuid = {0};
  RPC_STATUS status = UuidCreate(&uuid);
  if (RPC_S_OK == status) {
    memcpy(data, &uuid, dataSize);
  }
}
#elif __APPLE__
static void InitializeGuid(uint8_t *data, const size_t dataSize) {
  CFUUIDRef uuidRef = CFUUIDCreate(0);
}
#else
#endif

namespace ultralove {
namespace tools {
namespace norad {

Guid::Guid() : data_{0} {}

Guid::~Guid() { memset(data_, 0, sizeof(uint8_t) * 16); }

Guid::Guid(const Guid &rhs) { *this = rhs; }

Guid &Guid::operator=(const Guid &rhs) {
  if (this != &rhs) {
    memcpy(data_, rhs.data_, sizeof(uint8_t) * 16);
  }

  return *this;
}

bool Guid::operator==(const Guid &rhs) const {
  return memcmp(data_, rhs.data_, sizeof(uint8_t) * 16) == 0;
}

bool Guid::operator<(const Guid &rhs) const {
  return memcmp(data_, rhs.data_, sizeof(uint8_t) * 16) < 0;
}

Guid Guid::New() {
  Guid guid;
  InitializeGuid(guid.data_, sizeof(uint8_t) * 16);
  return guid;
}

const Guid &Guid::Null() {
  static Guid self;
  return self;
}

} // namespace norad
} // namespace tools
} // namespace ultralove
