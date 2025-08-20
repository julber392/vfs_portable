
#include "vfs.h"
#include <sstream>
#include <cstring>
#include <filesystem>

using namespace std;

VirtualFileSystem::VirtualFileSystem(const std::string &path, size_t blocks, size_t blockSize) :
        diskPath(path), totalBlocks(blocks), blockSize(blockSize) {};

