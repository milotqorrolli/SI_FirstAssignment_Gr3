#ifndef TWOFISH_ENCRYPTOR_HPP
#define TWOFISH_ENCRYPTOR_HPP

#include <vector>
#include <string>
#include <cstdint>

using namespace std;

class TwofishEncryptor
{
public:
    TwofishEncryptor(const vector<uint8_t> &key);
    ~TwofishEncryptor();

    vector<uint8_t> encrypt(const vector<uint8_t> &plaintext);
    vector<uint8_t> decrypt(const vector<uint8_t> &ciphertext);

private:
    // Twofish internal data
    vector<uint32_t> keySchedule;  // key schedule words
    vector<uint8_t> sBox0;         // first substitution box
    vector<uint8_t> sBox1;         // second substitution box

    void keyScheduleGeneration(const vector<uint8_t> &key);
    vector<uint8_t> blockEncrypt(const vector<uint8_t> &block);
    vector<uint8_t> blockDecrypt(const vector<uint8_t> &block);

    // Helper math for Twofish
    uint32_t hFunction(uint32_t x, const vector<uint32_t> &l, int k);
    uint32_t mdsMultiply(uint32_t x, uint32_t y);
    uint32_t rsMultiply(uint32_t x, uint32_t y);

public:
    // Inline constructor and destructor for simple init/destroy
    inline TwofishEncryptor(const vector<uint8_t> &key)
    {
        keyScheduleGeneration(key); // initialize schedule
    }

    inline ~TwofishEncryptor() = default;
};

#endif // TWOFISH_ENCRYPTOR_HPP