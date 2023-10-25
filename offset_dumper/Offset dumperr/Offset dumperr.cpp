#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <fstream>
#include <string>

void DumpProcessMemory(DWORD processId, const std::wstring& outputFileName) {
    HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, processId);

    if (processHandle == nullptr) {
        std::wcerr << L"Failed to open process. Error code: " << GetLastError() << std::endl;
        return;
    }

    MODULEENTRY32 moduleEntry;
    moduleEntry.dwSize = sizeof(MODULEENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
    if (snapshot == INVALID_HANDLE_VALUE) {
        std::wcerr << L"Failed to create snapshot. Error code: " << GetLastError() << std::endl;
        CloseHandle(processHandle);
        return;
    }

    if (Module32First(snapshot, &moduleEntry)) {
        do {
            std::wcout << L"Module Name: " << moduleEntry.szModule << std::endl;

            std::ofstream outputFile(outputFileName.c_str(), std::ios::out | std::ios::binary);
            if (outputFile.is_open()) {
                char buffer[4096];
                SIZE_T bytesRead;

                if (ReadProcessMemory(processHandle, moduleEntry.modBaseAddr, buffer, sizeof(buffer), &bytesRead)) {
                    outputFile.write(buffer, bytesRead);
                }
                else {
                    std::wcerr << L"Failed to read process memory. Error code: " << GetLastError() << std::endl;
                }

                outputFile.close();
            }
            else {
                std::wcerr << L"Failed to create output file." << std::endl;
            }

        } while (Module32Next(snapshot, &moduleEntry));
    }
    else {
        std::wcerr << L"Failed to enumerate modules. Error code: " << GetLastError() << std::endl;
    }

    CloseHandle(snapshot);
    CloseHandle(processHandle);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::wcerr << L"Usage: OffsetDumper.exe <ProcessID> <OutputFileName>" << std::endl;
        return 1;
    }

    DWORD processId = std::stoi(argv[1]);
    std::wstring outputFileName;
    outputFileName.assign(argv[2], argv[2] + strlen(argv[2]));

    DumpProcessMemory(processId, outputFileName);
    return 0;
}
