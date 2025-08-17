
#include "vfs.h"
#include <sstream>
#include <cstring>
#include <filesystem>

using namespace std;

VirtualFileSystem::VirtualFileSystem(const string &path, size_t blocks, size_t blockSize)
    : diskPath(path), totalBlocks(blocks), blockSize(blockSize) {}

bool VirtualFileSystem::mkfs() {
    fstream file(diskPath, ios::binary | ios::out | ios::trunc);
    if (!file) return false;

    vector<char> zero(blockSize, 0);
    for (size_t i = 0; i < totalBlocks; i++) {
        file.write(zero.data(), blockSize);
    }
    return true;
}

bool VirtualFileSystem::readAll(map<string, DirEntry> &entries) {
    ifstream file(diskPath, ios::binary);
    if (!file) return false;
    size_t n;
    file.read((char*)&n, sizeof(size_t));
    for (size_t i=0;i<n;i++) {
        size_t len;
        file.read((char*)&len, sizeof(size_t));
        string name(len, '\0');
        file.read(name.data(), len);
        DirEntry e;
        e.name = name;
        file.read((char*)&e.isDir, sizeof(bool));
        file.read((char*)&e.startBlock, sizeof(size_t));
        file.read((char*)&e.size, sizeof(size_t));
        entries[e.name] = e;
    }
    return true;
}

bool VirtualFileSystem::writeAll(const map<string, DirEntry> &entries) {
    fstream file(diskPath, ios::binary | ios::in | ios::out);
    if (!file) return false;
    file.seekp(0);
    size_t n = entries.size();
    file.write((const char*)&n, sizeof(size_t));
    for (auto &kv : entries) {
        size_t len = kv.first.size();
        file.write((const char*)&len, sizeof(size_t));
        file.write(kv.first.data(), len);
        file.write((const char*)&kv.second.isDir, sizeof(bool));
        file.write((const char*)&kv.second.startBlock, sizeof(size_t));
        file.write((const char*)&kv.second.size, sizeof(size_t));
    }
    return true;
}

bool VirtualFileSystem::mkdir(const string &dirPath) {
    map<string, DirEntry> entries;
    readAll(entries);
    if (entries.count(dirPath)) return false;
    DirEntry d{dirPath,true,0,0};
    entries[dirPath] = d;
    return writeAll(entries);
}

bool VirtualFileSystem::rmdir(const string &dirPath) {
    map<string, DirEntry> entries;
    readAll(entries);
    if (!entries.count(dirPath)) return false;
    entries.erase(dirPath);
    return writeAll(entries);
}

bool VirtualFileSystem::put(const string &hostFile, const string &vfsPath) {
    map<string, DirEntry> entries;
    readAll(entries);
    ifstream in(hostFile, ios::binary);
    if (!in) return false;
    vector<char> buffer((istreambuf_iterator<char>(in)), {});
    fstream file(diskPath, ios::binary | ios::in | ios::out);
    if (!file) return false;
    size_t start = sizeof(size_t); // simple naive placement after header
    file.seekp(start);
    file.write(buffer.data(), buffer.size());
    DirEntry d{vfsPath,false,start,buffer.size()};
    entries[vfsPath]=d;
    return writeAll(entries);
}

bool VirtualFileSystem::get(const string &vfsPath, const string &hostFile) {
    map<string, DirEntry> entries;
    readAll(entries);
    if (!entries.count(vfsPath)) return false;
    DirEntry d = entries[vfsPath];
    if (d.isDir) return false;
    ifstream file(diskPath, ios::binary);
    file.seekg(d.startBlock);
    vector<char> buffer(d.size);
    file.read(buffer.data(), d.size);
    ofstream out(hostFile, ios::binary);
    out.write(buffer.data(), buffer.size());
    return true;
}

bool VirtualFileSystem::rm(const string &vfsPath) {
    map<string, DirEntry> entries;
    readAll(entries);
    if (!entries.count(vfsPath)) return false;
    entries.erase(vfsPath);
    return writeAll(entries);
}

bool VirtualFileSystem::cat(const string &vfsPath) {
    map<string, DirEntry> entries;
    readAll(entries);
    if (!entries.count(vfsPath)) return false;
    DirEntry d = entries[vfsPath];
    if (d.isDir) return false;
    ifstream file(diskPath, ios::binary);
    file.seekg(d.startBlock);
    vector<char> buffer(d.size);
    file.read(buffer.data(), d.size);
    cout.write(buffer.data(), buffer.size());
    cout << "\n";
    return true;
}

bool VirtualFileSystem::ls(const string &dirPath) {
    map<string, DirEntry> entries;
    readAll(entries);
    for (auto &kv : entries) {
        if (kv.first.rfind(dirPath, 0) == 0) {
            cout << (kv.second.isDir ? "[DIR] " : "[FILE] ") << kv.first << "\n";
        }
    }
    return true;
}
