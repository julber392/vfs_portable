
# Virtual File System in File (Portable C++)

## Build
```
mkdir build && cd build
cmake ..
cmake --build .
```

## Usage
```
./vfs mkfs disk.img 16
./vfs mkdir disk.img /docs
./vfs put disk.img README.md /docs/readme.txt
./vfs ls disk.img /docs
./vfs cat disk.img /docs/readme.txt
./vfs get disk.img /docs/readme.txt out.txt
./vfs rm disk.img /docs/readme.txt
./vfs rmdir disk.img /docs
```
