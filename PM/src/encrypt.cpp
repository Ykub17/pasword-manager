#include "sodium_crypto.hpp"
#include "user_io.h"
#include "encryption.hpp"


void encrypt_file(const std::string& input, const std::string& output, const char* password)
{
    SodiumCrypto crypto;
    crypto.init();

    constexpr size_t SALT_SIZE  = CryptoConfig::SALT_SIZE;
    constexpr size_t NONCE_SIZE = CryptoConfig::NONCE_SIZE;
    constexpr size_t KEY_SIZE   = CryptoConfig::KEY_SIZE;

    auto plaintext = read_file(input);

    unsigned char salt[SALT_SIZE];
    unsigned char nonce[NONCE_SIZE];
    unsigned char key[KEY_SIZE];

    crypto.generate_salt(salt, SALT_SIZE);
    crypto.generate_nonce(nonce, NONCE_SIZE);
    crypto.derive_key(key, KEY_SIZE, password, salt);

    auto ciphertext = crypto.encrypt(plaintext, nonce, key);

    std::vector<unsigned char> out;
    out.insert(out.end(), salt, salt + SALT_SIZE);
    out.insert(out.end(), nonce, nonce + NONCE_SIZE);
    out.insert(out.end(), ciphertext.begin(), ciphertext.end());

    write_file(output, out);
}
