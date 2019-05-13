#include <iostream>
#include <fstream>
#include <cstdint>
#include <climits>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <Windows.h>

namespace Tombstone {
    /* ======================================== [ Begin "Unique" Functions ] ======================================== */
    decltype(auto) getCurrentTime() {
        auto time = std::chrono::system_clock::now();
        if (time != NULL) {
            return time;
        } else {
            return NULL;
        }
    }
    /* ======================================== [ End "Unique" Functions ] ======================================== */

    /* ======================================== [ Begin File Class ] ======================================== */
    class File {
    private:
        std::vector<File> parsedFiles;
    public:
        bool isOnDisk(const std::string filePath);
        int clearFile(const std::string filePath);
        void editFile(const std::string filePath, const char *mode, std::string content);
        int deleteFile(const std::string filePath);
        void getParsedFiles();
        File();
        ~File();
    };
    bool File::isOnDisk(const std::string filePath) {
        if (FILE *file = fopen(filePath.c_str(), "r")) {
            parsedFiles.push_back(this);
            return true;
        } else {
            return false;
        }
    }
    void File::clearFile(const std::string filePath) {
        std::ofstream targetFile;
        if (isOnDisk(filePath)) {
            targetFile.open(filePath.c_str(), std::ios::write);
            targetFile.close();
            parsedFiles.push_back(this);
            return 0;
        } else {
            return 1;
        }
    }
    void File::editFile(const std::string filePath, const char *mode, std::string content) {
        std::ofstream targetFile;
        if (isOnDisk(filePath)) {
            if (mode == "a") {
                targetFile.open(filePath.c_str(), std::ios:app);
                targetFile.write(content.c_str(), sizeof(content + 1));
            } else if (mode == "w") {
                targetFile.open(filePath.c_str(), std::ios::write);
                targetFile.write(content.c_str(), sizeof(content + 1));
            }
            targetFile.close();
            parsedFiles.push_back(this);
            return;
        } else {
            return;
        }
    }
    int File::deleteFile(const std::string filePath) {
        if (isOnDisk(filePath)) {
            system(("del " + filePath).c_str());
            if (isOnDisk(filePath)) {
                parsedFiles.push_back(this);
                return 0;
            } else {
                return 1;
            }
        } else {
            return 1;
        }
    }
    void File::getParsedFiles() {
        for (File file : parsedFiles) {
            std::cout << file << " ";
        }
    }
    /* ======================================== [ End File Class ] ======================================== */
    
    /* ======================================== [ Begin Memory Struct ] ======================================== */
    struct Memory {
        static volatile uintptr_t allocate(unsigned bytes);
        static volatile uintptr_t deallocate(void &pointer);
    };
    volatile uintptr_t Memory::allocate(unsigned bytes) {
        int *ptr = nullptr;
        ptr = static_cast<int*>(malloc(bytes));
        if (ptr != NULL) {
            return ptr;
        } else if (ptr == NULL) {
            free(ptr);
            return 1;
        }
    }
    volatile uintptr_t Memory::deallocate(int &pointer) {
        if (pointer != NULL) {
            free(pointer);
            return 0;
        } else if (pointer == NULL) {
            return 1;
        }
    }
    /* ======================================== [ End Memory Struct ] ======================================== */
    
    /* ======================================== [ Begin Window Struct ] ======================================== */
    struct Window {
        static HANDLE windowExists(const std::string window);
        template <typename T>
        static volatile T modifyProcessMemory(DWORD &address, T newValue);
    };
    HANDLE Window::windowExists(const std::string window) {
        HWND hWnd = FindWindowA(NULL, window.c_str());
        if (hWnd) {
            DWORD procID;
            GetWindowThreadProcessId(hWnd, &procID);
            HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
            if (handle) {
                return handle;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }
    template<typename T>
    volatile T Window::modifyProcessMemory(const std::string window, DWORD &address, T newValue) {
        if (windowExists(window) != nullptr) {
            if (WriteProcessMemory(windowExists(window), &address, newValue, sizeof(newValue), 0)) {
                return newValue;
            } else {
                return NULL;
            }
        } else {
            return NULL;
        }
    }
    /* ======================================== [ End Window Struct ] ======================================== */
} // namespace Tombstone
