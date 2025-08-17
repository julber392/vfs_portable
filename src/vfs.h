
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

struct DirEntry {
    std::string name;
    bool isDir;
    size_t startBlock;
    size_t size;
};

class VirtualFileSystem {
public:
    VirtualFileSystem(const std::string &path, size_t blocks, size_t blockSize = 512);
    bool mkfs();
    bool mkdir(const std::string &dirPath);
    bool rmdir(const std::string &dirPath);
    bool put(const std::string &hostFile, const std::string &vfsPath);
    bool get(const std::string &vfsPath, const std::string &hostFile);
    bool rm(const std::string &vfsPath);
    bool cat(const std::string &vfsPath);
    bool ls(const std::string &dirPath);
private:
    std::string diskPath;
    size_t totalBlocks;
    size_t blockSize;
    bool readAll(std::map<std::string, DirEntry> &entries);
    bool writeAll(const std::map<std::string, DirEntry> &entries);
};
