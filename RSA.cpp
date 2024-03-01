#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <gmp.h>
#include <gmpxx.h>
#include <algebra.h>    // ? GMP işlemlerini kısaltmak için.
#include <configfile.h> // ? Config.INI

/*
    Euler Phi fonksiyonu (φ(n)), bir tam sayı n'nin Euler'in totient fonksiyonunu hesaplamak için kullanılır.
    Bu fonksiyon, n ile aralarında asal olan 1'den küçük pozitif tam sayıların sayısını verir.

    Parametreler:
        primeOne: Birinci asal sayının bellek adresi.
        primeTwo: İkinci asal sayının bellek adresi.

    Return Değeri:
        mpz_class: Hesaplanan φ(n) değeri, bir GMP büyük tam sayı nesnesi olarak döndürülür.
*/
mpz_class EulerPhi(mpz_class &primeOne, mpz_class &primeTwo)
{
    mpz_class result;

    // ** Asal sayıları birer eksiğine eşitle
    primeOne = primeOne - 1;
    primeTwo = primeTwo - 1;

    try
    {
        // ** İki asal sayıdan φ(n) değerini hesapla
        mpz_mul(result.get_mpz_t(), primeOne.get_mpz_t(), primeTwo.get_mpz_t());
        return result;
    }
    catch (std::exception &ex)
    { // ** Phi değeri hesaplanırken bir hata oluştu
        OwnErr();
        return mpz_class();
    }
}

/*
    Private Key fonksiyonu hesaplanmış Phi sonucu ve Üreteç ile özel anahtarı bulur.

    Parametreler:
        phi      : Hesaplanmış Euler Phi sonucunun bellek adresi.
        generator: [2, phi-1] aralığında (generator, phi) = 1 olan değerin bellek adresi.

    Return Değeri:
        mpz_class: Private Key değerini tutan GMP büyük tam sayı nesnesi olarak döndürür.
*/
mpz_class PrivateKey(mpz_class &phi, mpz_class &generator)
{
    mpz_class coefficientNumber = 1;
    mpz_class privateKeyModResult{};
    mpz_class privateKeyResult{};
    bool condition = true;

    try
    {
        do
        { // ** [ k*φ(n) + 1 ] Generator'a tam bölünmesi için gereken k'yı bulur.
            privateKeyResult = (multiply(coefficientNumber, phi) + 1);
            privateKeyModResult = modulus(privateKeyResult, generator);

            if (privateKeyModResult == 0)
            {
                condition = false;
                privateKeyResult = dvide(privateKeyResult, generator);
            }
            else
            {
                coefficientNumber = coefficientNumber + 1;
            }

        } while (condition);

        // ** Özel anahtarı döndürür.
        return privateKeyResult;
    }
    catch (std::exception &ex)
    { // ** Private Key değeri hesaplanırken bir hata oluştu
        OwnErr();
        return mpz_class();
    }
}

/*
    Convert Text To Numbers fonksiyonu şifrelenecek Stringi'i alır ve ASCII dizisine çevirir.

    Parametreler:
        text: ASCII dizisine dönüştürülecek string metinin bellek adresi.

    Return Değeri:
        mpz_class: ASCII karşılıklarını GMP büyük tamsayı bir vektör olarak döndürür.
*/
std::vector<mpz_class> ConvertTextToNumbers(std::string &text)
{
    std::vector<mpz_class> numbers;

    try
    {
        // ** Text içinde ki her bir Karakteri ASCII dönüştür
        for (char ch : text)
        {
            numbers.push_back(static_cast<int>(ch));
        }

        return numbers;
    }
    catch (std::exception &ex)
    { // ** ConvertTextToNumbers değeri hesaplanırken bir hata oluştu
        OwnErr();
        return numbers;
    }
}

/*
    Convert Nubmers To Text fonksiyonu ASCII çevrilmiş vektör dizesini alır Okunabilir hale getirir.

    Parametreler:
        numbers: ASCII dizisine dönüştürülmüş elemanları mpz_class türünde bir vektörün bellek adresi.

    Return Değeri:
        string: ASCII olarak dönüştürülmüş bir vektörü okunabilir hale çevirir.
*/
std::string ConvertNumbersToText(const std::vector<mpz_class> &numbers)
{
    std::string text;
    try
    {
        // ** Vektör içinde ki ASCII karşılıklarını Karaktere çevir
        for (const auto &num : numbers)
        {
            text += static_cast<char>(mpz_get_ui(num.get_mpz_t()));
        }

        return text;
    }
    catch (std::exception &ex)
    { // ** ConvertNumbersToText değeri hesaplanırken bir hata oluştu
        OwnErr();
        return text;
    }
}

