
#include "sodium.h"
#include <vector>
#include <cstring>
#include <stdexcept>
#include <string>
#include "user_io.h" 

void decrypt_file(const std::string& input, const std::string& output, const char* password) 
{
    constexpr size_t SALT_SIZE  = crypto_pwhash_SALTBYTES;// Довжина salt 16 байт
    constexpr size_t NONCE_SIZE = crypto_aead_xchacha20poly1305_ietf_NPUBBYTES;// Довжина nonce 24 байти
    constexpr size_t KEY_SIZE   = crypto_aead_xchacha20poly1305_ietf_KEYBYTES;// Довжина ключа 32 байти

    auto data = read_file(input);// Читаємо вхідний файл

    if (data.size() < SALT_SIZE + NONCE_SIZE)// Перевіряємо, чи достатньо даних для salt та nonce
        throw std::runtime_error("Invalid encrypted file");

    unsigned char salt[SALT_SIZE], nonce[NONCE_SIZE], key[KEY_SIZE];// Оголошуємо масиви для salt, nonce та ключа
    std::memcpy(salt, data.data(), SALT_SIZE);// Копіюємо salt з початку файлу
    std::memcpy(nonce, data.data() + SALT_SIZE, NONCE_SIZE);// Копіюємо nonce після salt

    if (crypto_pwhash(key, KEY_SIZE, password, std::strlen(password),// Виводимо ключ з пароля
                      salt, crypto_pwhash_OPSLIMIT_MODERATE,// Встановлюємо обмеження на кількість операцій
                      crypto_pwhash_MEMLIMIT_MODERATE,// Встановлюємо обмеження на використання пам'яті
                      crypto_pwhash_ALG_DEFAULT) != 0)
    {
        throw std::runtime_error("Key derivation failed");
    }

    size_t offset = SALT_SIZE + NONCE_SIZE;// Визначаємо початок зашифрованих даних
    size_t cipher_len = data.size() - offset;// Визначаємо довжину зашифрованих даних

    std::vector<unsigned char> plaintext(cipher_len);// Підготовка контейнера для розшифрованих даних
    unsigned long long plain_len;// Змінна для збереження довжини розшифрованих даних

    if (crypto_aead_xchacha20poly1305_ietf_decrypt//процес розшифрування
        (
            plaintext.data(), &plain_len,// Вихідні параметри: розшифровані дані та їх довжина
            nullptr,
            data.data() + offset, cipher_len,// Вхідні параметри: зашифровані дані та їх довжина
            nullptr, 0,
            nonce, key) != 0) // Використовуємо nonce та ключ для розшифрування
    {
        throw std::runtime_error("Wrong password or corrupted file");
    }

    plaintext.resize(plain_len);// Змінюємо розмір вектора відповідно до фактичної довжини розшифрованих даних
    write_file(output, plaintext);// Записуємо розшифровані дані у файл
}
