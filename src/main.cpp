
#include "vfs.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: vfs <cmd> <disk> [args...]\n";
        return 1;
    }
    std::string cmd = argv[1];
    std::string disk = argv[2];
    VirtualFileSystem vfs(disk, 128);
    if (cmd=="mkfs") {
        size_t blocks = (argc>3)?std::stoul(argv[3]):128;
        VirtualFileSystem v(disk,blocks);
        if (v.mkfs()) std::cout<<"Created fs on "<<disk<<"\n";
    } else if (cmd=="mkdir") {
        if (argc<4) return 1;
        vfs.mkdir(argv[3]);
    } else if (cmd=="rmdir") {
        if (argc<4) return 1;
        vfs.rmdir(argv[3]);
    } else if (cmd=="put") {
        if (argc<5) return 1;
        vfs.put(argv[3], argv[4]);
    } else if (cmd=="get") {
        if (argc<5) return 1;
        vfs.get(argv[3], argv[4]);
    } else if (cmd=="rm") {
        if (argc<4) return 1;
        vfs.rm(argv[3]);
    } else if (cmd=="cat") {
        if (argc<4) return 1;
        vfs.cat(argv[3]);
    } else if (cmd=="ls") {
        if (argc<4) return 1;
        vfs.ls(argv[3]);
    }
}