/*
    Encrypt fonksiyonu RSA Her bir ASCII karakterini şifreler.

    Parametreler:
        message  : ASCII çevrilmiş vektörün bellek adresi.
        generator: Önceden belirlenmiş üreteç değerinin bellek adresi.
        PublicKey: Özel asal sayıların çarpım değerinin bellek adresi.

    Return Değeri:
        string: ASCII olarak dönüştürülmüş bir vektörü okunabilir hale çevirir.
*/
std::vector<mpz_class> Encrypt(const std::vector<mpz_class> &message, const mpz_class &generator, const mpz_class &publicKey)
{
    std::vector<mpz_class> encryptedMessage;
    mpz_class encrypted;

    try
    {
        for (const auto &num : message)
        {

            mpz_powm(encrypted.get_mpz_t(), num.get_mpz_t(), generator.get_mpz_t(), publicKey.get_mpz_t());
            encryptedMessage.push_back(encrypted); // Her sayıyı şifreliyoruz
        }
        return encryptedMessage;
    }
    catch (std::exception &ex)
    { // ** Encrypt değeri hesaplanırken bir hata oluştu
        OwnErr();
        return encryptedMessage;
    }
}

/*
    Decrypt fonksiyonu RSA ile şifrelenen veriyi özel anahtar ile çözer.

    Parametreler:
        encryptedMessage: RSA ile şifrelenmiş vektörün bellek adresi.
        generator       : Önceden belirlenmiş üreteç değerinin bellek adresi.
        publicKey       : Özel asal sayıların çarpım değerinin bellek adresi.
        privateKey      : Özel asal sayılar ile @PrivateKey fonksiyonunda hesaplanan değerin bellek adresi.

    Return Değeri:
        string: ASCII olarak dönüştürülmüş bir vektörü okunabilir hale çevirir.
*/
std::vector<mpz_class> Decrypt(const std::vector<mpz_class> &encryptedMessage, const mpz_class &privateKey, const mpz_class &publicKey)
{
    std::vector<mpz_class> decryptedMessage;
    try
    {
        // ** Her sayıyı özel anahtar ile çöz.
        for (const auto &num : encryptedMessage)
        {
            mpz_class decrypted;
            mpz_powm(decrypted.get_mpz_t(), num.get_mpz_t(), privateKey.get_mpz_t(), publicKey.get_mpz_t());
            decryptedMessage.push_back(decrypted);
        }
        return decryptedMessage;
    }
    catch (std::exception &ex)
    { // ** Decrypt değeri hesaplanırken bir hata oluştu
        OwnErr();
        return decryptedMessage;
    }
}

/*
    Fonksiyonlar:
        WriteTerminal      : Terminale Yazdırmak için kullandığım fonksiyon.
        _add_              : EncryptedText ve DecryptedText Config.ini dosyasına ekler.
        _main_             : RSA için gerekli işlemlerin başlatıldığı fonksiyon.
        _match_ini_items_  : Config.ini içerisinde ki Text, Generator, PrimeOne, PrimeTwo degerlerini alır.

    Parametreler:
        encryptedMessage: RSA ile şifrelenmiş vektörün bellek adresi.
        decryptedMessage: RSA ile şifresi çözülmüş text'in bellek adresi.
        publicKey       : Özel asal sayıların çarpım değerinin bellek adresi.
        privateKey      : Özel asal sayılar ile @PrivateKey fonksiyonunda hesaplanan değerin bellek adresi.
        filename        : .INI dosyasının ismi Default: Config.INI
        convertedDecryptedMessage: ASCII'den Okunabilir hale çevrilmiş şifresi çözülmüş metinin bellek adresi.

*/
void WriteTerminal(std::vector<mpz_class> &encryptedMsg, const std::string &decryptedMessage)
{
    // ** Şifreli metini Hex tabanında terminale yazdırma
    try
    {
        std::cout << "\n\n";
        std::cout << "Encrypted Message (Hex): ";

        for (const auto &num : encryptedMsg)
        {
            char *hexStr = mpz_get_str(NULL, 16, num.get_mpz_t());
            // ** Hex türünde yazdır.
            std::cout << hexStr << " ";
            free(hexStr); // Bellek sızıntısını önlemek için belleği serbest bırakın
        }
        std::cout << std::endl;

        // ** Şifresi çözülmüş  metini terminale yazdırma
        std::cout << "Decrypted Text: ";
        for (const auto &num : decryptedMessage)
        {
            std::cout << num;
        }
        std::cout << std::endl;
    }
    catch (std::exception &ex)
    {
        OwnErr();
    }
}

