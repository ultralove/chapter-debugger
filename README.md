# ChapDBG - ID3v2 Frame Analyzer

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![CMake](https://img.shields.io/badge/CMake-3.23%2B-green.svg)](https://cmake.org/)

ChapDBG is a powerful command-line tool for analyzing ID3v2 metadata frames in audio files. Built with modern C++20, it provides detailed inspection capabilities for ID3v2 tags, supporting both processed and raw frame analysis.

## Features

- **Comprehensive ID3v2 Support**: Parse and analyze various ID3v2 frame types
- **Multiple Output Modes**: View processed frame data or raw binary dumps
- **Cross-Platform**: Windows, macOS, and Linux support
- **Modern C++**: Built with C++20 for performance and reliability
- **Flexible CLI**: User-friendly command-line interface with multiple options

### Supported Frame Types

- **Text Information Frames** (TIT2, TALB, TPE1, etc.)
- **URL Link Frames** (WCOM, WCOP, WOAF, etc.)
- **Attached Picture Frames** (APIC)
- **Chapter Frames** (CHAP)
- **Table of Contents Frames** (CTOC)
- **Comment Frames** (COMM)

## Quick Start

### Prerequisites

- **Compiler**: C++20 compatible compiler
  - GCC 10+ or Clang 12+ on Linux
  - Clang 12+ on macOS
  - MSVC 2019+ on Windows
- **Build System**: CMake 3.23 or later
- **Git**: For cloning the repository

### Installation

1. **Clone the repository**

   ```bash
   git clone https://github.com/ultralove/chapter-debugger.git
   cd chapter-debugger
   ```

2. **Build the project**

   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

3. **Install (optional)**

   ```bash
   sudo make install  # Installs to /usr/local/bin by default
   ```

### Basic Usage

```bash
# Analyze an audio file with ID3v2 tags
chapdbg your_audio_file.mp3

# View raw frame data
chapdbg --raw your_audio_file.mp3

# Multiple files
chapdbg song1.mp3 song2.mp3 album/*.mp3

# Suppress logo and show version
chapdbg --nologo --version
```

## Usage Examples

### Analyze ID3v2 Frames

```bash
$ chapdbg example.mp3
CHAPDBG - ID3v2 Frame Analyzer version 7.0.1
Copyright (c) Ultralove Contributors. All rights reserved.

[Frame analysis output will be displayed here]
```

### Raw Frame Inspection

```bash
$ chapdbg --raw example.mp3
[Raw binary frame data in hexadecimal format]
```

### Batch Processing

```bash
$ chapdbg *.mp3
[Processes all MP3 files in current directory]
```

## Command Line Options

| Option | Short | Description |
|--------|-------|-------------|
| `--nologo` | - | Suppress startup banner and copyright message |
| `--version` | - | Display version information |
| `--raw` | `-r` | Display unprocessed raw frame data |
| `--help` | `-h` | Show help information |

## Building from Source

### Development Setup

1. **Clone with dependencies**

   ```bash
   git clone https://github.com/ultralove/chapter-debugger.git
   cd chapter-debugger
   ```

2. **Configure build**

   ```bash
   mkdir build && cd build
   cmake -DCMAKE_BUILD_TYPE=Debug ..
   ```

3. **Build**

   ```bash
   cmake --build . --parallel
   ```

### Platform-Specific Notes

#### macOS

- **Universal Binary**: Automatic x86_64 + ARM64 support on Clang 12+
- **Minimum Target**: macOS 10.13 (x86_64) or 10.15 (Universal)

#### Linux (Ubuntu)

- Install build essentials: `sudo apt install build-essential cmake git`

#### Windows

- Use Visual Studio 2019+ or Build Tools
- CMake will automatically detect and configure MSVC

## Testing

```bash
# Run with sample files
cd build
./chapdbg ../test_files/*.mp3

# Test raw output
./chapdbg --raw ../test_files/sample.mp3
```

## Project Structure

```text
chapdbg/
├── CMakeLists.txt          # Main build configuration
├── LICENSE                 # MIT license
├── README.md              # This file
├── include/               # Public headers (if any)
└── src/                   # Source code
    ├── main.cpp           # Application entry point
    ├── ID3V2.{h,cpp}      # ID3v2 specification implementation
    ├── FrameController.{h,cpp}  # Frame parsing logic
    ├── BinaryStream.{h,cpp}     # Binary data handling
    ├── Frame.{h,cpp}      # Base frame class
    ├── *Frame.{h,cpp}     # Specific frame implementations
    ├── FileUtilities.{h,cpp}    # File I/O utilities
    └── ...                # Additional utilities
```

## Contributing

We welcome contributions! Please see our contributing guidelines:

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/amazing-feature`)
3. **Commit** your changes (`git commit -m 'Add amazing feature'`)
4. **Push** to the branch (`git push origin feature/amazing-feature`)
5. **Open** a Pull Request

### Development Guidelines

- Follow C++20 best practices and modern idioms
- Maintain consistent code style with existing codebase
- Add tests for new functionality
- Update documentation as needed
- Ensure cross-platform compatibility

## Requirements

### Runtime Requirements

- No external runtime dependencies (statically linked)

### Build Requirements

- C++20 compatible compiler
- CMake 3.23+
- Git (for dependency fetching)

### External Dependencies (Auto-fetched)

- [CLI11](https://github.com/CLIUtils/CLI11) v2.4.1 - Command line parsing

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Version Information

- **Current Version**: 7.0.1
- **ID3v2 Support**: Comprehensive frame type coverage
- **Build System**: CMake with modern C++ standards

## Issue Reporting

Found a bug or have a feature request? Please open an issue on our [GitHub Issues](https://github.com/heikopanjas/chapdbg/issues) page.

When reporting issues, please include:

- Operating system and version
- Compiler version
- Sample audio file (if applicable)
- Command line used
- Expected vs actual behavior

## Related Projects

- [Ultralove](https://github.com/ultralove) - Organization homepage
- [ID3v2 Specification](http://id3.org/id3v2.4.0-structure) - Official ID3v2.4 documentation

---

**ChapDBG** - Analyzing ID3v2 metadata with precision and performance.
