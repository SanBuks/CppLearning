# 第四章 表达式
## 1. 表达式基础
### 左值与右值
- 左值 : 用对象的身份, 内存位置 ( 如赋值, 取地址, 解引用, 递增递减都需要左值)
- 右值 : 用对象的值, 左值可以当作右值使用, 反过来不行

### 求值顺序
- 同一表达式内, 各对象的求值顺序未定义 除非为 `&&`, `||`,  `,` 和 `: ?`
- 尽量用复合赋值因为其求值次数要少于一般赋值语句
- 尽量使得对象在表达式内只在一个地方被修改, 被修改的对象只在一个地方出现

### 类型转换
#### 整型提升
- 定义 : 在表达式计算时，各种整型 (bool, short, char) 首先要提升为 int，如果 int 不足以表示的话，就需要提升为unsigned int类型，然后再执行表达式的运算
- wchar\_t, char16\_t, char32\_t 会提升为 int(u), long(u), long long(u) 最小类型

#### 无符号类型转换
```c++
unsigned int a = 10;
int b =11;
long c = 11;
auto r1 = a + b;  
// 1. sizeof(unsigned int) >= sizeof(int) : => unsigned int

auto r2 = a + c;
// 1. sizeof(unsigned int) == sizeof(long) : => unsigned int
// 2. sizeof(unsigned int) < sizeof(long) : => long
```

#### 隐式类型转换
- 数组名退化成首元素指针
- anyptr => void \* 或 const anyptr => const void \*
- 0 / nullptr => anyptr
- 非底层const => 底层const
- 指针或算数类型 => bool (条件中)
- 类类型定义转换

#### 显式类型转换
- `static_cast<type>(var)`  用于任何不包含底层const的类型转换
- `const_cast<type>(var)` 用于去除底层const
- `reinterpret_cast<type>(var)` 改变位模式

## 2. 运算符
### 算数运算符
- 算数运算符求值结果为右值
- 除法的商一律向零取整, 模数结果的正负号与被模数相同

### 逻辑与关系运算符
- 逻辑与关系运算符结果为布尔右值
```c++
if(val) 	// 非0任何值, 条件为真
if(!val) 	// 只有为0, 条件为真
if(val == true)  // 除非val是bool类型否则是错误写法, true会整型提升为1 产生偏差
```

### sizeof 运算符
- 返回 : size\_t类型常量表达式
- 用法 : `sizeof(type);` 或 `sizeof expr;`(并不计算表达式值而计算结果类型大小) 
- 结果 : 
    - 引用 -> 实际类型大小
    - 指针 -> 指针大小
    - \*指针 -> 指针所指类型大小 ( 指针不必是有效的 )
    - 数组 -> 数组总体大小 (不会发生退化)
    - string / vector -> 类型固定部分大小, 不包括元素部分

### 其他
- 尽量用前置递增递减, 尤其运用在复杂类型上, 可以减少复杂类型的额外存储
- 条件运算符优先级较低, 一般在两端加上括号
- 箭头运算符结果为左值, 点运算符左右值根据对象而定, 逗号运算符左右值根据最后对象而定
- 位运算符对于符号处理未定义, 尽量用于无符号数