void _add_(const std::vector<mpz_class> &encryptedMsg, const std::string &convertedDecryptedMessage)
{

    // ** .INI dosyasını oku
    try
    {
        std::map<std::string, std::map<std::string, std::string>> iniData = ReadINI("Config.ini");

        std::string encryptedText;
        std::string encryptedTextHex;

        for (const auto &num : encryptedMsg)
        {
        }
        std::cout << std::endl;

        for (const auto &num : encryptedMsg)
        { // ** Her bir sayıyı bir boşlukla ayırarak .ini dosyasına ekle & Hex türünde bellekte tut.
            encryptedText += num.get_str() + " ";

            char *hexStr = mpz_get_str(NULL, 16, num.get_mpz_t());
            // ** Hex türünde kaydet.
            encryptedTextHex.append(hexStr);
            encryptedTextHex.append(" ");
            free(hexStr); // Bellek sızıntısını önlemek için belleği serbest bırakın
        }

        // ** Okunan .INI dosyasında ki gerekli yerlere yerleştir.
        iniData["EncryptedText"]["Encrypted"] = encryptedText;
        iniData["EncryptedHex"]["Hex"] = encryptedTextHex;
        iniData["DecryptedText"]["Decrypted"] = convertedDecryptedMessage;

        // ** .INI dosyasını güncelle
        WriteINI("Config.ini", iniData);
    }
    catch (std::exception &ex)
    {
        OwnErr();
    }
}

void _main_(std::string &text, const mpz_class &publicGenerator, const mpz_class &publicKey, const mpz_class &privateKey)
{

    try
    {
        // ** Metni ASCII dizesine çevir
        std::vector<mpz_class> numbers = ConvertTextToNumbers(text);

        // ** ASCII dizesinde ki metni şifrele
        std::vector<mpz_class> encryptedMsg = Encrypt(numbers, publicGenerator, publicKey);

        // ** Şifrelenmiş metni çöz
        std::vector<mpz_class> decryptedMessage = Decrypt(encryptedMsg, privateKey, publicKey);

        // ** Çözülmüş metni ASCII -> Char çevir.
        std::string convertedDecryptedMessage = ConvertNumbersToText(decryptedMessage);

        // ** .INI dosyasını güncelle.
        _add_(encryptedMsg, convertedDecryptedMessage);

        // ** Hesaplanan değerleri terminale bastır.
        WriteTerminal(encryptedMsg, convertedDecryptedMessage);
    }
    catch (std::exception &ex)
    {
        OwnErr();
    }
}

void _match_ini_items_(std::string &filename)
{
    try
    {
        // ** .INI dosyasını oku.
        std::map<std::string, std::map<std::string, std::string>> iniData = ReturnINI(filename);

        // ** Kullanıcı tanımlı değerler ile eşleştir.
        mpz_class secretPrimeOne(iniData["Private"]["PrimeOne"]);
        mpz_class secretPrimeTwo(iniData["Private"]["PrimeTwo"]);
        mpz_class publicGenerator(iniData["Public"]["Generator"]);
        std::string seed = iniData["SecretText"]["Seed"];
        std::string text = iniData["SecretText"]["Text"];

        // ** SEED verisini text'e ekle
        text.append(seed);

        // ** RSA islemlerini yap.
        mpz_class publicKey = multiply(secretPrimeOne, secretPrimeTwo);
        mpz_class phiResult = EulerPhi(secretPrimeOne, secretPrimeTwo);
        mpz_class privateKey = PrivateKey(phiResult, publicGenerator);

        { // ** .INI okunan degerleri terminale yazdır.

            std::cout << "Loaded values from Config.INI file:" << std::endl;
            std::cout << "Private Prime One: " << secretPrimeOne << std::endl;
            std::cout << "Private Prime Two: " << secretPrimeTwo << std::endl;
            std::cout << "Public Generator: " << publicGenerator << std::endl;
            std::cout << "Public Key: " << publicKey << std::endl;
            std::cout << "Private Key: " << privateKey << std::endl;
            std::cout << "Text: " << text << std::endl;
        }

        // ** Islemleri Baslat !
        _main_(text, publicGenerator, publicKey, privateKey);
    }
    catch (std::exception &ex)
    {
        OwnErr();
    }
}

int main()
{
    std::string iniFilename = "Config.ini";
    _match_ini_items_(iniFilename);
}