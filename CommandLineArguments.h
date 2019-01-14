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

#ifndef __ULTRASCHALL_COMMAND_LINE_ARGUMENTS_H_INCL__
#define __ULTRASCHALL_COMMAND_LINE_ARGUMENTS_H_INCL__

#include "Common.h"
#include "StringUtilities.h"

class CommandLineArguments
{
public:
    CommandLineArguments();

    static CommandLineArguments Parse(int argc, char** argv, const bool includeArg0 = false);
    static CommandLineArguments Parse(const ultraschall::framework::StringArray& args);

    inline const std::string& FileName() const;
    inline bool DumpTags() const;
    inline bool DryRun() const;

private:
    std::string fileName_;
    bool        dumpTags_ = false;
    bool        dryRun_ = false;

    static void PrintVersion();
    static void PrintHelp();
};

inline const std::string& CommandLineArguments::FileName() const
{
    return fileName_;
}

inline bool CommandLineArguments::DumpTags() const
{
    return dumpTags_;
}

inline bool CommandLineArguments::DryRun() const
{
    return dryRun_;
}

#endif // #ifndef __ULTRASCHALL_COMMAND_LINE_ARGUMENTS_H_INCL__
