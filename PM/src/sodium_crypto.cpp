#include "sodium_crypto.hpp"
#include <sodium.h>
#include <stdexcept>

void SodiumCrypto::init() {
    if (sodium_init() < 0) {
        throw std::runtime_error("libsodium init failed");
    }
}

void SodiumCrypto::generate_salt(unsigned char* salt, size_t size) {
    randombytes_buf(salt, size);
}

void SodiumCrypto::generate_nonce(unsigned char* nonce, size_t size) {
    randombytes_buf(nonce, size);
}

void SodiumCrypto::derive_key(
    unsigned char* key,
    size_t key_size,
    const char* password,
    const unsigned char* salt
) {
    if (crypto_pwhash(
            key,
            key_size,
            password,
            std::strlen(password),
            salt,
            crypto_pwhash_OPSLIMIT_MODERATE,
            crypto_pwhash_MEMLIMIT_MODERATE,
            crypto_pwhash_ALG_DEFAULT
        ) != 0)
    {
        throw std::runtime_error("Key derivation failed");
    }
}

std::vector<unsigned char> SodiumCrypto::encrypt(
    const std::vector<unsigned char>& plaintext,
    const unsigned char* nonce,
    const unsigned char* key
) {
    std::vector<unsigned char> ciphertext(
        plaintext.size() + crypto_aead_xchacha20poly1305_ietf_ABYTES
    );

    unsigned long long cipher_len = 0;

    crypto_aead_xchacha20poly1305_ietf_encrypt(
        ciphertext.data(),
        &cipher_len,
        plaintext.data(),
        plaintext.size(),
        nullptr,
        0,
        nullptr,
        nonce,
        key
    );

    ciphertext.resize(cipher_len);
    return ciphertext;
}

std::vector<unsigned char> SodiumCrypto::decrypt(
    const std::vector<unsigned char>& ciphertext,
    const unsigned char* nonce,
    const unsigned char* key
) {
    std::vector<unsigned char> plaintext(ciphertext.size());
    unsigned long long plain_len = 0;

    if (crypto_aead_xchacha20poly1305_ietf_decrypt(
            plaintext.data(),
            &plain_len,
            nullptr,
            ciphertext.data(),
            ciphertext.size(),
            nullptr,
            0,
            nonce,
            key
        ) != 0)
    {
        throw std::runtime_error("Wrong password or corrupted file");
    }

    plaintext.resize(plain_len);
    return plaintext;
}
