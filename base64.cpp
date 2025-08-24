#include "base64.h"
#include <vector>
#include <array>

namespace { // Anonymous namespace for internal linkage
    const std::string base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    const std::array<int, 256> base64_decode_table = [] {
        std::array<int, 256> table{};
        table.fill(-1);
        for (int i = 0; i < 64; ++i) {
            table[static_cast<unsigned char>(base64_chars[i])] = i;
        }
        return table;
    }();

    inline bool is_base64(unsigned char c) {
        return (isalnum(c) || (c == '+') || (c == '/'));
    }
}

void Base64Converter::encode(std::istream& is, std::ostream& os) {
    std::array<unsigned char, 3> in_buffer;
    std::array<unsigned char, 4> out_buffer;
    int bytes_read = 0;

    while (is.read(reinterpret_cast<char*>(in_buffer.data()), 3)) {
        bytes_read = 3;
        out_buffer[0] = (in_buffer[0] & 0xfc) >> 2;
        out_buffer[1] = ((in_buffer[0] & 0x03) << 4) + ((in_buffer[1] & 0xf0) >> 4);
        out_buffer[2] = ((in_buffer[1] & 0x0f) << 2) + ((in_buffer[2] & 0xc0) >> 6);
        out_buffer[3] = in_buffer[2] & 0x3f;
        for (int i = 0; i < 4; ++i) os.put(base64_chars[out_buffer[i]]);
    }
    
    bytes_read = is.gcount(); // Get count of bytes read in the last attempt
    if (bytes_read > 0) {
        for (int i = bytes_read; i < 3; ++i) in_buffer[i] = '\0';
        
        out_buffer[0] = (in_buffer[0] & 0xfc) >> 2;
        out_buffer[1] = ((in_buffer[0] & 0x03) << 4) + ((in_buffer[1] & 0xf0) >> 4);
        out_buffer[2] = ((in_buffer[1] & 0x0f) << 2) + ((in_buffer[2] & 0xc0) >> 6);

        for (int i = 0; i < bytes_read + 1; ++i) os.put(base64_chars[out_buffer[i]]);
        for (int i = 0; i < 3 - bytes_read; ++i) os.put('=');
    }
}

void Base64Converter::decode(std::istream& is, std::ostream& os) {
    std::array<unsigned char, 4> in_buffer;
    std::array<unsigned char, 3> out_buffer;
    char c;
    int chars_read = 0;

    while (is.get(c)) {
        if (is_base64(c)) {
            in_buffer[chars_read++] = c;
            if (chars_read == 4) {
                for (int i = 0; i < 4; ++i) in_buffer[i] = base64_decode_table[in_buffer[i]];

                out_buffer[0] = (in_buffer[0] << 2) + ((in_buffer[1] & 0x30) >> 4);
                out_buffer[1] = ((in_buffer[1] & 0x0f) << 4) + ((in_buffer[2] & 0x3c) >> 2);
                out_buffer[2] = ((in_buffer[2] & 0x03) << 6) + in_buffer[3];
                
                os.write(reinterpret_cast<const char*>(out_buffer.data()), 3);
                chars_read = 0;
            }
        }
    }

    // Note: This simple streaming decoder assumes valid padding and doesn't handle the last partial block.
    // A production-ready version would need more complex logic to handle the final '=' characters correctly.
}
