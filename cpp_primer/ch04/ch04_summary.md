# 1. 表达式基础
## 1.1 表达式
- 表达式: 由一个或多个运算对象和操作符组成, 可对其求值得到结果, 表达式本身也可以看作运算对象
- 字面值和变量: 最简单的表达式, 其结果就是本身的值
- 表达式的值类别属性: 左值和右值, 用于编译器优化和右值语义

## 1.2 左值与右值
- 左值: 用对象的身份, 内存位置 (如赋值, 取地址, 解引用, 递增递减都需要左值)
- 右值: 用对象的值 (如用于赋值的常量对象, 取地址的结果, 只用于赋值的临时量)
- 通用原则: 左值可以当作右值使用, 反过来不行
- 操作符与返回值: 不同操作符作用于对象后的结果不同, 还会影响 decltype 类型推断的结果
```c++
int a = 3;
int *p = &a;             // &a 作为结果为右值
                         // p  作为结果为左值

decltype(a) b = 3;       // a  作为结果为左值, decltype 推断为其本身类型为 int
decltype(*p) c = 3;      // *p 作为结果为左值, decltype 推断为其本身类型为 int &
decltype(&p) d = 0x1234; // &p 作为结果为右值, decltype 推断为其本身类型的指针 int **
```

## 1.3 优先级与结合律
- 优先级: 规定操作符是否被优先计算
- 结合律: 规定操作符与操作数结合的规律 (左结合则操作数在操作符左边, 右结合同理)
- 过程: 首先根据优先级判断哪些符号优先计算, 然后在优先级相等的符号中, 根据结合律方向一一计算 
- 规律: 同级操作符的结合律一定相同, 不同级操作符的结合律不一定相同

## 1.4 求值顺序
- 未定义求值顺序: 尽管优先级和结合律规定运算对象的组合方式, 但是没有规定具体的求值顺序
- 部分定义求值顺序的操作符: `&&`, `||`,  `,` 和 `: ?`
- 注意: 一个表达式内尽量使得某对象只在一处被修改, 否则会出现求值未定义情况
```c++
// my_io 若在在多处求值, 其状态改变的过程顺序未定义
return f(my_io) + h(my_io) - k(my_io);
```

# 2. 运算符
## 2.1 算术运算符
- 算术运算符能作用于任意算术类型, 算术运算符的 运算对象 和 求值结果皆为右值
- 算术类型在表达式求值之前, 小整型会提升称为大整型
```c++
// bool 型 true 小整形提升为 int 型 1
// 出于风格的考虑, bool 型不要用于运算
assert(-true == ture);  // 出错

// 补码除法 向零取整
std::cout << " 3 / 2 = " <<  3 / 2 << "\n";       //  1
std::cout << "-3 / 2 = " << -3 / 2 << "\n";       // -1
// 补码算术左移 向下取整
std::cout  << " 3 >> 1 = " << ( 3 >> 1) << "\n";  //  1
std::cout  << "-3 >> 1 = " << (-3 >> 1) << "\n";  // -2
    
//  m % -n == m % n 
std::cout << " 21 % -6 = " <<  21 % -6 << "\n";   //  3
// -m %  n == -(m % n)
std::cout << "-21 %  6 = " << -21 %  6 << "\n";   // -3
// -m % -n == -(m % n)
std::cout << "-21 % -6 = " << -21 % -6 << "\n";   // -3
```

## 2.2 逻辑与关系运算符
- 运算对象和求值结果皆为右值
- 优先级从高到低为: !; >=, ==; &&; ||
```c++
if ( val)   // 非 0 任何值, 条件为真
if (!val)  // 只有为 0,   条件为真

// 判断条件应该直接通过对象进行判断, 否则是错误写法 
if (val == true)  // 错误, true 会整型提升为 1
if (val)          // 正确
```

## 2.3 赋值运算符
- 满足右结合律, 优先级较低, 一般加上括号, 容易误用为条件
- 存在初始值列表初始化, 避免窄化转换
- 尽量用复合赋值, 其求值次数要少于一般赋值语句

## 2.4 递增递减运算符
- 前置: 运算后作为求值结果
- 后置: 运算后以改变之前保留的副本作为求值结果
- 尽量用前置递增递减, 尤其运用在复杂类型上, 可以减少复杂类型的额外存储
- \*p++ == \*(p++)
- 递增对象出现在同一表达式的两个地方容易发生未定一情况

## 2.5 成员访问运算符
- p->size() == (*p).size()
- 箭头运算符结果为左值
- 点运算符左右值根据对象而定

