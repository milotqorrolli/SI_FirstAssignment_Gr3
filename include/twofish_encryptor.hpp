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
    std::vector<uint32_t> keySchedule;
    std::vector<uint8_t> sBox0, sBox1;
    std::vector<uint8_t> keyBytes;

    void keyScheduleGeneration(const std::vector<uint8_t> &key);
    std::vector<uint8_t> blockEncrypt(const std::vector<uint8_t> &block);
    std::vector<uint8_t> blockDecrypt(const std::vector<uint8_t> &block);

    uint32_t hFunction(uint32_t x, const std::vector<uint32_t> &l, int k);
    uint32_t mdsMultiply(uint32_t x, uint32_t y);
    uint32_t rsMultiply(uint32_t x, uint32_t y);
};

#endif
