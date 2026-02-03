#pragma once

#include <vector>
#include <string>
#include <cstddef>
#include <sodium.h>

namespace CryptoConfig {
    // Використовуємо системні константи libsodium для максимальної сумісності
    inline constexpr size_t SALT_SIZE  = crypto_pwhash_SALTBYTES;           // 16
    inline constexpr size_t NONCE_SIZE = crypto_aead_xchacha20poly1305_ietf_NPUBBYTES; // 24
    inline constexpr size_t KEY_SIZE   = crypto_aead_xchacha20poly1305_ietf_KEYBYTES;  // 32
    inline constexpr size_t MAC_SIZE   = crypto_aead_xchacha20poly1305_ietf_ABYTES;    // 16 (тег автентифікації)
}
class SodiumCrypto {
public:
     void init();

    void generate_salt(unsigned char* salt, size_t size);
    void generate_nonce(unsigned char* nonce, size_t size);

    void derive_key(
        unsigned char* key,
        size_t key_size,
        const char* password,
        const unsigned char* salt
    );

    std::vector<unsigned char> encrypt(
        const std::vector<unsigned char>& plaintext,
        const unsigned char* nonce,
        const unsigned char* key
    );

    std::vector<unsigned char> decrypt(
        const std::vector<unsigned char>& ciphertext,
        const unsigned char* nonce,
        const unsigned char* key
    );
};
