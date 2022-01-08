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

#include "FrameController.h"

#include "FrameFactory.h"
#include "StringUtilities.h"

namespace ultraschall { namespace tools { namespace chapdbg {

FrameList FrameController::ParseFrames(const BinaryStream& stream)
{
    PRECONDITION_RETURN(stream.Data() != nullptr, FrameList());
    PRECONDITION_RETURN(stream.Size() > 0, FrameList());

    const FrameFactory& frameFactory = FrameFactory::Instance();
    FrameDictionary frameDictionary;
    size_t offset = ID3V2_FILE_HEADER_SIZE;
    bool isValid  = true;
    while ((true == isValid) && (offset < stream.Size())) {
        const uint8_t* data    = stream.Data(offset);
        const size_t dataSize  = stream.Size() - offset;
        const size_t frameSize = ID3V2_DECODE_FRAME_SIZE(&data[ID3V2_FRAME_SIZE_OFFSET], ID3V2_FRAME_SIZE_SIZE);
        if (frameSize > 0) {
            if (frameFactory.CanCreate(data, ID3V2_FRAME_ID_SIZE) == true) {
                Frame* pFrame = frameFactory.Create(data, dataSize);
                if (pFrame != nullptr) {
                    frameDictionary.insert(std::make_pair(Guid::New(), pFrame));
                }
            }
        }
        else { // invalid frame size
            // std::cout << "Invalid frame size" << std::endl;
            isValid = false;
        }
        offset += (frameSize + ID3V2_FRAME_HEADER_SIZE);
    }

    FrameList frameList;
    std::for_each(frameDictionary.begin(), frameDictionary.end(), [&](const std::pair<Guid, Frame*>& item) { frameList.insert(item.second); });

    return frameList;
}

size_t FrameController::DumpRawFrames(const BinaryStream& stream)
{
    PRECONDITION_RETURN(stream.Data() != nullptr, ID3V2_INVALID_FRAME);
    PRECONDITION_RETURN(stream.Size() > 0, ID3V2_INVALID_FRAME);

    DumpRawHeader(stream.Data(0), ID3V2_FILE_HEADER_SIZE);

    size_t offset = ID3V2_FILE_HEADER_SIZE;
    bool isValid  = Frame::IsValid(stream.Data(offset), stream.Size() - offset);
    while ((true == isValid) && (offset < stream.Size())) {
        offset += DumpRawFrame(0, stream.Data(offset), stream.Size());
        isValid = Frame::IsValid(stream.Data(offset), stream.Size() - offset);
    }

    return offset;
}

void FrameController::DumpRawHeader(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION(data != 0);
    PRECONDITION(dataSize >= ID3V2_FILE_HEADER_SIZE);

    const uint32_t id = ID3V2_DECODE_FILE_ID(data, ID3V2_FILE_HEADER_SIZE);
    std::cout << "Id:      " << ((uint8_t*)&id)[0] << ((uint8_t*)&id)[1] << ((uint8_t*)&id)[2] << std::endl;

    const uint8_t version  = ID3V2_DECODE_FILE_VERSION(data, ID3V2_FILE_HEADER_SIZE);
    const uint8_t revision = ID3V2_DECODE_FILE_REVISION(data, ID3V2_FILE_HEADER_SIZE);
    std::cout << "Version: 2." << static_cast<int>(version) << "." << static_cast<int>(revision) << std::endl;

    const uint8_t flags = ID3V2_DECODE_FILE_FLAGS(data, ID3V2_FILE_HEADER_SIZE);
    std::cout << "Flags:   0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(flags) << std::endl;

    const uint32_t size = ID3V2_DECODE_FILE_SIZE(data, ID3V2_FILE_HEADER_SIZE);
    std::cout << "Size:    0x" << std::hex << std::setw(8) << std::setfill('0') << size << " (" << std::dec << size << ")" << std::endl;

    static const size_t ID3V2_MAX_DATA_ROW_SIZE = 32;
    std::cout << "Data:" << std::endl;
    HexDump(data, ID3V2_FILE_HEADER_SIZE, ID3V2_MAX_DATA_ROW_SIZE);
    std::cout << std::endl;
}

size_t FrameController::ComputeSubframeOffset(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != 0, ID3V2_INVALID_SIZE_VALUE);
    PRECONDITION_RETURN(dataSize >= ID3V2_FRAME_HEADER_SIZE, ID3V2_INVALID_SIZE_VALUE);

