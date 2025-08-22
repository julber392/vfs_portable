
#include "vfs.h"
#include <sstream>
#include <cstring>
#include <filesystem>

using namespace std;

VirtualFileSystem::VirtualFileSystem(const std::string &path, size_t blocks, size_t blockSize) :
        diskPath(path), totalBlocks(blocks), blockSize(blockSize) {};

bool VirtualFileSystem::mkfs() {
    fstream file(diskPath, ios::binary | ios::out | ios::trunc);
    if (!file) return false;

    vector<char> zero(blockSize, 0);
    for (size_t i = 0; i < totalBlocks; i++) {
        file.write(zero.data(), blockSize);
    }
    return true;
}
