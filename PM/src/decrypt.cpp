#include "sodium_crypto.hpp"
#include "user_io.h"
#include "encryption.hpp"


void decrypt_file(const std::string& input, const std::string& output, const char* password)
{
    SodiumCrypto crypto;
    crypto.init();

    constexpr size_t SALT_SIZE  = CryptoConfig::SALT_SIZE;
    constexpr size_t NONCE_SIZE = CryptoConfig::NONCE_SIZE;
    constexpr size_t KEY_SIZE   = CryptoConfig::KEY_SIZE;

    auto data = read_file(input);

    if (data.size() < SALT_SIZE + NONCE_SIZE)
        throw std::runtime_error("Invalid encrypted file");

    unsigned char salt[SALT_SIZE];
    unsigned char nonce[NONCE_SIZE];
    unsigned char key[KEY_SIZE];

    std::memcpy(salt, data.data(), SALT_SIZE);
    std::memcpy(nonce, data.data() + SALT_SIZE, NONCE_SIZE);

    crypto.derive_key(key, KEY_SIZE, password, salt);

    size_t offset = SALT_SIZE + NONCE_SIZE;

    std::vector<unsigned char> ciphertext(
        data.begin() + offset,
        data.end()
    );

    auto plaintext = crypto.decrypt(ciphertext, nonce, key);
    write_file(output, plaintext);
}
