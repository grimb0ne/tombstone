#include <iostream>
#include <fstream>
#include <cstdint>
#include <climits>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <Windows.h>

#ifdef max
#undef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifdef min
#undef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void*)0)
#endif
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef CONST
#define CONST const
#endif
#ifndef IN
#define IN 0
#endif
#ifndef OUT
#define OUT 1
#endif

#define LOG(x) std::cout << x

typedef unsigned char BYTE;
typedef BYTE *PBYTE, *LPBYTE;
typedef unsigned long DWORD;
typedef DWORD *PDWORD, *LPDWORD;
typedef unsigned short WORD;
typedef WORD *PWORD, *LPWORD;
typedef CONST void *PCVOID, *LPCVOID;

auto flipSign = [](signed &value) decltype(auto) -> {
    if (value < 0) {
        value = value * (-1);    
    } else if (value > 0) {
        value = value * (-1);    
    } else {
        value = value;
    }
    return value;
};

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

    /* ======================================== [ Begin Vector Struct ] ======================================== */
    struct Vector {
        template<typename T>
        static void cycleVector(const std::vector<T>& vect);   
        template<typename T>
        static void fillVector(const std::vector<T>& vect, T content);
    };
    template<typename t>
    void Vector::cycleVector(const std::vector<T>& vect) {
        for (WORD i = 0; i < vect.size(); i++) {
            std::cout << vect.at(i) << ", ";
        }
    }
    template<typename T>
    void Vector::fillVector(const std::vector<T>& vect, T content) {
        for (WORD i = 0; i < vect.size(); i++) {
            vect.at(i) = content;    
        }
    }
    /* ======================================== [ End Vector Struct ] ======================================== */
    
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
    int File::clearFile(const std::string filePath) {
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
