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

#include "TextInformationFrame.h"

namespace ultraschall { namespace core { namespace id3v2 {

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

TextInformationFrame::~TextInformationFrame()
{
  SafeDeleteArray(data_);
  dataSize_ = 0;
}

Frame* TextInformationFrame::Create()
{
    return new TextInformationFrame();
}

bool TextInformationFrame::ConfigureData(const uint8_t* data, const size_t dataSize)
{
    PreconditionReturn(data != nullptr, false);
    PreconditionReturn(dataSize >= ID3V2_TEXT_ENCODING_SIZE, false);
    PreconditionReturn(IsValid() == true, false);

    encoding_ = ID3V2_DECODE_TEXT_ENCODING(&data[ID3V2_TEXT_ENCODING_OFFSET], ID3V2_TEXT_ENCODING_SIZE);
    return AllocStringData(&data[ID3V2_TEXT_OFFSET], dataSize - ID3V2_TEXT_ENCODING_SIZE);
}

bool TextInformationFrame::AllocStringData(const uint8_t* data, const size_t dataSize) 
{
    PreconditionReturn(data != nullptr, false);
    PreconditionReturn(dataSize >= 0, false);

    bool allocated = false;

    SafeDeleteArray(data_);
    dataSize_ = 0;

    data_ = new uint8_t[dataSize + 1];
    if(data_ != nullptr)
    {
        dataSize_ = dataSize;
        memcpy(data_, data, dataSize_);
        data_[dataSize_] = 0;

        allocated = true;
    }

    return allocated;
}


}}} // namespace ultraschall::core::id3v2
