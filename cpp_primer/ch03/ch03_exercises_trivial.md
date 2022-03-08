# 3.01
> 使用恰当的using 声明重做 1.4.1节和2.6.2节的练习。
```c++
// 1.09
int main(int argc, char *argv[]) {
  int sum = 0, n = 50;
  while (n != 101) {
    sum += n++;
  }
  cout << sum;  // 3825
  return 0;
}
// 1.10
int main(int argc, char *argv[]) {
  int n = 10;
  while (n != -1) {
    std::cout << n-- << " ";
  }
  return 0;
}
// 其余略
```

# 3.02
> 编写一段程序从标准输入中一次读入一行，然后修改该程序使其一次读入一个词。
```c++
int main() {
  std::string str;
  // while(std::cin>>str)
  while (getline(std::cin, str)) {
    std::cout << str << std::endl;
  }
  return 0;
}
```

# 3.04
> 编写一段程序读取两个字符串，比较其是否相等并输出结果。如果不相等，输出比较大的那个字符串。
> 改写上述程序，比较输入的两个字符串是否等长，如果不等长，输出长度较大的那个字符串。
```c++
std::string cmp(const std::string &s1, const std::string &s2) {
  if (s1 == s2) {
    return s1;    // if (s1.size() == s2.size()) { return s1; }
  } else {
    if (s1 > s2) {
      return s1;  // if (s1.size() > s2.size()) { return s1; }
    } else {
      return s2;
    }
  }
}
```

# 3.05
> 编写一段程序从标准输入中读入多个字符串并将他们连接起来，输出连接成的大字符串。然后修改上述程序，用空格把输入的多个字符串分割开来。
```c++
int main() {
  std::string str1, str2;
  while (std::cin >> str2) {
    str1 += str2 + " ";
  }
  std::cout << str1;
  return 0;
}
```

# 3.06
> 编写一段程序，使用范围for语句将字符串内所有字符用X代替。

见下一题

# 3.07
> 就上一题完成的程序而言，如果将循环控制的变量设置为char将发生什么？先估计一下结果，然后实际编程进行验证。
```c++
int main() {
  std::string s1("12345");
  std::cout << s1 << std::endl;
  // for (char &it : s1)
  for (auto &it: s1) {
    it = 'x';
  }
  std::cout << s1;
  return 0;
}
```

# 3.08
> 分别用while循环和传统for循环重写第一题的程序，你觉得哪种形式更好呢？为什么？
```c++
for (decltype(s1.size()) index = 0; index < s1.size(); index++) {
  s1[index] = 'x';
}

decltype(s1.size()) index = 0;
while (index < s1.size()) {
  s1[index] = 'x';
  ++index;
}
// range-for 更加简洁
```

# 3.10
> 编写一段程序，读入一个包含标点符号的字符串，将标点符号去除后输出字符串剩余的部分。
```c++
std::string remove_punct(const std::string &s) {
  std::string str;
  for (const auto &it: s) {
    if (!ispunct(it)) {
      str += it;
    }
  }
  return str;
}
int main() {
  std::string s1("123.2?5/45'+-");
  std::cout << s1 << std::endl;
  std::cout << remove_punct(s1);
  return 0;
}
```

# 3.12
> 下列vector对象的定义有不正确的吗？如果有，请指出来。对于正确的，描述其执行结果；对于不正确的，说明其错误的原因。
```c++
vector<vector<int>> ivec;         // 合法
vector<string> svec = ivec;       // 非法, 类型不同
vector<string> svec(10, "null");  // 合法
```

# 3.14
> 编写一段程序，用cin读入一组整数并把它们存入一个vector对象。
```c++
int main() {
  int a;
  std::vector<int> v;
  while (std::cin >> a) {
    v.push_back(a);
  }
  for (const auto &it: v) {
    std::cout << it << " ";
  }
  return 0;
}
```

# 3.15
> 改写上题程序，不过这次读入的是字符串。
```c++
int main() {
  std::string str;
  std::vector<std::string> v;
  while (std::cin >> str) {
    v.push_back(str);
  }
  for (const auto &it: v) {
    std::cout << it << " ";
  }
  return 0;
}
```

# 3.16
> 编写一段程序，把练习3.13中vector对象的容量和具体内容输出出来

参考 3.13

# 3.17
> 从cin读入一组词并把它们存入一个vector对象，然后设法把所有词都改为大写形式。输出改变后的结果，每个词占一行。
```c++
int main() {
  std::string str;
  std::vector<std::string> v;
  while (std::cin >> str) {
    v.push_back(str);
  }
  for (const auto &it: v) {
    std::cout << it << " ";
  }
  std::cout << std::endl << "--------------" << std::endl;
  for (auto &word: v) {
    for (auto &letter: word) {
      letter = toupper(letter);
    }
  }
  for (const auto &it: v) {
    std::cout << it << std::endl;
  }
  return 0;
}
```

# 3.18
> 下面的程序合法吗？如果不合法，你准备如何修改？
```c++
vector<int> ivec;
ivec[0] = 42;  // 非法, 改为 ivec.push_back(42);
```

# 3.19
> 如果想定义一个含有10个元素的vector对象，所有元素的值都是42，请例举三种不同的实现方法，哪种方式更好呢？
```c++
// 最好方式
vector<int> vec(10, 42);
// 第二种方式
vector<int> vec(10);
for (auto &it: vec) {
  it = 42;
}
// 第三种方式
vector<int> vec;
for (int i = 0; i != 10; ++i) {
  vec.push_back(42);
}
```

# 3.21
> 请使用迭代器重做3.3.3节的第一个练习。

参考 3.13


