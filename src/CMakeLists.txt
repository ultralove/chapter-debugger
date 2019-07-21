################################################################################
#
# Copyright (c) The Ultraschall Project (http://ultraschall.fm)
#
# The MIT License
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
################################################################################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FRAMEWORK_INCLUDES
  Guid.h
	SharedObject.h
	SequentialStream.h
	Common.h
	StringUtilities.h
	FileUtilities.h
	PlatformUtilities.h
)

set(FRAMEWORK_SOURCES
  Guid.cpp
	SequentialStream.cpp
	StringUtilities.cpp
	FileUtilities.cpp
)

set(ID3V2_INCLUDES
	ID3V2.h
	ID3V2_Frame.h
	ID3V2_FrameData.h
	ID3V2_FrameResource.h
	ID3V2_FrameFactory.h
	ID3V2_FrameController.h
	ID3V2_FrameUtilities.h
	ID3V2_COMM_Frame.h
	ID3V2_Header.h
)

set(ID3V2_SOURCES
	ID3V2.cpp
	ID3V2_Frame.cpp
	ID3V2_FrameData.cpp
	ID3V2_FrameFactory.cpp
	ID3V2_FrameController.cpp
	ID3V2_FrameUtilities.cpp
	ID3V2_COMM_Frame.cpp
	ID3V2_Header.cpp
)

# set(APPLICATION_INCLUDES)

set(APPLICATION_SOURCES
	main.cpp
)

add_executable(ultraschall-norad
	${FRAMEWORK_INCLUDES}
	${FRAMEWORK_SOURCES}
	${ID3V2_INCLUDES}
	${ID3V2_SOURCES}
	${APPLICATION_INCLUDES}
	${APPLICATION_SOURCES}
)

target_link_libraries(ultraschall-norad rpcrt4.lib)
