# cmake_minimum_required
```cmake
# cmake_minimum_required(VERSION <min>[...<policy_max>])
cmake_policy(VERSION 2.9...3.22)

# 1. <min> 和 <policy_max> 版本格式为 major.minor[.patch[.tweak]]
# 2. 设定变量 CMAKE_MINIMUM_REQUIRED_VERSION 为版本号 min
# 3. cmake 版本至少为 min 否则 fatal error (2.4 以后, FATAL_ERROR 被忽略)
# 4. 必须在 CMakeLists 的最开始调用, 因为必须要一开始指定必要的策略, 如果放在函数中再进行调用, 则函数的一些未定义
# 5. 指定引入的 policy 最高版本为 policy_max, 之后的版本策略为 unset
```

# cmake_policy
- 策略(policy): 代表 cmake 行为和特性的更新, 每个版本引入若干个新的行为
- 策略变量(CMP<NNNN>): N为整数, 有 OLD 和 NEW 两种, 版本之前包括本版本在内的所有策略为 NEW, 版本之后为 unset (除非设定了默认宏)
- CMAKE_POLICY_DEFAULT_CMP<NNNN>: 指定 unset 策略的默认宏, 只对 unset 策略有效, 会静默警告
```cmake
# cmake_policy(VERSION <min>[...<max>]) 
# cmake_minimum_required(...) 隐式调用 cmake_policy()

# 1. 设置版本要求范围 (新版本引入的策略 是 unset)
cmake_policy(VERSION 2.9...3.0)
# 2. 显示 设置策略(可能会静默 warning)
cmake_policy(SET CMP0001 OLD)
# 3. 获取 策略变量
cmake_policy(GET CMP0001 MY_VAR)

# 4. 关于默认宏, 不推荐在 CMakeLists 中设定默认宏, 而是手动设定
# CMakeLists 中通过 cmake_policy(SET) 设定
# cmake .. -DCMAKE_POLICY_DEFAULT_CMP<NNNN>=<OLD|NEW>

# 5. 策略栈 以 cmake_policy(PUSH) ... cmake_policy(POP) 成对出现, 在指定范围内设定特殊的策略
#    include(), find_package(), function(), macro()
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