# libnbt++ 2

libnbt++ is a free C++ library for Minecraft's file format Named Binary Tag
(NBT). It can read and write compressed and uncompressed NBT files and
provides a code interface for working with NBT data.

----------

libnbt++2 is a remake of the old libnbt++ library with the goal of making it
more easily usable and fixing some problems. The old libnbt++ especially
suffered from a very convoluted syntax and boilerplate code needed to work
with NBT data.

## How to build:
Here is an template:
```shell
cmake -S [source dir] -B [build dir] -G [generator] -DCMAKE_C_COMPILER:FILEPATH=[C compiler] -DCMAKE_CXX_COMPILER:FILEPATH=[C++ compiler] -DCMAKE_INSTALL_PREFIX:PATH=[install dir]

cmake --build [build dir]
cmake --install [build dir]
```

**If you hope to use this library with cmake, do not ignore this thrid command.**

For example:
```shell
cd libnbtplusplus
cmake -S . -B ./build -G Ninja -DCMAKE_C_COMPILER:FILEPATH=gcc -DCMAKE_CXX_COMPILER:FILEPATH=g++ -DCMAKE_INSTALL_PREFIX:PATH=./install
cmake --build ./build
cmake --install ./build
```

## How to use
### 1. Find package

In cmake, you can find this package with `find_package`:
```cmake
find_package(libNBT++ 2.5.1 REQUIRED)
```
Here the version `2.5.1` and `REQUIRED` is optional. 

**Note that `find_package` requires that the installation prefix should be in `CMAKE_PREFIX_PATH`.**

### 2. Link to libraray


And when you have an target(executable , shared or static lib) that depends on NBT++, you should link to NBT++ by `target_link_libraries`:
```cmake
target_link_libraries([target-name] [PRIVATE|PUBLIC] libNBT++::NBT)
```

You do **not** need to manually add the include dir by `include_directories` or `target_include_directories`, these will be included for this target by `target_link_libraries`.

### 3. Include headers

Example:
```cpp
#include <libNBT++/nbt_tags.h>
```
Note that headers are installed in `${CMAKE_INSTALL_PREFIX}/include/libNBT++`, and the actual included directory is `${CMAKE_INSTALL_PREFIX}/include`. 