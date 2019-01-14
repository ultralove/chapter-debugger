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

#include "CommandLineArguments.h"

CommandLineArguments::CommandLineArguments() {}

CommandLineArguments CommandLineArguments::Parse(int argc, char** argv, const bool includeArg0)
{
    PRECONDITION_RETURN(argc > 0, CommandLineArguments());
    PRECONDITION_RETURN(argv != 0, CommandLineArguments());

    if(includeArg0 == false)
    {
        --argc;
        ++argv;
    }

    ultraschall::framework::StringArray args;
    for(int i = 0; i < argc; ++i)
    {
        args.push_back(argv[i]);
    }

    return Parse(args);
}

CommandLineArguments CommandLineArguments::Parse(const ultraschall::framework::StringArray& args)
{
    CommandLineArguments result;

    for(std::string arg : args)
    {
        std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
        if("--version" == arg)
        {
            PrintVersion();
            return CommandLineArguments();
        }
        else if("--help" == arg)
        {
            PrintHelp();
            return CommandLineArguments();
        }
        else if(("--dump" == arg) || ("-d" == arg))
        {
            result.dumpTags_ = true;
        }
        else if("--dryrun" == arg)
        {
            result.dryRun_ = true;
        }
        else // if(result.fileName_.empty() == true)
        {
            result.fileName_ = arg;
        }
    }

    return result;
}

void CommandLineArguments::PrintVersion()
{
    std::cout << "1.0.0-alpha1" << std::endl;
}

void CommandLineArguments::PrintHelp()
{
    std::cout << "ultraschall-norad <audio-file> []" << std::endl;
}