## 2.6 位运算符
- 位运算符对于有符号数的符号位处理依赖于实现, 建议用于无符号数
- 移位运算符的移动位数必须为正, 且小于操作数的位长, 否则是未定义行为
- 左移右侧增加 0, 正数右移左侧增加 0, 负数右移则视实现而定(一般增加的是符号位)
- 移位运算符的优先级低于算术运算符, 高于关系运算符

## 2.7 sizeof 运算符
- 结果: 表达式结果的类型大小, size_t 类型, 常量表达式
- 用法: `sizeof(type);` 或 `sizeof expr;`
```c++
class Data {
 public: 
  int a = 3;
};

int main() {
  int num = 32; 
  int &ref = num;
  int *p = &num;
  int *q = nullptr;
  int array[100] = {};
  std::string str = "12345678";

  std::cout << sizeof num     << "\n";  // 4   int 大小
  std::cout << sizeof ref     << "\n";  // 4   引用所绑定类型 大小
  std::cout << sizeof q       << "\n";  // 8   指针 大小
  std::cout << sizeof p       << "\n";  // 8   指针 大小
  std::cout << sizeof *q      << "\n";  // 4   指针所指类型 大小
  std::cout << sizeof *p      << "\n";  // 4   指针不必是有效的
  std::cout << sizeof array   << "\n";  // 400 数组总体 大小(不会发生退化)
  std::cout << sizeof str     << "\n";  // 32  类型固定部分 大小, 不包括元素部分
  std::cout << sizeof(Data)   << "\n";  // 4   类 大小
  std::cout << sizeof Data::a << "\n";  // 4   类数据成员类型 大小

  // size_t 类型
  std::size_t = sizeof(num);
  // 返回值是常量表达式
  int array_test[sizeof array] = {};
  
  return 0;
}
```

## 2.8 其他
- 条件运算符(三目运算符)优先级较低, 一般要加括号
- 逗号运算符表达式的值类别根据最右侧的对象而定

# 3. 隐式类型转换
## 3.1 算术转换
> 算术类型转换过程: 在计算表达式之前执行整型提升, 如果符号不一样, 则进行 无符号类型转换 或 小类型转换成大类型

### 整型提升
- bool, char(u), short(u) 首先提升为 int, int 不足以表示则提升为 unsigned
- wchar\_t, char16\_t, char32\_t 会提升为 int(u), long(u), long long(u) 最小类型

### 无符号类型转换
```c++
unsigned int a = 10;
int b  = 11;
long c = 11;

// 1. sizeof(unsigned int) >= sizeof(int) : => unsigned int
auto r1 = a + b;  

// 2. sizeof(unsigned int) < sizeof(long) : => long, 无符号数的所有值能存在有符号数中
//    sizeof(unsigned int) < sizeof(long) : => unsigned int, 无符号数的所有值不能存在有符号数中
auto r2 = a + c;  // 这里 unsigned int -> long
```

## 3.2 其他隐式类型转换
### 数组名退化
```c++
int array[100] = {};
// 在表达式中, 数组退化成指针
int *p = array;

// 不发生退化的情况: (还有 typeid)
decltype(array) s = {};             // decltype 
std::cout << sizeof(array) << "\n"; // sizeof
int (&array_ref)[100] = array;      // 引用声明
std::cout << &array + 1 << " " 
          << array + 1 << "\n";     // 取地址
```

### 转换为指针
```c++
int a = 1; const int b = 3;
int *c = &a;
const int *d = &b;

void *e = c;           // XXX *       -> void *
const void *f = d;     // const XXX * -> const void *

int *g = 0;            // 0           -> int *
int *h = nullptr;      // nullptr     -> int *

Base *base = &derived; // Derived *   -> Base *
```

### 转换为布尔
```c++
bool b = 0;         // 0 -> false
bool a = 1;         // 其他 -> true 
                    
bool c = nullptr;   // nullptr -> false
bool d = NULL;      // NULL -> false
bool e = &b;        // 其他 -> true
```

### 转换为常量
```c++
int a; 
const int &b = a;   // T -> const T &, 非常量转换为指向常量的引用
const int *c = &a;  // T * -> const T *, 指向非常量指针转换为 指向常量的指针
```

### 类类型定义转换
- 转换构造函数

## 3.3 显式类型转换
- `static_cast<type>(var)`: 用于任何不包含底层 const 的类型转换
- `const_cast<type>(var)`: 用于去除底层 const
- `reinterpret_cast<type>(var)`: 改变位模式