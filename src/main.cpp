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

#include "CLI11.hpp"

#include "FileUtilities.h"
#include "ID3V2.h"
#include "ID3V2_FrameController.h"
#include "ID3V2_FrameUtilities.h"

bool suppressLogo = false;
bool printVersion = false;
bool rawFrames    = false;

void        PrintLogo();
void        PrintVersion();
const char* Version();
void        PrintError(const std::string& errorMessage);

int main(int argc, char** argv)
{
    // CLI::App app{"Ultraschall ID3V2 Frame Analyzer version 0.1.0 for x64"};
    CLI::App app;
    app.allow_extras();
    app.add_flag("--nologo", suppressLogo, "Do not display the startup banner and copyright message");
    app.add_flag("--version", printVersion, "Display compiler version information");
    app.add_flag("-r,--raw", rawFrames, "Print unprocessed frame data");

    std::string errorMessage;
    int         errorCode = 0;
    try
    {
        app.parse(argc, argv);
        PrintLogo();
        PrintVersion();
    }
    catch(const CLI::ParseError& e)
    {
        PrintLogo();
        PrintVersion();
        app.exit(e);
    }

    for(std::string arg : app.remaining())
    {
        if(ultraschall::framework::FileExists(arg) == true)
        {
            ultraschall::framework::SequentialStream stream = ultraschall::framework::ReadFile(arg);
            if(rawFrames == false)
            {
                ultraschall::framework::ID3V2_FrameController::DumpFrames(stream);
            }
            else
            {
                ultraschall::framework::ID3V2_FrameController::DumpRawFrames(stream);
            }
        }
        else
        {
            errorMessage = "Can't open '" + arg + "' for read.";
            PrintError(errorMessage);
        }
    }

    return 0;
}

void PrintLogo()
{
    if((false == suppressLogo) && (false == printVersion))
    {
        std::cout << "Ultraschall ID3V2 Frame Analyzer for x64 version " << Version() << std::endl
                  << "Copyright (c) 2019 ultraschall.fm, All rights reserved." << std::endl
                  << std::endl;
    }
}

void PrintVersion()
{
    if(true == printVersion)
    {
        std::cout << Version() << std::endl << std::endl;
    }
}

const char* Version()
{
    return "0.1.0";
}

void PrintError(const std::string& errorMessage)
{
    std::cout << errorMessage << std::endl;
    std::cout << "Run with --help for more information." << std::endl << std::endl;
}
