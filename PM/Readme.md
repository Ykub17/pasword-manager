# C++ File Encryptor (libsodium)

Шифратор та дешифратор паролей за домогою библиотеки  **libsodium**.

## Технології
* **Мова:** C++
* **Криптографія:** [libsodium](https://doc.libsodium.org/doc/installation)

##  Збірка проекту

1. Для збірки проекту по-перше треба встановити бібліотеку [libsodium](https://doc.libsodium.org/doc/installation) (подробна інструкція для її встановлення)

2. Скомпілюйте проект:
  g++ \
-I./include \
./src/main.cpp ./src/encrypt.cpp ./src/decrypt.cpp ./src/user_io.cpp \
-L./libs \
-lsodium \
-o password_encryptor

##  Користування проектом
1. Для того щоб шифрувати треба вести таку команду *./password_encryptor encrypt --input pasw.txt --output pasw.enc --password MyStrongPassword123*, і також треба заздалегіть створити файл **pasw.txt** , де будуть міститься паролі 

2. Для дешифрування треба вести команду *./password_encryptor decrypt --input pasw.enc --output decrypted.txt --password MyStrongPassword123*      

