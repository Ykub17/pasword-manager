#pragma once

#include <string>
void encrypt_file(const std::string& input, const std::string& output, const char* password);
void decrypt_file(const std::string& input, const std::string& output, const char* password);

