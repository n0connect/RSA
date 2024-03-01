# RSA Projesi

Bu proje, RSA şifreleme algoritmasını uygulamak için C++ dilinde yazılmıştır. RSA algoritmasının anahtar üretimi, metin şifreleme ve şifreli metni çözme işlemleri burada gerçekleştirilir.

# Program Görselleri

![terminalOutput](https://github.com/n0connect/RSA/assets/126422643/0cea7c65-6027-4f42-8310-f8207f9dcb3e)
![terminalOutput2](https://github.com/n0connect/RSA/assets/126422643/118cea5b-de4c-42c2-8c8d-c50ac8871ab1)
** Programın çalışma anından görseller.

## Dosyalar

- **Config.ini**: Proje yapılandırma dosyası.
- **PrimeCalculator.cpp**: 256 bitlik asal sayıları bulmak için kullanılan C++ kodu.
- **PrimeCalculator.exe**: PrimeCalculator.cpp kodunun derlenmiş uygulaması.
- **probPrime.txt**: PrimeCalculator ile bulunan 256 bitlik asal sayıların listesi.
- **RSA.cpp**: RSA şifreleme algoritması uygulamasının C++ kodu.
- **RSA.exe**: RSA şifreleme algoritması uygulamasının derlenmiş uygulaması.

## Kullanım

PrimeCalculator.cpp dosyası, 256 bitlik asal sayıları bulmak için kullanılır. Çalıştırıldığında, probPrime.txt dosyasına asal sayılar listelenir.

RSA.cpp dosyası, RSA şifreleme algoritmasını uygular. Config.ini dosyasında yapılandırılan anahtarlar ve metinler üzerinde işlem yapar.

### Config.ini Ayarları

- **[DecryptedText]**: Şifrelenmiş metni çözülmüş metinle eşleştirmek için kullanılır. Örnek: `Decrypted=https://github.com/n0connect/RSA`
- **[EncryptedHex]**: Metnin onaltılık (hex) şifrelenmiş sürümünü belirtir. Örnek: `Hex=e2de3f24258d3014 136319082ad93d67 ...`
- **[EncryptedText]**: Metnin şifrelenmiş sürümünü belirtir. Örnek: `Encrypted=16347573121882861588 1396987832284298599 ...`
- **[Private]**: Özel anahtar değerlerini belirtir. `PrimeOne` ve `PrimeTwo` değerleri kullanılır. Örnek: `PrimeOne=5000999921`
- **[Public]**: Genel anahtar değerlerini belirtir. `Generator` ve `PublicKey` değerleri kullanılır. Örnek: `Generator=65537`
- **[SecretText]**: Şifrelenmiş metin ve çözülmüş metinle ilgili gizli bilgileri belirtir. `Seed` ve `Text` değerleri kullanılır. Örnek: `Seed=/RSA`

## Lisans

Bu proje MIT Lisansı altında lisanslanmıştır. Detaylar için [LICENSE](LICENSE) dosyasına bakın.

## İletişim

Projeyi geliştirirken herhangi bir sorunla karşılaşırsanız veya herhangi bir geri bildirimde bulunmak isterseniz, lütfen bir GitHub Issue açın veya [email protected] adresine e-posta gönderin.

