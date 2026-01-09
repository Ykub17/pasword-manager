#include <iostream>
#include "CLI11.hpp"         // Бібліотека для роботи з командним рядком
#include "encryption.hpp" // Шифрування
#include "description.hpp" // Дешифрування
#include "userIO.hpp"   // Взаємодія з користувачем

int main(int argc, char** argv) 
{
    CLI::App app("Програма для шифрування та дешифрування файлів");

    // 
    std::string filename;
    std::string password;

    // --- Налаштування команди шифрування ---
    auto enc_cmd = app.add_subcommand("encrypt", "шифрування файлу");
    enc_cmd->add_option("-f,--file", filename, "Шлях до вихідного файлу")->required();
    enc_cmd->add_option("-p,--password", password, "Пароль для шифрування")->required();

    // --- Налаштування команди дешифрування  ---
    auto dec_cmd = app.add_subcommand("decrypt", "дешифрування файлу");
    dec_cmd->add_option("-f,--file", filename, "Шлях до зашифрованого файлу")->required();
    dec_cmd->add_option("-p,--password", password, "Пароль для дешифрування")->required();

    // Парсинг аргументів командного рядка
    CLI11_PARSE(app, argc, argv);

    // Тут буде логіка шифрування/дешифрування
}