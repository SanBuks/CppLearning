> 3.22.1 新增 summary

# cmake_policy
- 策略(policy): 代表 cmake 行为和特性的更新, 每个版本引入若干个新的行为
- 策略变量(CMP<NNNN>): N为整数, 有 OLD 和 NEW 两种, 版本之前包括本版本在内的所有策略为 NEW, 版本之后为 unset (除非设定了默认宏)

# Setting Policies by CMake Version
```cmake
# cmake_policy(VERSION <min>[...<max>]) 
# cmake_minimum_required(...) 隐式调用 cmake_policy()

# 设置版本要求范围 (新版本引入的策略 是 unset)
cmake_policy(VERSION 2.9...3.0)

# 关于默认宏 CMAKE_POLICY_DEFAULT_CMP<NNNN>
#  1) 指定 unset 策略的默认宏, 只对 unset 策略有效, 会静默警告
#  2) 不要在 CMakeLists 中设定默认宏, 而是通过命令 cmake .. -DCMAKE_POLICY_DEFAULT_CMP<NNNN>=<OLD|NEW>
```

# Setting Policies Explicitly
```cmake
# 显示 设置策略(可能会静默 warning)
cmake_policy(SET CMP0001 OLD)
```

# Checking Policy Settings
```cmake
# 获取 策略变量
cmake_policy(GET CMP0001 MY_VAR)
```

# CMake Policy Stack
```cmake
# 策略栈 以 cmake_policy(PUSH) ... cmake_policy(POP) 成对出现, 在指定范围内设定特殊的策略
# include(), find_package(), function(), macro()
#  1) 上述调用的策略栈中的预设值 在定义时设置, 而非调用时设置
#  2) 前二者的策略改动不会传播到调用作用域(除非指定 NO_POLICY_SCOPE), 而后二者会
cmake_policy(PUSH)
cmake_policy(SET CMP0001 OLD)
function(Test)
  cmake_policy(GET CMP0001 MY_VAR)
  message(STATUS ${MY_VAR})      # OLD
  cmake_policy(SET CMP0001 NEW)
endfunction()

cmake_policy(GET CMP0001 MY_VAR)
message(STATUS ${MY_VAR})        # OLD
Test()
cmake_policy(GET CMP0001 MY_VAR)
message(STATUS ${MY_VAR})        # NEW
cmake_policy(POP)

cmake_policy(GET CMP0001 MY_VAR)
message(STATUS ${MY_VAR})        # NEW
```