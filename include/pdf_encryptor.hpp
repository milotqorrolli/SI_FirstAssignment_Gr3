#ifndef PDF_ENCRYPTOR_HPP
#define PDF_ENCRYPTOR_HPP

#include "twofish_encryptor.hpp"
#include <string>
#include <vector>

class PDFEncryptor {
public:
    PDFEncryptor(const std::string& key);
    ~PDFEncryptor();

    bool encryptPDF(const std::string& inputPath, const std::string& outputPath);
    bool decryptPDF(const std::string& inputPath, const std::string& outputPath);

private:
    TwofishEncryptor* encryptor;
    std::vector<uint8_t> keyBytes;

    std::vector<uint8_t> readFile(const std::string& path);
    bool writeFile(const std::string& path, const std::vector<uint8_t>& data);
};

#endif