# 3.22
> 修改之前那个输出text第一段的程序，首先把text的第一段全部改成大写形式，然后输出它。
```c++
int main() {
  std::fstream ifs("ch03_data/data_03_22");
  if (!ifs) {
    std::cout << "open file failure\n";
    return 1;
  }
  std::string line;
  std::vector<std::string> text;

  while (getline(ifs, line) && !line.empty()) {
    text.push_back(line);
  }
  for (auto it = text.cbegin(); it != text.cend() && !it->empty(); ++it) {
    for (const auto &letter: *it) {
      std::cout << static_cast<char>(toupper(letter));
    }
    std::cout << std::endl;
  }
  return 0;
}
```

# 3.23
> 编写一段程序，创建一个含有10个整数的vector对象，然后使用迭代器将所有元素的值都变成原来的两倍。输出vector对象的内容，检验程序是否正确。
```c++
int main() {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (auto it = v.begin(); it != v.end(); ++it) {
    *it = 2 * (*it);
  }
  for (const auto &item: v) {
    std::cout << item << " ";
  }
  return 0;
}
```

# 3.25
> 3.3.3节划分分数段的程序是使用下标运算符实现的，请利用迭代器改写该程序实现完全相同的功能。
```c++
int main() {
  int n;
  std::vector<int> v(11, 0);
  while (std::cin >> n) {
    int index = n / 10;
    auto it = v.begin();
    for (; index > 0; --index) {
      it++;
    }
    (*it)++;
  }
  int index = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    std::cout << index << " : " << *it << "\n";
    ++index;
  }
  return 0;
}
```

# 3.29
> 相比于vector 来说，数组有哪些缺点，请例举一些。

- 数组大小固定
- 不可被拷贝赋值
- 没有迭代器, 存在越界风险

# 3.30
> 指出下面代码中的索引错误。
```c++
constexpr size_t array_size = 10;
int ia[array_size];
for (size_t ix = 1; ix <= array_size; ++ix) {  // ix < array_size
  ia[ix] = ix;
}
```

# 3.31
> 编写一段程序，定义一个含有10个int的数组，令每个元素的值就是其下标值。
```c++
int main() {
  constexpr size_t size = 10;
  int arr[size] = {};
  for (size_t i = 0; i < size; ++i) {
    arr[i] = i;
  }
  for (const auto &item: arr) {
    std::cout << item << " ";
  }
  return 0;
}
```

# 3.32
> 将上一题刚刚创建的数组拷贝给另一数组。利用vector重写程序，实现类似的功能。
```c++
int main() {
  constexpr size_t size = 10;
  int arr[size] = {};

  for (size_t i = 0; i < size; ++i) {
    arr[i] = i;
  }
  std::vector<int> vec(std::begin(arr), std::end(arr));
  std::vector<int> vec1(vec);
  for (const auto &item: vec1) {
    std::cout << item << " ";
  }
  return 0;
}
```

# 3.33
> 对于104页的程序来说，如果不初始化scores将会发生什么？

dynamic init 未定义

# 3.34
> 假定p1 和 p2 都指向同一个数组中的元素，则下面程序的功能是什么？什么情况下该程序是非法的？
```c++
p1 += p2 - p1;
```

p1 指向 p2 所指位置 

# 3.35
> 编写一段程序，利用指针将数组中的元素置为0。
```c++
int main() {
  int arr[4] = {1, 2, 3, 4};
  for (auto it = arr; it != arr + 4; ++it) {
    *it = 0;
  }
  for (const auto &item: arr) {
    std::cout << item << " ";
  }
  return 0;
}
```

# 3.36
> 编写一段程序，比较两个数组是否相等。再写一段程序，比较两个vector对象是否相等。
```c++
bool is_equal(const int *a, size_t a_size, const int *b, size_t b_size) {
  if (a_size == b_size) {
    for (auto ap = a, bp = b; ap != a + a_size; ++ap, ++bp) {
      if (*ap != *bp) {
        return false;
      }
    }
    return true;
  }
  return false;
}

bool is_equal(const std::vector<int> &lhs, const std::vector<int> &rhs) {
  return lhs == rhs;
}
```

# 3.37
> 下面的程序是何含义，程序的输出结果是什么？
```c++
const char ca[] = { 'h', 'e', 'l', 'l', 'o' };
const char *cp = ca;
while (*cp) {  // 以非 '\0' 结尾, 会一直从ca开头循环内存直到发现'\0'
  cout << *cp << endl;
  ++cp;
}
```

# 3.39
> 编写一段程序，比较两个 string 对象。再编写一段程序，比较两个C风格字符串的内容。
```c++
bool isequal(const char *a, size_t a_size, const char *b, size_t b_size) {
  if (a_size == b_size) {
    for (auto ap = a, bp = b; ap != a + a_size; ++ap, ++bp) {
      if (*ap != *bp) {
        return false;
      }
    }
    return true;
  }
  return false;
}

bool isequal(const std::string &s1, const std::string &s2) {
  return s1 == s2;
}
```

# 3.41
> 编写一段程序，用整型数组初始化一个vector对象。
```c++
int main() {
  int a[] = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> v(std::begin(a), std::end(a));
  for (const auto &item: v) {
    std::cout << item << " ";
  }
  return 0;
}
```

# 3.42
> 编写一段程序，将含有整数元素的 vector 对象拷贝给一个整型数组。
```c++
int main() {
  int a[] = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> v(std::begin(a), std::end(a));
  int *p = new int[v.size()];
  for (size_t i = 0; i < v.size(); ++i) {
    p[i] = v[i];
    std::cout << p[i] << " ";
  }
  return 0;
}
```