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
    // Twofish internal data
    std::vector<uint32_t> keySchedule;  // key schedule words
    std::vector<uint8_t> sBox0;         // first substitution box
    std::vector<uint8_t> sBox1;         // second substitution box

    void keyScheduleGeneration(const std::vector<uint8_t> &key);
    std::vector<uint8_t> blockEncrypt(const std::vector<uint8_t> &block);
    std::vector<uint8_t> blockDecrypt(const std::vector<uint8_t> &block);

    // Helper math for Twofish
    uint32_t hFunction(uint32_t x, const std::vector<uint32_t> &l, int k);
    uint32_t mdsMultiply(uint32_t x, uint32_t y);
    uint32_t rsMultiply(uint32_t x, uint32_t y);

public:
    // Inline constructor and destructor for simple init/destroy
    inline TwofishEncryptor(const std::vector<uint8_t> &key)
    {
        keyScheduleGeneration(key); // initialize schedule
    }

    inline ~TwofishEncryptor() = default;
};

#endif // TWOFISH_ENCRYPTOR_HPP