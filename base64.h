#ifndef BASE64_H
#define BASE64_H

#include <iostream>
#include <string>

class Base64Converter {
public:
    // Encodes data from an input stream and writes to an output stream.
    static void encode(std::istream& is, std::ostream& os);

    // Decodes data from an input stream and writes to an output stream.
    static void decode(std::istream& is, std::ostream& os);
};

#endif // BASE64_H
