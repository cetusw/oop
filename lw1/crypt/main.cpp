#include <cstdint>
#include <fstream>
#include <iostream>
#include <cstring>

constexpr int MIN_KEY_VALUE = 0;
constexpr int MAX_KEY_VALUE = 255;

enum class CryptMode
{
    Encrypt,
    Decrypt,
};

void CheckNumberOfArguments(const int numberOfArguments)
{
    if (numberOfArguments != 5)
    {
        throw std::invalid_argument("ERROR");
    }
}

void CheckKeyValue(const int keyValue)
{
    if (keyValue < MIN_KEY_VALUE || keyValue > MAX_KEY_VALUE)
    {
        throw std::invalid_argument("ERROR");
    }
}

uint8_t MixBits(const uint8_t byte)
{
    uint8_t result = 0;
    result |= (byte & 0x80) >> 2;
    result |= (byte & 0x40) >> 5;
    result |= (byte & 0x20) >> 5;
    result |= (byte & 0x10) << 3;
    result |= (byte & 0x08) << 3;
    result |= (byte & 0x04) << 2;
    result |= (byte & 0x02) << 2;
    result |= (byte & 0x01) << 2;
    return result;
}

uint8_t ReverseMixBits(const uint8_t byte)
{
    uint8_t result = 0;
    result |= (byte & 0x20) << 2;
    result |= (byte & 0x02) << 5;
    result |= (byte & 0x01) << 5;
    result |= (byte & 0x80) >> 3;
    result |= (byte & 0x40) >> 3;
    result |= (byte & 0x10) >> 2;
    result |= (byte & 0x08) >> 2;
    result |= (byte & 0x04) >> 2;
    return result;
}

void Encrypt(uint8_t &byte, const uint8_t key)
{
    byte ^= key;
    byte = MixBits(byte);
}

void Decrypt(uint8_t &byte, const uint8_t key)
{
    byte = ReverseMixBits(byte);
    byte ^= key;
}

void Crypt(CryptMode mode, const std::string &inputFilePath, const std::string &outputFilePath, uint8_t key)
{
    std::ifstream input(inputFilePath, std::ios::binary);
    std::ofstream output(outputFilePath, std::ios::binary);

    if (!input.is_open() || !output.is_open())
    {
        throw std::invalid_argument("ERROR");
    }

    char buffer;
    while (input.get(buffer))
    {
        auto byte = static_cast<uint8_t>(buffer);

        if (mode == CryptMode::Encrypt)
        {
            Encrypt(byte, key);
        }

        if (mode == CryptMode::Decrypt)
        {
            Decrypt(byte, key);
        }

        output.put(static_cast<char>(byte));
    }
}

CryptMode getCryptMode(const char *value)
{
    if (std::strcmp(value, "encrypt") == 0)
    {
        return CryptMode::Encrypt;
    }
    if (std::strcmp(value, "decrypt") == 0)
    {
        return CryptMode::Decrypt;
    }
    throw std::invalid_argument("ERROR");
}

int main(const int argc, char *argv[])
{
    try
    {
        CheckNumberOfArguments(argc);
        const CryptMode cryptMode = getCryptMode(argv[1]);
        int key;
        try
        {
            key = std::stoi(argv[4]);
        }
        catch (std::invalid_argument &e)
        {
            throw std::invalid_argument("ERROR");
        }
        CheckKeyValue(key);
        const std::string inputFilePath = argv[2];
        const std::string outputFilePath = argv[3];
        Crypt(cryptMode, inputFilePath, outputFilePath, static_cast<uint8_t>(key));
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}


// вынести в константу crypt mode
// вынести константы макс и мин значений, написать тесты
