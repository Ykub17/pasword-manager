#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP
#include <iostream>    
#include <fstream>     
#include <string>      
#include <functional>  

using namespace std;

void encryptFile(const std::string& filename) 
{
    std::ifstream inputFile(filename);
    std::ofstream outputFile(filename + ".hash");

    if (!inputFile.is_open()) 
    {
        std::cerr << "Помилка: не вдалося відкрити файл " << filename << std::endl;
        return;
    }

    std::string line;
    std::hash<std::string> hasher;

    while (std::getline(inputFile, line)) 
    {
        size_t hashValue = hasher(line);// size_t використовуєм для збереження хеш-значення тому що інт буде занадто малий
        outputFile << hashValue << std::endl;
    }

    std::cout << "Файл успішно захешовано у " << filename << ".hash" << std::endl;
    inputFile.close();
    outputFile.close();
}
#endif // ENCRYPTION_HPP