
# 1. 表达式基础
## 1.1 左值与右值
- 左值 : 用对象的身份, 内存位置 (如赋值, 取地址, 解引用, 递增递减都需要左值)
- 右值 : 用对象的值 (如用于赋值的常量对象, 取地址的结果, 只用于赋值的临时量)
- 通用原则 : 左值可以当作右值使用, 反过来不行
- 操作符与返回值 : 不同操作符对于左值还是右值的要求不同, 结果也会不同
```c++
int a = 3;
int *p = &a;
decltype(a) b = 3;  // 这里 a 为右值, 则取 a 的类型 int
decltype(*p) c = 3;  // 这里 *p 为左值, 则取 *p 的引用类型 int &
decltype(&p) d = 0x1234; // 这里 &p 为右值, 则取 &p 的类型为 int **
```
## 1.2 优先级与结合律
- 优先级 : 规定操作符是否被优先计算
- 结合律 : 规定操作符与操作数结合的规律 (左结合则操作数在操作符左边, 右结合同理)
- 过程 : 首先根据优先级判断哪些符号优先计算, 然后在优先级相等的符号中, 根据结合律方向一一计算 (同级操作符和结合律相同, 不同级操作符的结合率不一定相同)

## 1.3 求值顺序
- 尽管优先级和结合律规定运算对象的组合方式, 但是没有规定具体的求值顺序
- 同一表达式内, 各对象的求值顺序未定义 除非为 `&&`, `||`,  `,` 和 `: ?`
- 尽量使得对象在表达式内只在一个地方被修改, 被修改的对象只在一个地方出现, 否则会出现求值未定义情况

# 2. 运算符
## 2.1 算术运算符
- 运算对象和求值结果皆为右值
- 求值之前, 小整型会提升称为大整型
- 出于风格的考虑, bool 型不要用于运算, 如 assert(-true == true);
- m % (-n) == m % n (余数必为正), (-m % n) == -(m % n)
- 除法的商一律向零取整

## 2.2 逻辑与关系运算符
- 运算对象和求值结果皆为右值
```c++
if(val) 	// 非0任何值, 条件为真
if(!val) 	// 只有为0, 条件为真

// 除非 val 是bool 类型否则是错误写法 
//true会整型提升为1 产生偏差
if(val == true)  
```

## 2.3 赋值运算符
- 满足右结合律
- 优先级较低
- 容易误用为条件
- 尽量用复合赋值, 其求值次数要少于一般赋值语句

## 2.4 递增递减运算符
- 前置 : 运算后作为求值结果
- 后置 : 运算后以改变之前保留的副本作为求值结果
- 尽量用前置递增递减, 尤其运用在复杂类型上, 可以减少复杂类型的额外存储
- \*p++ == \*(p++)
- 递增对象出现在同一表达式的两个地方容易发生未定一情况

## 2.5 sizeof 运算符
- 用法 : `sizeof(type);` 或 `sizeof expr;`(并不计算表达式值而计算结果类型大小) 
```c++
#include <iostream>
#include <string>

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

  std::cout << sizeof num << "\n";  // 4
  std::cout << sizeof ref  << "\n";  // 4 引用所绑定类型大小
  std::cout << sizeof q << "\n";  // 8 指针大小
  std::cout << sizeof p << "\n";  // 8 指针大小
  std::cout << sizeof *q << "\n";  // 4 指针所指类型大小
  std::cout << sizeof *p << "\n";  // 4 指针不必是有效的
  std::cout << sizeof array << "\n";  // 400 数组总体大小 (不会发生退化)
  std::cout << sizeof str << "\n";  // 32 类型固定部分大小, 不包括元素部分
  std::cout << sizeof(Data) << "\n";  // 4 类大小
  std::cout << sizeof Data::a << "\n";  // 4 类数据成员类型大小

  // size_t 类型
  std::size_t = sizeof(num);
  // 返回值是常量表达式
  int array_test[sizeof array] = {};
  return 0;
}
```

## 2.6 其他
- 条件运算符优先级较低, 一般在两端加上括号
- 存在小整型提升, 对于有符号数的符号位处理依赖于实现, 建议用于无符号数
- 箭头运算符结果为左值
- 点运算符左右值根据对象而定
- 逗号运算符左右值根据最后对象而定


# 3. 类型转换
## 3.1 算术转换
- 转换过程 : 在计算表达式之前执行整型提升, 随后进行无符号类型转换, 最后小类型转换成大类型

### 整型提升
- bool, char(u) , short(u) 首先要提升为 int,  int 不足以表示则提升为 unsigned
- wchar\_t, char16\_t, char32\_t 会提升为 int(u), long(u), long long(u) 最小类型

### 无符号类型转换
```c++
unsigned int a = 10;
int b =11;
long c = 11;
auto r1 = a + b;  
// 1. sizeof(unsigned int) >= sizeof(int) : => unsigned int

auto r2 = a + c;
// 1. sizeof(unsigned int) == sizeof(long) : => unsigned int, 无符号数的所有值不能存在有符号数中
// 2. sizeof(unsigned int) < sizeof(long) : => long, 无符号数的所有值能存在有符号数中
```

## 3.2 隐式类型转换
- 自动执行的类型转换为隐式类型转换
### 数组名退化
```c++
int array[100] = {};
// 在表达式中, 数组退化成指针
int *p = array;

// 不发生退化的情况 :
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

void *e = c;           // XXX * -> void *
const void *f = d;     // const XXX * -> const void *
int *g = 0;            // 0 -> int *
int *h = nullptr;      // nullptr  -> int *
Base *base = &derived; // &Derived -> Base *
```
### 转换为布尔
- 算术类型 转换为 bool : 0 -> false, 其他  -> true 
- 指针类型 转换为 bool : NULL/nullptr -> false, 其他 -> true
### 转换为常量
- 非常量指针转换为 常量 : T -> T \* 
- 非常量指针转换为 引用 : T -> const T &
### 类类型定义转换
- 通过非 explict 的 单参数构造函数来转换

## 3.3 显式类型转换
- `static_cast<type>(var)`  用于任何不包含底层 const 的类型转换
- `const_cast<type>(var)` 用于去除底层 const
- `reinterpret_cast<type>(var)` 改变位模式
