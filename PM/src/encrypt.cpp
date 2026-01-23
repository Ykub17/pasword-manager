
#include "sodium.h"
#include <vector>
#include <cstring>
#include <stdexcept>
#include <string>
#include "user_io.h"

void encrypt_file(const std::string& input, const std::string& output, const char* password) 
{
    constexpr size_t SALT_SIZE  = crypto_pwhash_SALTBYTES; // Довжина salt 16 байт
    constexpr size_t NONCE_SIZE = crypto_aead_xchacha20poly1305_ietf_NPUBBYTES; // Довжина nonce 24 байти
    constexpr size_t KEY_SIZE   = crypto_aead_xchacha20poly1305_ietf_KEYBYTES; // Довжина ключа 32 байти

    auto plaintext = read_file(input);// Читаємо вхідний файл

    unsigned char salt[SALT_SIZE], nonce[NONCE_SIZE], key[KEY_SIZE];// Оголошуємо масиви для salt, nonce та ключа
    randombytes_buf(salt, sizeof salt);// Генеруємо випадковий salt
    randombytes_buf(nonce, sizeof nonce);// Генеруємо випадковий nonce

    if (crypto_pwhash(key, KEY_SIZE, password, std::strlen(password),// Виводимо ключ з пароля
                      salt, crypto_pwhash_OPSLIMIT_MODERATE,// Встановлюємо обмеження на кількість операцій
                      crypto_pwhash_MEMLIMIT_MODERATE,// Встановлюємо обмеження на використання пам'яті
                      crypto_pwhash_ALG_DEFAULT) != 0) // Використовуємо стандартний алгоритм
    {
        throw std::runtime_error("Key derivation failed");// Викидаємо помилку, якщо виведення ключа не вдалося
    }

    std::vector<unsigned char> ciphertext(plaintext.size() +//Підготовка контейнера для зашифрованих даних
                                          crypto_aead_xchacha20poly1305_ietf_ABYTES);
    unsigned long long cipher_len;

    crypto_aead_xchacha20poly1305_ietf_encrypt//процес шифрування
    (
        ciphertext.data(), &cipher_len,// Вихідні параметри: зашифровані дані та їх довжина
        plaintext.data(), plaintext.size(),// Вхідні параметри: відкриті дані та їх довжина
        nullptr, 0, nullptr, 
        nonce, key// Використовуємо nonce та ключ для шифрування
    );

    std::vector<unsigned char> out;// Підготовка контейнера для вихідних даних
    out.insert(out.end(), salt, salt + SALT_SIZE);// Додаємо salt на початок
    out.insert(out.end(), nonce, nonce + NONCE_SIZE);// Додаємо nonce після salt
    out.insert(out.end(), ciphertext.begin(), ciphertext.begin() + cipher_len);// Додаємо зашифровані дані після nonce

    write_file(output, out);// Записуємо вихідні дані у файл
}
