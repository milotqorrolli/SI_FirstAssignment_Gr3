#include "pdf_encryptor.hpp"
#include <fstream>
#include <iostream>

// Constructor: convert textual key to bytes and normalize length to a
// supported Twofish key size (16/24/32 bytes). Then create the
// TwofishEncryptor instance used for file encryption/decryption.
PDFEncryptor::PDFEncryptor(const std::string &key)
{
    keyBytes.assign(key.begin(), key.end());
    // Normalize key length to Twofish supported sizes (16, 24, 32)
    size_t k = keyBytes.size();
    if (k <= 16)
    {
        keyBytes.resize(16, 0);
    }
    else if (k <= 24)
    {
        keyBytes.resize(24, 0);
    }
    else if (k <= 32)
    {
        keyBytes.resize(32, 0);
    }
    else
    {
        keyBytes.resize(32);
    }
    encryptor = new TwofishEncryptor(keyBytes);
}

PDFEncryptor::~PDFEncryptor()
{
    delete encryptor;
}

// Read the input file, encrypt its bytes using the TwofishEncryptor,
// and write the encrypted output. Returns true on success.
bool PDFEncryptor::encryptPDF(const std::string &inputPath, const std::string &outputPath)
{
    std::vector<uint8_t> data = readFile(inputPath);
    if (data.empty())
    {
        std::cerr << "Failed to read input file." << std::endl;
        return false;
    }
    std::vector<uint8_t> encrypted = encryptor->encrypt(data);
    return writeFile(outputPath, encrypted);
}

// Read encrypted input (IV + ciphertext), decrypt it and write the
// resulting plaintext PDF bytes to outputPath. Returns true on success.
bool PDFEncryptor::decryptPDF(const std::string &inputPath, const std::string &outputPath)
{
    std::vector<uint8_t> data = readFile(inputPath);
    if (data.empty())
    {
        std::cerr << "Failed to read input file." << std::endl;
        return false;
    }
    std::vector<uint8_t> decrypted = encryptor->decrypt(data);
    return writeFile(outputPath, decrypted);
}

// Helper: read the entire file into a byte vector. Returns empty vector on
// failure.
std::vector<uint8_t> PDFEncryptor::readFile(const std::string &path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file)
    {
        return {};
    }
    return std::vector<uint8_t>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

// Helper: write a byte vector to a file. Returns true on success.
bool PDFEncryptor::writeFile(const std::string &path, const std::vector<uint8_t> &data)
{
    std::ofstream file(path, std::ios::binary);
    if (!file)
    {
        return false;
    }
    file.write(reinterpret_cast<const char *>(data.data()), data.size());
    return true;
}
