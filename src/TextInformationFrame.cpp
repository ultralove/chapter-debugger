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

#include "TextInformationFrame.h"

#include "FastRoutines.h"
#include "StringUtilities.h"

namespace ultralove {
namespace tools {
namespace norad {

static FrameResource<TextInformationFrame> registry1("TALB");
static FrameResource<TextInformationFrame> registry2("TBPM");
static FrameResource<TextInformationFrame> registry3("TCOM");
static FrameResource<TextInformationFrame> registry4("TCON");
static FrameResource<TextInformationFrame> registry5("TCOP");
static FrameResource<TextInformationFrame> registry6("TDAT");
static FrameResource<TextInformationFrame> registry7("TDLY");
static FrameResource<TextInformationFrame> registry8("TENC");
static FrameResource<TextInformationFrame> registry9("TEXT");
static FrameResource<TextInformationFrame> registry10("TFLT");
static FrameResource<TextInformationFrame> registry11("TIME");
static FrameResource<TextInformationFrame> registry12("TIT1");
static FrameResource<TextInformationFrame> registry13("TIT2");
static FrameResource<TextInformationFrame> registry14("TIT3");
static FrameResource<TextInformationFrame> registry15("TKEY");
static FrameResource<TextInformationFrame> registry16("TLAN");
static FrameResource<TextInformationFrame> registry17("TLEN");
static FrameResource<TextInformationFrame> registry18("TMED");
static FrameResource<TextInformationFrame> registry19("TOAL");
static FrameResource<TextInformationFrame> registry20("TOFN");
static FrameResource<TextInformationFrame> registry21("TOLY");
static FrameResource<TextInformationFrame> registry22("TOPE");
static FrameResource<TextInformationFrame> registry23("TORY");
static FrameResource<TextInformationFrame> registry24("TOWN");
static FrameResource<TextInformationFrame> registry25("TPE1");
static FrameResource<TextInformationFrame> registry26("TPE2");
static FrameResource<TextInformationFrame> registry27("TPE3");
static FrameResource<TextInformationFrame> registry28("TPE4");
static FrameResource<TextInformationFrame> registry29("TPOS");
static FrameResource<TextInformationFrame> registry30("TPUB");
static FrameResource<TextInformationFrame> registry31("TRCK");
static FrameResource<TextInformationFrame> registry32("TRDA");
static FrameResource<TextInformationFrame> registry33("TRSN");
static FrameResource<TextInformationFrame> registry34("TRSO");
static FrameResource<TextInformationFrame> registry35("TSIZ");
static FrameResource<TextInformationFrame> registry36("TSRC");
static FrameResource<TextInformationFrame> registry37("TSSE");
static FrameResource<TextInformationFrame> registry38("TYER");

TextInformationFrame::~TextInformationFrame() {
  SafeDeleteArray(data_);
  dataSize_ = 0;
}

Frame *TextInformationFrame::Create() { return new TextInformationFrame(); }

bool TextInformationFrame::ConfigureData(const uint8_t *data,
                                         const size_t dataSize) {
  PRECONDITION_RETURN(data != 0, false);
  PRECONDITION_RETURN(dataSize >= ID3V2_TEXT_ENCODING_SIZE, false);
  PRECONDITION_RETURN(IsValid() == true, false);

  std::cout << "----------------------------------------" << std::endl;

  encoding_ = ID3V2_DECODE_TEXT_ENCODING(&data[ID3V2_TEXT_ENCODING_OFFSET],
                                         ID3V2_TEXT_ENCODING_SIZE);
  if (encoding_ == 0) { // ISO-8859-1
    const char *InputBuffer = (char *)&data[ID3V2_TEXT_ENCODING_SIZE];
    if (InputBuffer != 0) {
      const size_t InputBufferSize = dataSize - ID3V2_TEXT_ENCODING_SIZE;
      const size_t OutputBufferSize = InputBufferSize + 1;
      char *OutputBuffer = Malloc<char>::Alloc(InputBufferSize);
      if (OutputBuffer != 0) {
        memcpy(OutputBuffer, InputBuffer, InputBufferSize);
        // std::cout << "InputBuffer = " << InputBufferSize << ",
        // OutputBufferSize = " << OutputBufferSize << std::endl;
        std::cout << OutputBuffer << std::endl;
        Malloc<char>::Free(OutputBuffer);
      }
    }
  } else if ((encoding_ == 1) || (encoding_ == 2)) // UTF-16/UTF-16BE
  {
    const uint16_t *InputBuffer = (uint16_t *)&data[ID3V2_TEXT_ENCODING_SIZE];
    size_t InputBufferSize =
        (dataSize - ID3V2_TEXT_ENCODING_SIZE) / sizeof(uint16_t);
    size_t OutputBufferSize = InputBufferSize * 2;
    char *OutputBuffer = Malloc<char>::Alloc(InputBufferSize * 2);
    if (OutputBuffer != 0) {
      uint32_t result = _Fast_Conv_UTF16_To_UTF8(
          InputBuffer, &InputBufferSize, (uint8_t *)OutputBuffer,
          &OutputBufferSize, UCONV_IN_ACCEPT_BOM | UCONV_IGNORE_NULL);
      if (result == 0) {
        // std::cout << "InputBuffer = " << InputBufferSize << ",
        // OutputBufferSize = " << OutputBufferSize << std::endl;
        std::cout << OutputBuffer << std::endl;
      }
      Malloc<char>::Free(OutputBuffer);
    }
  } else if (encoding_ == 0) { // UTF-8
    const char *InputBuffer = (char *)&data[ID3V2_TEXT_ENCODING_SIZE];
    if (InputBuffer != 0) {
      const size_t InputBufferSize = dataSize - ID3V2_TEXT_ENCODING_SIZE;
      const size_t OutputBufferSize = InputBufferSize + 1;
      char *OutputBuffer = Malloc<char>::Alloc(InputBufferSize);
      if (OutputBuffer != 0) {
        memcpy(OutputBuffer, InputBuffer, InputBufferSize);
        // std::cout << "InputBuffer = " << InputBufferSize << ",
        // OutputBufferSize = " << OutputBufferSize << std::endl;
        std::cout << OutputBuffer << std::endl;
        Malloc<char>::Free(OutputBuffer);
      }
    }
  } else {
  }

  std::cout << "----------------------------------------" << std::endl;
  std::cout << std::endl;

  return true;
}

} // namespace norad
} // namespace tools
} // namespace ultralove
