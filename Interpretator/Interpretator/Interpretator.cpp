#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: BinaryInterpreter.exe <InputFileName> <OutputFileName>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1], std::ios::in | std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return 1;
    }

    std::vector<unsigned char> binaryData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    std::ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to create output file." << std::endl;
        return 1;
    }

    // Выводим интерпретацию бинарных данных в шестнадцатеричном формате и символьном виде
    for (unsigned char byte : binaryData) {
        outputFile << std::hex << static_cast<int>(byte) << " ";

        // Печатаем символы, если они в диапазоне от 32 до 126 (включительно), иначе печатаем точку
        if (byte >= 32 && byte <= 126) {
            outputFile << byte;
        }
        else {
            outputFile << ".";
        }

        outputFile << std::endl;
    }

    std::cout << "Interpreted data has been saved to " << argv[2] << std::endl;

    return 0;
}
