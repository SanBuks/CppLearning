```cmake
# 增加 目标的 include 目录 (等效于 -Idir)
target_include_direcotries(Tutorial
                           SYSTEM   # 视为系统头文件
                           AFTER    # 追加在包含头文件路径之前, (BEFORE)
                           PRIVATE  # 定义作用域
                           "${PROJECT_SOURCE_DIR}/include")
```
