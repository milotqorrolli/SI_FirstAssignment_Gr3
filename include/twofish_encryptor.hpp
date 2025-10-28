#ifndef TWOFISH_ENCRYPTOR_HPP
#define TWOFISH_ENCRYPTOR_HPP

#include <vector>
#include <string>
#include <cstdint>

class TwofishEncryptor
{
public:
    TwofishEncryptor(const std::vector<uint8_t> &key);
    ~TwofishEncryptor();

    std::vector<uint8_t> encrypt(const std::vector<uint8_t> &plaintext);
    std::vector<uint8_t> decrypt(const std::vector<uint8_t> &ciphertext);

private:
    // internal details will be added later
};

#endif // TWOFISH_ENCRYPTOR_HPP