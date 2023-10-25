#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

int main() {
    std::ifstream inputFile("hex.txt", std::ios::binary); // Открываем файл в бинарном режиме
    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл." << std::endl;
        return 1;
    }

    // Читаем данные из файла в вектор байт
    std::vector<unsigned char> binaryData(std::istreambuf_iterator<char>(inputFile), {});

    // Печатаем расшифрованные данные
    std::cout << "Расшифрованные данные: ";
    for (unsigned char byte : binaryData) {
        std::cout << byte;
    }
    std::cout << std::endl;

    // Сохраняем расшифрованные данные в файл decrypted_hex.txt
    std::ofstream outputFile("decrypted_hex.txt");
    if (outputFile.is_open()) {
        for (unsigned char byte : binaryData) {
            outputFile << byte;
        }
        std::cout << "Расшифрованные данные сохранены в decrypted_hex.txt." << std::endl;
    }
    else {
        std::cerr << "Не удалось создать файл для записи." << std::endl;
    }

    return 0;
}
