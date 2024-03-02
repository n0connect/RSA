#ifndef OWNERR_H
#define OWNERR_H

#include <iostream>
#include <string>

// Err: Hata mesajı gönderen işlev
// Parametreler:
//   - callingFunctionName: Hatanın meydana geldiği işlevin adı
//   - line: Hatanın meydana geldiği satır numarası
//   - file: Hatanın meydana geldiği dosyanın adı
//   - errorMessage: Hata mesajı
void Err(const std::string &callingFunctionName, int line, const std::string &file, const std::string &errorMessage)
{
    std::cerr << "Error in function: " << callingFunctionName << " at line " << line << " in file " << file << std::endl;
    std::cerr << "Error message: " << errorMessage << std::endl;
    exit(EXIT_FAILURE);
}

#define OwnErr()                                               \
    do                                                         \
    {                                                          \
        std::string errorMsg = ex.what();                      \
        if (errorMsg.empty())                                  \
            errorMsg = "No detailed error message available."; \
        Err(__func__, __LINE__, __FILE__, errorMsg);           \
    } while (0)

#endif // OWNERR_H
