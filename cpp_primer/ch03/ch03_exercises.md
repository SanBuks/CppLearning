# 3.03 getline 与 cin 区别
> 请说明string类的输入运算符和getline函数分别是如何处理空白字符的。

1. `is>>str;` 忽略空白符, 读入字符直到遇到空白符为止, 返回 is 
2. `getline(is, str)` 忽略空白符, 读入一行直到换行符为止(包含`\n`), 舍弃`\n`后赋予str, 返回 is

# 3.09 访问容器元素需要判断是否存在
> 下面的程序有何作用？它合法吗？如果不合法？为什么？
```c++
string s;
cout << s[0] << endl; // 首先需要判断是否为空, 否则访问未定义
```

# 3.11 for-range 不可修改元素个数
> 下面的范围for语句合法吗？如果合法，c的类型是什么？
```c++
const string s = "Keep out!";
for(auto &c : s){ /* ... */ }
// c 为 const char & 只读操作合法, 写操作非法
```

# 3.13 值初始化与列表初始化
> 下列的vector对象各包含多少个元素？这些元素的值分别是多少？
```c++
vector<int> v1;         // 0个元素 {}
vector<int> v2(10);     // 10个元素 {0,0,...,0}
vector<int> v3(10, 42); // 10个元素 {42,42,...,42}
vector<int> v4{ 10 };   // 1个元素 {10}
vector<int> v5{ 10, 42 }; // 2个元素 {10,42}
vector<string> v6{ 10 };  // 10个元素 {"", ..., ""}
vector<string> v7{ 10, "hi" };  // 10个元素 {"hi", "hi", ..., "hi"}
```

# 3.20 无符号注意事项
> 读入一组整数并把他们存入一个vector对象，将每对相邻整数的和输出出来。改写你的程序，这次要求先输出第一个和最后一个元素的和，接着输出第二个和倒数第二个元素的和，以此类推。
```c++
#include <iostream>
#include <vector>
int main(){
  int a;
  std::vector<int> v;
  while (std::cin >> a) {
    v.push_back(a);
  }
  for (const auto &it: v) {
    std::cout << it << " ";
  }
  std::cout << std::endl;
  // 邻接求值
  if (v.size() > 1) { // 判断是否有邻接数
    for (decltype(v.size()) index = 1; index < v.size(); ++index) {
      std::cout << v[index] + v[index - 1] << " ";
    }
  }
  // 前后求值
  if (!v.empty()) {
    if (v.size() > 1) { // 注意 只有一个元素用 <= 会发生错误
      for (decltype(v.size()) b = 0, e = v.size() - 1; b <= e; ++b, --e) {
        std::cout << v[b] + v[e] << " ";
      }
    } else {
      std::cout << 2 * v[0];
    } 
  }
  return 0;
}
```

# 3.24 无符号下标与迭代器区别
> 请使用迭代器重做3.3.3节的最后一个练习。
```c++
#include <iostream>
#include <vector>
int main(){
  int a;
  std::vector<int> v;
  
  while (std::cin >> a) {
    v.push_back(a);
  }
  // 邻接求值
  if (v.size() > 1) {  // 判断是否有邻接数
    for (auto it = v.begin() + 1; it != v.end(); ++it) {
      std::cout << *it + *(it - 1) << " ";
    }
  }
  // 前后求值
  if (!v.empty()) {
    for (auto b = v.begin(), e = v.end() - 1; b <= e; ++b, --e) {
      std::cout << *b + *e << " ";
    }
  }

  return 0;
}
```

# 3.26 迭代器不可相加
> 在100页的二分搜索程序中，为什么用的是 mid = beg + (end - beg) / 2, 而非 mid = (beg + end) / 2  ?

迭代器相加没有意义, 不支持相加操作

# 3.27 数组下标要求
> 假设txt_size是一个无参函数，它的返回值是int。请回答下列哪个定义是非法的，为什么？
```c++
unsigned buf_size = 1024;
int ia[buf_size];             // 合法
int ia[4 * 7 - 14];           // 合法
int ia[txt_size()];           // 取决于 txt_size 是否是 constexpr 函数
char st[11] = "fundamental";  // 非法, 11+1('\0')
```

# 3.28 静态和非静态 默认初始化
> 下列数组中元素的值是什么？
```c++
string sa[10];     // dynamic init 都是 空串
int ia[10];        // zero init 都是 0
int main() {
  string sa2[10];  // dynamic init 空串
  int ia2[10];     // dynamic init 随机值
  return 0;
}
```

# 3.38 指针不可相加
> 在本节中我们提到，将两个指针相加不但是非法的，而且也没有什么意义。请问为什么两个指针相加没有意义？

- 相减可以表示两个指针相对位置, 相加并没有逻辑上的意义
- 内存分布不一定是有序递增的
- 相加需要处理额外的类型大小问题

# 3.40 strcpy 与 strcat
> 编写一段程序，定义两个字符数组并用字符串字面值初始化它们；接着再定义一个字符数组存放前面两个数组连接后的结果。使用strcpy和strcat把前两个数组的内容拷贝到第三个数组当中。
```c++
#include <iostream>
#include <cstring>
  
int main() {
  const char *p1 = "123";
  const char *p2 = "456789";
  char *q = new char[strlen(p1) + strlen(p2) + 1];
  strcpy(q, p1);
  strcat(q, p2);
  std::cout << q;
  return 0;
}
```

# 3.43 for-range auto 遍历多维数组
> 编写3个不同版本的程序，令其均能输出ia的元素。 版本1使用范围for语句管理迭代过程；版本2和版本3都使用普通for语句，其中版本2要求使用下标运算符，版本3要求使用指针。 此外，在所有3个版本的程序中都要直接写出数据类型，而不能使用类型别名、auto关键字和decltype关键字。
```c++
int ia[3][4];
for (const auto (&row): ia) {
  for (const auto &col: row) {
    cout << col << " ";
  }
}

for (size_t row = 0; row < 3; ++row) {
  for (size_t col = 0; col < 4; ++col) {
    cout << ia[row][col] << " ";
  }
}

for (int (*row)[4] = ia; row != ia + 3; ++row) {
  for (int *col = *row; col != *row + 4; ++col) {
    cout << *col << " ";
  }
}
```

# 3.44 for-range decltype 遍历多维数组
> 改写上一个练习中的程序，使用类型别名来代替循环控制变量的类型。
```c++
int ia[3][4] = {};
for (decltype(ia[0]) row: ia) {
  for (decltype(ia[0][0]) col: row) {
    cout << col << " ";
  }
}
```

# 3.45 for-range auto 遍历多维数组
> 再一次改写程序，这次使用 auto 关键字。
```c++
int ia[3][4];
for (const auto (&row): ia) {
  for (const auto &col: row) {
    cout << col << " ";
  }
}
```