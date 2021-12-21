> 3.22.1 新增 summary

# cmake_minimum_required
```cmake
# cmake_minimum_required(VERSION <min>[...<policy_max>])
cmake_policy(VERSION 2.9...3.22)

# <min> 和 <policy_max> 版本格式为 major.minor[.patch[.tweak]]

# cmake 版本至少为 min 否则 fatal error (2.4 以后, FATAL_ERROR 被忽略)
# 指定引入的 policy 最高版本为 policy_max, 之后版本策略为 unset

# 设定变量 CMAKE_MINIMUM_REQUIRED_VERSION 为版本号 min

# 必须在 CMakeLists 的最开始调用, 因为必须要一开始指定必要的策略, 如果放在函数中再进行调用, 则某些行为未定义
```

# Policy Settings
- 会隐式调用 cmake_policy()
- 在版本之前(包含此版本)的策略被设定为 NEW, 之后的策略为 unset
