#include <iostream>
#include "CLI11.HPP"
#include "sodium.h"
void encrypt_file(const std::string& input, const std::string& output, const char* password);
void decrypt_file(const std::string& input, const std::string& output, const char* password);

int main(int argc, char** argv) 
{
    if (sodium_init() < 0) 
    {
        std::cerr << "libsodium init failed\n";
        return 1;
    }

    CLI::App app("File encryption / decryption tool");

    std::string input, output, password;

    auto enc = app.add_subcommand("encrypt", "Encrypt file");
    enc->add_option("-i,--input", input)->required();
    enc->add_option("-o,--output", output)->required();
    enc->add_option("-p,--password", password)->required();

    auto dec = app.add_subcommand("decrypt", "Decrypt file");
    dec->add_option("-i,--input", input)->required();
    dec->add_option("-o,--output", output)->required();
    dec->add_option("-p,--password", password)->required();

    CLI11_PARSE(app, argc, argv);

    try {
        if (app.got_subcommand(enc)) 
        {
            encrypt_file(input, output, password.c_str());
            std::cout << "Encrypted successfully\n";
        } else if (app.got_subcommand(dec)) 
        {
            decrypt_file(input, output, password.c_str());
            std::cout << "Decrypted successfully\n";
        } else 
        {
            std::cout << app.help() << std::endl;
        }
    } catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
