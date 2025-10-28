# Twofish PDF Encryptor

A C++ application for encrypting and decrypting PDF documents using the Twofish symmetric key block cipher.

## Features

- Encrypt PDF files with Twofish algorithm
- Decrypt encrypted PDF files
- Qt-based GUI for easy operation
- Cross-platform support

## Requirements

- Qt5
- CMake 3.16 or higher
- C++17 compatible compiler

## Building

1. Clone the repository
2. Create a build directory: `mkdir build && cd build`
3. Run CMake: `CMAKE_PREFIX_PATH=/opt/homebrew/opt/qt@5 cmake ..`
4. Build: `make`

## Usage

1. Run the application: `./bin/TwofishPDFEncryptor`
2. Select input PDF file
3. Select output PDF file
4. Enter encryption/decryption key
5. Click Encrypt or Decrypt

## Project Structure

- `include/`: Header files
- `src/`: Source files
- `ui/`: Qt UI files
- `data/`: Sample data
- `build/`: Build directory

