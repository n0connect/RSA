// ? Bu dosya, INI dosyalarını okuyan, yazan ve işleyen işlevleri içerir.

#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

std::map<std::string, std::map<std::string, std::string>> ReadINI(const std::string &filename)
{
    std::map<std::string, std::map<std::string, std::string>> iniData;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return iniData;
    }

    std::string currentSection;
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == ';') // Boş satırları veya yorum satırlarını atla
            continue;
        else if (line[0] == '[')
        { // Bölüm başlıklarını tanımla
            currentSection = line.substr(1, line.find(']') - 1);
        }
        else
        {
            size_t pos = line.find('=');
            if (pos != std::string::npos)
            {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                iniData[currentSection][key] = value;
            }
        }
    }
    file.close();
    return iniData;
}

void WriteINI(const std::string &filename, const std::map<std::string, std::map<std::string, std::string>> &iniData)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    for (const auto &section : iniData)
    {
        file << "[" << section.first << "]\n";
        for (const auto &pair : section.second)
        {
            file << pair.first << "=" << pair.second << "\n";
        }
        file << "\n";
    }
    file.close();
}

void CreateDefaultINI(const std::string &filename)
{
    std::map<std::string, std::map<std::string, std::string>> iniData = {
        {"Private", {{"PrimeOne", "5000999921"}, {"PrimeTwo", "4999999937"}}},
        {"Public", {{"Generator", "65537"}, {"PublicKey", "25004999289937004977"}}},
        {"SecretText", {{"Text", "RSA-algoritmasinin-frekans-degeri-risklidir!"}, {"Seed", "NULL"}}},
        {"EncryptedText", {{"Encrypted", ""}}},
        {"EncryptedHex", {{"Hex", ""}}},
        {"DecryptedText", {{"Decrypted", ""}}}};

    WriteINI(filename, iniData);
}

void CheckFileExists(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Config.ini file does not exist. Creating default Config.ini file..." << std::endl;
        CreateDefaultINI(filename);
    }
}

std::map<std::string, std::map<std::string, std::string>> ReturnINI(const std::string &filename)
{
    CheckFileExists(filename);

    std::map<std::string, std::map<std::string, std::string>> readData = ReadINI(filename);

    /*
    std::clog << "Config.ini file is reading..." << std::endl;
    for (const auto &section : readData)
    {
        std::cout << "[" << section.first << "]\n";
        for (const auto &pair : section.second)
        {
            std::cout << pair.first << "=" << pair.second << "\n";
        }
        std::cout << "\n";
    }
    */

    return readData;
}

#endif // CONFIGFILE_H
