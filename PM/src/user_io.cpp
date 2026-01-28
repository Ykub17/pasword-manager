#include "user_io.h"
std::vector<unsigned char> read_file(const std::string& path) 
{ std::ifstream file(path, std::ios::binary); 
    if (!file) throw std::runtime_error("Cannot open input file"); 
    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

void write_file(const std::string& path, const std::vector<unsigned char>& data) 
{
    std::ofstream file(path, std::ios::binary);
    if (!file)
        throw std::runtime_error("Cannot open output file");

    file.write(reinterpret_cast<const char*>(data.data()), data.size());

    if (!file)
        throw std::runtime_error("Error while writing file");
}