    size_t offset    = ID3V2_FRAME_HEADER_SIZE;
    const uint8_t* p = &data[offset];

    // Skip over element id;
    while (*p != '\0') {
        p++;
        offset++;
    }

    // Skip over '\0'
    offset++;

    return offset + (sizeof(uint32_t) * 4);
}

size_t FrameController::DumpRawFrame(const size_t indentLevel, const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != 0, ID3V2_INVALID_SIZE_VALUE);
    PRECONDITION_RETURN(dataSize >= ID3V2_FRAME_HEADER_SIZE, ID3V2_INVALID_SIZE_VALUE);

    const uint32_t id = ID3V2_DECODE_FRAME_ID(ID3V2_DATA_OFFSET(data, ID3V2_FRAME_ID_OFFSET), ID3V2_FRAME_ID_SIZE);
    std::cout << IndentString(indentLevel) << "Id:      " << ((uint8_t*)&id)[0] << ((uint8_t*)&id)[1] << ((uint8_t*)&id)[2] << ((uint8_t*)&id)[3] << std::endl;

    const uint16_t flags = ID3V2_DECODE_FRAME_FLAGS(ID3V2_DATA_OFFSET(data, ID3V2_FRAME_FLAGS_OFFSET), ID3V2_FRAME_FLAGS_SIZE);
    std::cout << IndentString(indentLevel) << "Flags:   0x" << std::hex << std::setw(4) << std::setfill('0') << flags << std::endl;

    const uint32_t size = ID3V2_DECODE_FRAME_SIZE(ID3V2_DATA_OFFSET(data, ID3V2_FRAME_SIZE_OFFSET), ID3V2_FRAME_SIZE_SIZE);
    std::cout << IndentString(indentLevel) << "Size:    0x" << std::hex << std::setw(8) << std::setfill('0') << size << " (" << std::dec << size << ")"
              << std::endl;

    static const uint32_t ID3V2_MAX_DATA_DISPLAY_SIZE = 512;
    static const size_t ID3V2_MAX_DATA_ROW_SIZE       = 32;

    std::cout << IndentString(indentLevel) << "Data:" << std::endl;
    HexDump(indentLevel, ID3V2_DATA_OFFSET(data, ID3V2_FRAME_DATA_OFFSET), std::min(size, ID3V2_MAX_DATA_DISPLAY_SIZE), ID3V2_MAX_DATA_ROW_SIZE);

    std::cout << std::endl;

    // Print sub-frames
    if (CompareRawFrameId(id, "CHAP", ID3V2_FRAME_ID_SIZE) == true) {
        size_t subframeOffset = ComputeSubframeOffset(data, ID3V2_FRAME_HEADER_SIZE + size);
        while (subframeOffset < size) {
            const uint8_t* subframeData = &data[subframeOffset];
            const size_t subFrameSize   = DumpRawFrame(indentLevel + 1, subframeData, size);
            subframeOffset += subFrameSize;
        }
    }

    return ID3V2_FRAME_HEADER_SIZE + size;
}

bool FrameController::CompareRawFrameId(const uint32_t rawFrameId, const char* frameId, const size_t frameIdSize)
{
    PRECONDITION_RETURN(frameId != nullptr, false);
    PRECONDITION_RETURN(frameIdSize > 0, false);
    PRECONDITION_RETURN(frameIdSize <= ID3V2_FRAME_ID_SIZE, false);

    const uint32_t id = ID3V2_DECODE_FRAME_ID(reinterpret_cast<const uint8_t*>(frameId), frameIdSize);
    return (id == rawFrameId);
}

std::ostream& operator<<(std::ostream& os, const Frame* pFrame)
{
    PRECONDITION_RETURN(pFrame != 0, os);

    const uint32_t id = pFrame->Id();
    std::cout << "FrameId: " << ((uint8_t*)&id)[0] << ((uint8_t*)&id)[1] << ((uint8_t*)&id)[2] << ((uint8_t*)&id)[3] << std::endl;

    const uint32_t size = pFrame->Size();
    std::cout << "Size:  0x" << std::hex << std::setw(8) << std::setfill('0') << size << " (" << std::dec << size << ")" << std::endl;

    const uint16_t flags = pFrame->Flags();
    std::cout << "Flags: 0x" << std::hex << std::setw(4) << std::setfill('0') << flags << std::endl;

    return os;
}
}}} // namespace ultraschall::tools::chapdbg
