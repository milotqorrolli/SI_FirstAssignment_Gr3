#ifndef TWOFISH_ENCRYPTOR_HPP
#define TWOFISH_ENCRYPTOR_HPP

#include <vector>
#include <string>
#include <cstdint>

//  Twofish
class TwofishEncryptor
{
public:
    // Construct with a key (arbitrary length). Key is normalized internally
    // to one of Twofish's supported sizes (16, 24, 32 bytes).
    TwofishEncryptor(const std::vector<uint8_t> &key);

    ~TwofishEncryptor();

    // Crypto++ implementation the returned vector is IV (16 bytes) + cipher.
    std::vector<uint8_t> encrypt(const std::vector<uint8_t> &plaintext);

    std::vector<uint8_t> decrypt(const std::vector<uint8_t> &ciphertext);

private:
    // Implementation internals for a full Twofish implementation.
    std::vector<uint32_t> keySchedule;
    std::vector<uint8_t> sBox0, sBox1;
    std::vector<uint8_t> keyBytes;

    void keyScheduleGeneration(const std::vector<uint8_t> &key);

    // Block-level encrypt/decrypt helpers (operate on one Twofish block).
    std::vector<uint8_t> blockEncrypt(const std::vector<uint8_t> &block);
    std::vector<uint8_t> blockDecrypt(const std::vector<uint8_t> &block);

    // Helper math functions used by a native Twofish implementation.
    uint32_t hFunction(uint32_t x, const std::vector<uint32_t> &l, int k);
    uint32_t mdsMultiply(uint32_t x, uint32_t y);
    uint32_t rsMultiply(uint32_t x, uint32_t y);
};

#endif
