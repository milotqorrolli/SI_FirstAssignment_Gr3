#include "twofish_encryptor.hpp"
#include <iostream>
#include <string>

#ifdef USE_CRYPTOPP
#include <cryptopp/twofish.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>

using namespace CryptoPP;

TwofishEncryptor::TwofishEncryptor(const std::vector<uint8_t> &key)
{
    // store key and normalize length to one of Twofish's supported sizes: 16, 24, or 32 bytes
    keyBytes = key;
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
}

TwofishEncryptor::~TwofishEncryptor() {}

// Return ciphertext with a 16-byte IV prepended
std::vector<uint8_t> TwofishEncryptor::encrypt(const std::vector<uint8_t> &plaintext)
{
    AutoSeededRandomPool prng;
    SecByteBlock iv(Twofish::BLOCKSIZE);
    prng.GenerateBlock(iv, iv.size());

    std::string cipher;
    try
    {
        CBC_Mode<Twofish>::Encryption enc(keyBytes.data(), (unsigned int)keyBytes.size(), iv);
        StringSource ss(plaintext.data(), plaintext.size(), true,
                        new StreamTransformationFilter(enc,
                                                       new StringSink(cipher),
                                                       StreamTransformationFilter::PKCS_PADDING));
    }
    catch (const Exception &e)
    {
        std::cerr << "Encryption error: " << e.what() << std::endl;
        return {};
    }

    std::vector<uint8_t> out;
    out.reserve(iv.size() + cipher.size());
    out.insert(out.end(), iv.BytePtr(), iv.BytePtr() + iv.size());
    out.insert(out.end(), cipher.begin(), cipher.end());
    return out;
}

// Expect ciphertext with IV prepended
std::vector<uint8_t> TwofishEncryptor::decrypt(const std::vector<uint8_t> &ciphertext)
{
    if (ciphertext.size() < Twofish::BLOCKSIZE)
        return {};
    const uint8_t *ivptr = ciphertext.data();
    const uint8_t *data = ciphertext.data() + Twofish::BLOCKSIZE;
    size_t dataLen = ciphertext.size() - Twofish::BLOCKSIZE;

    std::string recovered;
    try
    {
        CBC_Mode<Twofish>::Decryption dec(keyBytes.data(), (unsigned int)keyBytes.size(), ivptr);
        StringSource ss(data, dataLen, true,
                        new StreamTransformationFilter(dec,
                                                       new StringSink(recovered),
                                                       StreamTransformationFilter::PKCS_PADDING));
    }
    catch (const Exception &e)
    {
        std::cerr << "Decryption error: " << e.what() << std::endl;
        return {};
    }

    return std::vector<uint8_t>(recovered.begin(), recovered.end());
}

#else
#pragma message("Crypto++ not found: Twofish real implementation disabled. Install Crypto++ and re-run CMake for full functionality.")
#include <stdexcept>

// Fallback stubs: compile, but throw at runtime if used.
std::vector<uint8_t> TwofishEncryptor::encrypt(const std::vector<uint8_t> &)
{
    throw std::runtime_error("Crypto++ not available: encrypt not supported");
}

std::vector<uint8_t> TwofishEncryptor::decrypt(const std::vector<uint8_t> &)
{
    throw std::runtime_error("Crypto++ not available: decrypt not supported");
}

#endif
