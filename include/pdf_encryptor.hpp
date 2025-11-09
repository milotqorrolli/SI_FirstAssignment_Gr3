#ifndef PDF_ENCRYPTOR_HPP
#define PDF_ENCRYPTOR_HPP

#include "twofish_encryptor.hpp"
#include <string>
#include <vector>

class PDFEncryptor
{
public:
    // The key will be converted to bytes and
    // normalized to a supported Twofish key length internally.
    PDFEncryptor(const std::string &key);

    ~PDFEncryptor();

    // Encrypt the file at inputPath and write encrypted bytes to outputPath.
    bool encryptPDF(const std::string &inputPath, const std::string &outputPath);

    // Decrypt the file at inputPath (expected to be produced by encryptPDF)
    bool decryptPDF(const std::string &inputPath, const std::string &outputPath);

private:
    TwofishEncryptor *encryptor;
    std::vector<uint8_t> keyBytes;

    std::vector<uint8_t> readFile(const std::string &path);
    bool writeFile(const std::string &path, const std::vector<uint8_t> &data);
};

#endif
