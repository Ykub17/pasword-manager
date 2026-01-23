#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

std::vector<unsigned char> read_file(const std::string& path);
void write_file(const std::string& path, const std::vector<unsigned char>& data) ;

