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

#include "BinaryStream.h"
#include "Common.h"
#include "FileUtilities.h"
#include "FrameController.h"
#include "Globals.h"

#include <CLI11.hpp>

namespace dbg     = ultraschall::tools::chapdbg;

bool suppressLogo = false;
bool printVersion = false;
bool rawFrames    = false;

void PrintLogo();
void PrintVersion();
void PrintError(const std::string& errorMessage);

int g = 0;

int main(int argc, char** argv)
{
   // CLI::App app{"Ultraschall ID3v2 Frame Analyzer version 0.1.0 for x64"};
   CLI::App app;
   app.allow_extras();
   app.add_flag("--nologo", suppressLogo, "Do not display the startup banner and copyright message");
   app.add_flag("--version", printVersion, "Display compiler version information");
   app.add_flag("-r,--raw", rawFrames, "Print unprocessed frame data");

   std::string errorMessage;
   int errorCode = 0;
   try {
      app.parse(argc, argv);
      PrintLogo();
      PrintVersion();
   }
   catch (const CLI::ParseError& e) {
      PrintLogo();
      PrintVersion();
      app.exit(e);
   }

   if (app.remaining_size() > 0) {
      for (std::string arg : app.remaining()) {
         if (dbg::FileExists(arg) == true) {
            dbg::FrameController controller;
            dbg::BinaryStream stream = dbg::ReadFile(arg);
            if (false == rawFrames) {
               dbg::FrameList frames = controller.ParseFrames(stream);
            }
            else {
               dbg::FrameController::DumpRawFrames(stream);
            }
         }
         else {
            errorMessage = "Can't open '" + arg + "' for read.";
            PrintError(errorMessage);
         }
      }
   }
   else {
      std::cout << app.help() << std::endl;
   }

   return 0;
}

void PrintLogo()
{
   if ((false == suppressLogo) && (false == printVersion)) {
      std::cout << "Ultraschall ID3v2 Frame Analyzer version " << dbg::Globals::version << std::endl
                << "Copyright (c) ultraschall.fm. All rights reserved." << std::endl
                << std::endl;
   }
}

void PrintVersion()
{
   if (true == printVersion) {
      std::cout << dbg::Globals::version << std::endl << std::endl;
   }
}

void PrintError(const std::string& errorMessage)
{
   std::cout << errorMessage << std::endl;
   std::cout << "Run with --help for more information." << std::endl << std::endl;
}
