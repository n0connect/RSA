#include <iostream>
#include <gmpxx.h>
#include <random>
#include <chrono>
#include <fstream>
#include <string>
#include <ownerr.h>

// ** Istenilen bit uzunluğunda yüksek olasılıkla asal sayı üretir
// ** Kullanılan algoritma "BPSW" (Bailey–Pomerance–Selfridge–Wagstaff)
mpz_class GenerateRandomPrime(short int _bit_, short int _validator_)
{
    mpz_class prime;
    gmp_randstate_t state;

    gmp_randinit_default(state);
    gmp_randseed_ui(state, std::chrono::high_resolution_clock::now().time_since_epoch().count());

    while (true)
    {
        mpz_urandomb(prime.get_mpz_t(), state, _bit_);
        if (mpz_probab_prime_p(prime.get_mpz_t(), _validator_) != 0)
            break;
    }

    gmp_randclear(state);

    return prime;
}

// ** Hesaplanan Asalları kaydet
void WritePrimesToFile(const std::string &fileName, const mpz_class &prime, short int _bit_, short int _validator_)
{
    std::ofstream outputFile(fileName, std::ios_base::app); // Dosyanın sonuna ekleme modunda aç
    if (!outputFile.is_open())
    {
        std::cerr << "Unable to open output file!" << std::endl;
        return;
    }

    outputFile << _bit_ << "BIT"
               << " " << _validator_ << " "
               << "Validator"
               << " ";                // Bit uzunluğu ve validator değerini dosyaya yaz
    outputFile << prime << std::endl; // Üretilen asal sayıyı dosyaya ekle
    outputFile.close();
}

int main()
{
    short int _bit_ = 64;
    short int _count_ = 10;
    short int primeCount{0};
    short int _validator_ = 2000;

    try
    {
        // ** Bilgilendirici mesajları ekrana yazdır
        std::cout << "Bit size determines the length of the prime number in bits." << std::endl;
        std::cout << "Validator size affects the certainty level of the primality test." << std::endl;
        std::cout << "A higher validator size results in a more rigorous primality check." << std::endl;

        // ** Kullanıcıdan bit ve validator boyutunu girmesini isteyen mesajları ekrana yazdır
        std::cout << "Enter the bit size (recommended: 256): ";
        std::cin >> _bit_;

        std::cout << "Enter the validator size (recommended: 25): ";
        std::cin >> _validator_;

        // ** Kaç adet asal sayı isteniyor
        std::cout << "Enter the prime count (recommended: 10): ";
        std::cin >> _count_;
    }
    catch (std::exception &ex)
    {
        OwnErr();
    }

    std::cout << std::endl;

    std::ofstream outputFile("probPrime.txt", std::ios_base::app); // Dosyanın sonuna ekleme modunda aç
    if (!outputFile.is_open())
    {
        std::cerr << "Unable to open output file!" << std::endl;
        return 1;
    }

    outputFile.close(); // Dosyayı kapat, yalnızca kontrol için açıldı

    mpz_class prime{};

    while (primeCount < _count_)
    {
        prime = GenerateRandomPrime(_bit_, _validator_);
        WritePrimesToFile("probPrime.txt", prime, _bit_, _validator_);
        ++primeCount;
    }

    // Üretilen asal sayıları ekrana yazdır
    std::ifstream inputFile("probPrime.txt");
    if (inputFile.is_open())
    {
        std::string line;
        while (std::getline(inputFile, line))
        {
            std::cout << line << std::endl;
        }
        inputFile.close();
    }
    else
    {
        std::cerr << "Unable to open input file!" << std::endl;
        return 1;
    }

    return 0;
}
