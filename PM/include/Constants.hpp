#pragma once
#include <sodium.h>
#include <cstddef>

namespace CryptoConfig {
    // Використовуємо системні константи libsodium для максимальної сумісності
    inline constexpr size_t SALT_SIZE  = crypto_pwhash_SALTBYTES;           // 16
    inline constexpr size_t NONCE_SIZE = crypto_aead_xchacha20poly1305_ietf_NPUBBYTES; // 24
    inline constexpr size_t KEY_SIZE   = crypto_aead_xchacha20poly1305_ietf_KEYBYTES;  // 32
    inline constexpr size_t MAC_SIZE   = crypto_aead_xchacha20poly1305_ietf_ABYTES;    // 16 (тег автентифікації)
}