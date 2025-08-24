---

# png64 - A High-Performance Base64 CLI Tool

![Language](https://img.shields.io/badge/language-C%2B%2B17-blue.svg)
![Build](https://img.shields.io/badge/build-CMake-orange.svg)
![Platform](https://img.shields.io/badge/platform-cross--platform-lightgrey.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

`png64` is a modern, robust, and highly efficient command-line utility for Base64 encoding and decoding. Written in C++17, it is designed from the ground up for streaming I/O, making it suitable for handling very large files with minimal memory usage.

## Key Features

-   **🚀 Streaming Architecture**: Processes files in small chunks, maintaining a tiny, constant memory footprint regardless of file size. Perfect for multi-gigabyte files.
-   **⚡ High Performance**: Built with modern C++ and compiled with optimizations for maximum speed.
-   **🖥️ Full CLI Functionality**: Supports encoding and decoding, reading from files or standard input (stdin), and writing to files or standard output (stdout).
-   **⚙️ Cross-Platform**: Uses CMake for a consistent build experience on Linux, macOS, and Windows.
-   **🧩 Clean Codebase**: Organized into logical components with a clear separation between the core Base64 logic and the main application driver.
-   **🔗 Simple Dependency Management**: Automatically fetches and builds its only dependency (`cxxopts`) via CMake's `FetchContent`.

## Building from Source

### Prerequisites

-   A C++17 compatible compiler (e.g., GCC, Clang, MSVC)
-   [CMake](https://cmake.org/download/) (version 3.16 or higher)
-   [Git](https://git-scm.com/downloads/)

### Steps

1.  **Clone the repository:**
    ```sh
    git clone https://github.com/your-username/png64.git
    cd png64
    ```

2.  **Configure the project with CMake:**
    This command creates a `build` directory, configures the project, and downloads the `cxxopts` dependency.
    ```sh
    cmake -B build
    ```

3.  **Compile the source code:**
    This command builds the executable inside the `build` directory.
    ```sh
    cmake --build build
    ```

4.  **Done!**
    The executable can be found at `build/png64` (on Linux/macOS) or `build/Debug/png64.exe` (on Windows). You can copy it to a location in your `PATH` for system-wide access.

## Usage

### Synopsis

```
png64 [options] [input_file] [output_file]
```
-   If `input_file` is omitted or specified as `-`, the tool reads from standard input.
-   If `output_file` is omitted or specified as `-`, the tool writes to standard output.

### Options

| Option           | Alias | Description                                        |
| ---------------- | ----- | -------------------------------------------------- |
| `--decode`       | `-d`  | Decode data (the default is to encode).            |
| `--input <path>` | `-i`  | Specify the input file path.                       |
| `--output <path>`| `-o`  | Specify the output file path.                      |
| `--version`      | `-v`  | Display version and author information and exit.   |
| `--help`         | `-h`  | Display the help message and exit.                 |

### Examples

#### Encoding Examples

-   **Encode a file to another file:**
    ```sh
    ./build/png64 -i my_image.png -o b64.txt
    ```

-   **Encode a file and print the result to the screen (stdout):**
    ```sh
    ./build/png64 -i my_image.png
    ```

-   **Encode data from stdin (using a pipe) and save to a file:**
    ```sh
    cat my_image.png | ./build/png64 -o b64.txt
    ```

#### Decoding Examples

-   **Decode a file to another file:**
    ```sh
    ./build/png64 -d -i b64.txt -o my_image_restored.png
    ```

-   **Decode a file to stdout and redirect the output to a new file:**
    ```sh
    ./build/png64 -d -i b64.txt > my_image_restored.png
    ```

-   **Decode data from stdin (using a pipe) and save to a file:**
    ```sh
    cat b64.txt | ./build/png64 -d -o my_image_restored.png
    ```

## Project Structure

```
png64/
├── CMakeLists.txt     # Build script for CMake
├── README.md          # This file
├── main.cpp           # Main application logic (argument parsing, I/O)
├── base64.h           # Header for the Base64Converter class
└── base64.cpp           # Implementation of streaming Base64 logic
```

## License

This project is licensed under the MIT License.
