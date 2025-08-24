#include "base64.h"
#include <iostream>
#include <fstream>
#include <string>
#include "cxxopts.hpp" // Library for argument parsing

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

void setup_binary_io_stdin() {
    #ifdef _WIN32
    _setmode(_fileno(stdin), _O_BINARY);
    #endif
}

void setup_binary_io_stdout() {
    #ifdef _WIN32
    _setmode(_fileno(stdout), _O_BINARY);
    #endif
}


int main(int argc, char* argv[]) {
    cxxopts::Options options("png64", "A robust Base64 encoder/decoder command-line tool.");

    options.add_options()
        ("d,decode", "Decode mode")
        ("i,input", "Input file (if omitted, uses stdin)", cxxopts::value<std::string>())
        ("o,output", "Output file (if omitted, uses stdout)", cxxopts::value<std::string>())
        ("v,version", "Print version")
        ("h,help", "Print usage");
    
    try {
        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return 0;
        }

        if (result.count("version")) {
            std::cout << "png64 version 2.0.0 (Optimal)" << std::endl;
            std::cout << "Author: alone_value" << std::endl;
            return 0;
        }

        bool decode_mode = result.count("decode");

        // --- Stream Management using RAII and Pointers ---
        std::ifstream fin;
        std::ofstream fout;

        std::istream* is = &std::cin; // Default to stdin
        std::ostream* os = &std::cout; // Default to stdout

        if (result.count("input")) {
            const auto& input_path = result["input"].as<std::string>();
            fin.open(input_path, std::ios::binary);
            if (!fin) {
                std::cerr << "Error: Cannot open input file: " << input_path << std::endl;
                return 1;
            }
            is = &fin;
        } else {
            setup_binary_io_stdin();
        }

        if (result.count("output")) {
            const auto& output_path = result["output"].as<std::string>();
            fout.open(output_path, std::ios::binary);
             if (!fout) {
                std::cerr << "Error: Cannot open output file: " << output_path << std::endl;
                return 1;
            }
            os = &fout;
        } else {
            setup_binary_io_stdout();
        }
        
        // --- Core Logic ---
        if (decode_mode) {
            Base64Converter::decode(*is, *os);
        } else {
            Base64Converter::encode(*is, *os);
        }

    } catch (const cxxopts::exceptions::exception& e) {
        std::cerr << "Error parsing options: " << e.what() << std::endl;
        return 1;
    }

    return 0; // fin and fout destructors are called here, closing files automatically.
}
