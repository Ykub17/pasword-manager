#pragma once

#include <vector>
#include <string>
#include <cstddef>

class SodiumCrypto {
public:
    static void init();

    static void generate_salt(unsigned char* salt, size_t size);
    static void generate_nonce(unsigned char* nonce, size_t size);

    static void derive_key(
        unsigned char* key,
        size_t key_size,
        const char* password,
        const unsigned char* salt
    );

    static std::vector<unsigned char> encrypt(
        const std::vector<unsigned char>& plaintext,
        const unsigned char* nonce,
        const unsigned char* key
    );

    static std::vector<unsigned char> decrypt(
        const std::vector<unsigned char>& ciphertext,
        const unsigned char* nonce,
        const unsigned char* key
    );
};
