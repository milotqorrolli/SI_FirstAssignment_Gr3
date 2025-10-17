#include "pdf_encryptor.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "Usage: cli_roundtrip <key> <input-pdf>\n";
        return 2;
    }

    std::string key = argv[1];
    std::string input = argv[2];
    std::string encrypted = "encrypted.bin";
    std::string decrypted = "decrypted_from_cli.pdf";

    PDFEncryptor enc(key);
    bool ok = enc.encryptPDF(input, encrypted);
    if (!ok)
    {
        std::cerr << "Encryption failed" << std::endl;
        return 3;
    }

    bool ok2 = enc.decryptPDF(encrypted, decrypted);
    if (!ok2)
    {
        std::cerr << "Decryption failed" << std::endl;
        return 4;
    }

    // Compare files
    std::ifstream f1(input, std::ios::binary);
    std::ifstream f2(decrypted, std::ios::binary);
    if (!f1 || !f2)
    {
        std::cerr << "Failed to open files for comparison" << std::endl;
        return 5;
    }
    std::vector<char> b1((std::istreambuf_iterator<char>(f1)), std::istreambuf_iterator<char>());
    std::vector<char> b2((std::istreambuf_iterator<char>(f2)), std::istreambuf_iterator<char>());
    if (b1 == b2)
    {
        std::cout << "OK: round-trip identical" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Mismatch: round-trip differs" << std::endl;
        return 1;
    }
}
