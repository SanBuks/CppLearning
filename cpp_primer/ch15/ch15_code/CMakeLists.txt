cmake_minimum_required(VERSION 3.20)
project(ch15 LANGUAGES CXX)

# 编译标准 和 构建类型
set(CMAKE_CXX_STANDARD 11          CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE INTERNAL "" FORCE)
set(CMAKE_BUILD_TYPE Debug         CACHE INTERNAL "" FORCE)

# 子目录
add_subdirectory(quote)
add_subdirectory(shape)
add_subdirectory(query)



# D:\DevelopTool\msys2\mingw64\bin\cmake.exe -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=D:/DevelopTool/msys2/mingw64/bin/make.exe -DCMAKE_C_COMPILER=D:/DevelopTool/msys2/mingw64/bin/gcc.exe -DCMAKE_CXX_COMPILER=D:/DevelopTool/msys2/mingw64/bin/g++.exe -DCMAKE_DEPENDS_USE_COMPILER=FALSE -G "CodeBlocks - MinGW Makefiles" D:\Project\LEARNING\CppLearning\cpp_primer\ch15\ch15_code
# cmake -G"MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_MAKE_PROGRAM=make