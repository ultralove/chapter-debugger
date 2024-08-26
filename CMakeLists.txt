################################################################################
#
# Copyright (c) ultralove contributors (https://github.com/ultralove)
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

cmake_minimum_required(VERSION 3.23)
project(norad VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(NORAD_TARGET_SYSTEM "windows")
elseif(APPLE)
    set(NORAD_TARGET_SYSTEM "darwin")
elseif(UNIX)
  execute_process(COMMAND uname -a RESULT_VARIABLE UNAME_RESULT OUTPUT_VARIABLE UNAME_OUTPUT OUTPUT_STRIP_TRAILING_WHITESPACE)
  if(UNAME_RESULT EQUAL 0)
    if(${UNAME_OUTPUT} MATCHES "[U|u]buntu")
        set(NORAD_TARGET_SYSTEM "linux")
    else()
      message(WARNING "Unsupported platform: " ${UNAME_OUTPUT} ". Supported platforms are Windows, Darwin and Ubuntu Linux.")
    endif()
  else()
    message(WARNING "Failed to run uname, result: ${UNAME_RESULT}")
  endif()
else()
  message(FATAL_ERROR "Unsupported platform: " ${UNAME_OUTPUT} ". Supported platforms are Windows, Darwin and Ubuntu Linux.")
endif()

if(${NORAD_TARGET_SYSTEM} STREQUAL "darwin")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12)
    message(STATUS "Building for x86_64 using clang ${CMAKE_CXX_COMPILER_VERSION}.")
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE INTERNAL "")
    set(CMAKE_OSX_ARCHITECTURES x86_64 CACHE INTERNAL "")
    add_compile_options(-mmacosx-version-min=10.13)
  else()
    message(STATUS "Building for x86_64 and arm64 using clang ${CMAKE_CXX_COMPILER_VERSION}.")
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15 CACHE INTERNAL "")
    set(CMAKE_OSX_ARCHITECTURES arm64 x86_64 CACHE INTERNAL "")
    add_compile_options(-mmacosx-version-min=10.15)
  endif()
endif()

include(FetchContent)

set(FETCHCONTENT_QUIET   ON)
set(FETCHCONTENT_VERBOSE OFF)

set(LIBCLI11_URL        "https://github.com/CLIUtils/CLI11.git")
set(LIBCLI11_VERSION    "v2.4.1")

FetchContent_Declare(libcli11
  GIT_REPOSITORY ${LIBCLI11_URL}
  GIT_SHALLOW    ON
  GIT_PROGRESS   OFF
  GIT_TAG        ${LIBCLI11_VERSION}
)
FetchContent_GetProperties(libcli11)
if(NOT libcli11_POPULATED)
  FetchContent_Populate(libcli11)
  set(LIBCLI11_INCLUDE_PATH ${libcli11_SOURCE_DIR}/include)
  set(CLI11_SINGLE_FILE     OFF CACHE INTERNAL "")
  set(CLI11_BUILD_DOCS      OFF CACHE INTERNAL "")
  set(CLI11_BUILD_TESTS     OFF CACHE INTERNAL "")
  set(CLI11_BUILD_EXAMPLES  OFF CACHE INTERNAL "")
  add_subdirectory(${libcli11_SOURCE_DIR} ${libcli11_BINARY_DIR})
endif()

message(STATUS "LIBCLI11_INCLUDE_PATH    = ${LIBCLI11_INCLUDE_PATH}")
message(STATUS "LIBCLI11_LIBRARY_PATH    = ${LIBCLI11_LIBRARY_PATH}")

include_directories(
  ${LIBCLI11_INCLUDE_PATH}
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(src)

# binary goes to '${CMAKE_INSTALL_PREFIX}/bin' by default, this is '/usr/local/bin'.
install(TARGETS norad DESTINATION bin)
