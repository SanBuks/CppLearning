```bash
# [modern-cmake] 项目基本结构
- project
  - .gitignore
  - README.md
  - LICENCE.md
  - CMakeLists.txt
  - cmake
    - FindSomeLib.cmake
    - something_else.cmake
  - include  # 头文件目录中没有 CmakeLists 
    - project  # 内置 project 目录 防止 install headers 产生冲突
      - lib.hpp
  - src
    - CMakeLists.txt
    - lib.cpp
  - apps
    - CMakeLists.txt
    - app.cpp
  - tests
    - CMakeLists.txt
    - testlib.cpp
  - docs
    - CMakeLists.txt
  - extern
    - googletest
  - scripts
    - helper.py
```

- 在 include 内设本项目文件夹和多个子项目文件夹有助于避免头文件冲突
- 如 #include "project/sub1/static/yyy.h"
