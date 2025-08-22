
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

bool VirtualFileSystem::mkdir(const string &dirPath) {
    return false;
}

bool VirtualFileSystem::rmdir(const std::string &dirPath) {}(const string &hostFile, const string &vfsPath) {
    return false;
}

bool VirtualFileSystem::put(const string &hostFile, const string &vfsPath) {
    return false;
}

bool VirtualFileSystem::get(const string &vfsPath, const string &hostFile) {
    return false;
}

bool VirtualFileSystem::rm(const std::string &vfsPath) {
    return false;
}

bool VirtualFileSystem::cat(const std::string &vfsPath) {
    return false;
}

bool VirtualFileSystem::ls(const std::string &dirPath) {
    return false;
}

bool VirtualFileSystem::readAll(std::map<std::string, DirEntry> &entries) {
    return false;
}

bool VirtualFileSystem::writeAll(const std::map<std::string, DirEntry> &entries) {
    return false;
}
