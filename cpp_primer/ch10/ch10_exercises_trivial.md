# 10.01
> 头文件algorithm中定义了一个名为count的函数，它类似find， 接受一对迭代器和一个值作为参数。count返回给定值在序列中出现的次数。
> 编写程序，读取int序列存入vector中，打印有多少个元素的值等于给定值。

# 10.02
> 重做上一题，但读取 string 序列存入 list 中。
```c++
int main() {
  using namespace std;
  vector<int> vec{1, 2, 2, 4, 4, 6, 6, 6, 9, 10};
  list<string> lst{"1", "1", "2", "2", "2", "3"};
  std::cout << count(vec.begin(), vec.end(), 6) << "\n";
  std::cout << count(lst.begin(), lst.end(), string("1")) << "\n";
  return 0;
}
```

# 10.03
> 用 accumulate求一个 vector<int> 中元素之和。
```c++
#include <numeric>

int main() {
  using namespace std;
  vector<int> vec{1, 2, 2, 4, 4, 6, 6, 6, 9, 10};
  std::cout << accumulate(vec.begin(), vec.end(), 0);
  return 0;
}
```

# 10.05
> 在本节对名册（roster）调用equal的例子中，如果两个名册中保存的都是C风格字符串而不是string，会发生什么？

发生错误, 保存的C风格字符串本质是指针, 对指针做 == 操作没有意义

# 10.06
> 编写程序，使用 fill_n 将一个序列中的 int 值都设置为0。
```c++
int main() {
  using namespace std;
  vector<int> vec{1, 2, 2, 4, 4, 6, 6, 6, 9, 10};
  fill_n(vec.begin(), vec.size(), 0);
  for_each(vec.begin(), vec.end(), [](const int &item) {
                                     std::cout << item << " "; });
  return 0;
}
```

# 10.07
> 下面程序是否有错误？如果有，请改正：
```c++
// (a)
vector<int> vec; 
list<int> lst; 
int i;
while (cin >> i)
  lst.push_back(i);
// 出错, vec 至少 与 lst 元素数量相同
// copy(lst.cbegin(), lst.cend(), back_inserter(vec));
copy(lst.cbegin(), lst.cend(), vec.begin());
  
// (b)  
vector<int> vec;
vec.reserve(10);
// vec 为空, 没有效果
// fill_n(back_inserter(vec), 10, 0);
fill_n(vec.begin(), 10, 0);
```

# 10.8
> 本节提到过，标准库算法不会改变它们所操作的容器的大小。为什么使用 back_inserter不会使这一断言失效？

back_inserter 是迭代器适配器的一种, 形式上是调用迭代器的 = 运算符, 在在形式上不改变容器大小

# 10.09
> 实现你自己的elimDups。分别在读取输入后、调用unique后以及调用erase后打印vector的内容。
```c++
template<typename T>
void ElimDups(std::vector<T> &vec) {
  std::sort(vec.begin(), vec.end());
  for_each(vec.begin(), vec.end(),
           [](const int &elem){ std::cout << elem << " ";});
  std::cout << "\n";

  auto erase_begin_it = std::unique(vec.begin(), vec.end());
  for_each(vec.begin(), vec.end(),
           [](const int &elem){ std::cout << elem << " ";});
  std::cout << "\n";

  vec.erase(erase_begin_it, vec.end());
  for_each(vec.begin(), vec.end(),
           [](const int &elem){ std::cout << elem << " ";});
  std::cout << "\n";
}

int main() {
  using namespace std;
  vector<int> vec{1, 3, 2, 3, 4, 7, 9, 5, 7, 10, 1};
  ElimDups(vec);
  return 0;
}
```

# 10.10
> 你认为算法不改变容器大小的原因是什么？

解耦, 改变容器的大小操作 可以通过 范围-语义 实现, 范围可以通过算法得出的迭代器表示, 语义可以通过容器本身的操作实现

# 10.11
> 编写程序，使用 stable_sort 和 isShorter 将传递给你的 elimDups 版本的 vector 排序。打印 vector的内容，验证你的程序的正确性。
```c++
bool IsShorter(const std::string &str1,  const std::string &str2) {
  return str1.size() < str2.size();
}

int main() {
  using namespace std;
  vector<string> vec{"123", "23", "3333", ""};
  stable_sort(vec.begin(), vec.end(), IsShorter);
  for_each(vec.begin(), vec.end(),
           [](const string &elem){ std::cout << elem << " ";});
  return 0;
}
```

# 10.12
> 编写名为 compareIsbn 的函数，比较两个 Sales_data 对象的isbn() 成员。使用这个函数排序一个保存 Sales_data 对象的 vector。

见 10.17

# 10.13
> 标准库定义了名为 partition 的算法，它接受一个谓词，对容器内容进行划分，
> 使得谓词为true 的值会排在容器的前半部分，而使得谓词为 false 的值会排在后半部分。
> 算法返回一个迭代器，指向最后一个使谓词为 true 的元素之后的位置。
> 编写函数，接受一个 string，返回一个 bool 值，指出 string 是否有5个或更多字符。使用此函数划分 words。打印出长度大于等于5的元素。
```c++
int main() {
  using namespace std;
  vector<string> vec{"2134", "2", "", "324324234", "234123413241"};
  auto eit = partition(vec.begin(), vec.end(), [](const string& str) {
                                                 return str.size() >= 5; });
  for_each(vec.begin(), eit,
           [](const string &elem){ std::cout << elem << " ";});
  return 0;
}
```

# 10.14
> 编写一个lambda，接受两个int，返回它们的和。
```c++
auto it = [](int lhs, int rhs) { return lhs + rhs; }
```

# 10.15
> 编写一个 lambda ，捕获它所在函数的 int，并接受一个 int参数。lambda 应该返回捕获的 int 和 int 参数的和。
```c++
int main() {
  using namespace std;
  int sz = 10;
  auto f_ = [sz](int num) -> int { return sz + num; };
  std::cout << f_(1);
  return 0;
}
```

# 10.16
> 使用 lambda 编写你自己版本的 biggies。

见 10.18

# 10.17
> 重写10.3.1节练习10.12的程序，在对sort的调用中使用 lambda 来代替函数 compareIsbn。
```c++
struct Sales_data {
  Sales_data() = default;
  explicit Sales_data(std::string bookNo) : bookNo_(std::move(bookNo)) {};
  std::string bookNo_;
  unsigned units_sold_ = 0;
  double revenue_ = 0.0;
};

bool IsShorter(const Sales_data &lhs,  const Sales_data &rhs) {
  return lhs.bookNo_.size() < rhs.bookNo_.size();
}

int main() {
  using namespace std;
  vector<Sales_data> vec{Sales_data{"1"}, Sales_data{"123"},
                         Sales_data{"0123"}, Sales_data{"23"},
                         Sales_data{"3333"}, Sales_data{"444444"}};
  stable_sort(vec.begin(), vec.end(), IsShorter);
  // stable_sort(vec.begin(), vec.end(), [](const Sales_data &lhs,  const Sales_data &rhs) {
  //                                       return lhs.bookNo_.size() < rhs.bookNo_.size(); });
  for_each(vec.begin(), vec.end(),
           [](const Sales_data &elem){ std::cout << elem.bookNo_ << " ";});
  return 0;
}
```

# 10.18
> 重写 biggies，用 partition 代替 find_if。我们在10.3.1节练习10.13中介绍了 partition 算法。

# 10.19
> 用 stable_partition 重写前一题的程序，与 stable_sort 类似，在划分后的序列中维持原有元素的顺序。
```c++
template<typename T>
void ElimDups(std::vector<T> &vec) {
  std::sort(vec.begin(), vec.end());
  auto erase_begin_it = std::unique(vec.begin(), vec.end());
  auto deduction = vec.end() - erase_begin_it;
  std::cout << "deduction is : " << deduction << "\n";
  vec.erase(erase_begin_it, vec.end());
}

void Biggies(std::vector<std::string> &words,
             std::vector<std::string>::size_type sz) {
  ElimDups(words);
  auto eit = std::stable_partition(words.begin(), words.end(),
                                   [sz] (const std::string &str) {
                                     return str.size() >= sz; });
  auto deduction = words.end() - eit;
  std::cout << "deduction is : " << deduction << "\n";
  words.erase(eit, words.end());
  std::for_each(words.cbegin(), words.cend(),
                [] (const std::string &str) {
                  std::cout << str << " "; });
  std::cout << "\n";
}
```

# 10.20
> 标准库定义了一个名为 count_if 的算法。
> 类似 find_if，此函数接受一对迭代器，表示一个输入范围，还接受一个谓词，会对输入范围中每个元素执行。
> count_if返回一个计数值，表示谓词有多少次为真。使用count_if重写我们程序中统计有多少单词长度超过6的部分。
```c++
int main() {
  using namespace std;
  vector<string> vec{"2134", "2", "", "324324234", "234123413241"};
  std::cout << count_if(vec.begin(), vec.end(),
                        [](const std::string &str) {
                          return str.size() > 3; });
  return 0;
}
```

# 10.22
> 重写统计长度小于等于6的单词数量的程序，使用函数代替lambda。
```c++
bool FilterString(const std::string &str , std::string::size_type sz) {
  return str.size() >= sz;
}

int main() {
  using namespace std;
  using namespace std::placeholders;

  int sz = 6;
  vector<string> vec{"2134", "2", "", "324324234", "234123413241"};

  auto callable = bind(FilterString, _1, sz);
  cout << count_if(vec.begin(), vec.end(), callable) << "\n";

  return 0;
}
}
```

# 10.23
> bind 接受几个参数？

bind 接受 n + 1个参数, n 为 func_name 参数

# 10.24
> 给定一个string，使用 bind 和 check_size 在一个 int 的vector 中查找第一个大于string长度的值。
```c++
bool FilterInteger(const int num, std::string::size_type sz) {
  return num > sz;
}

std::pair<bool, int> FindTargetInteger(const std::string &str, std::vector<int> &vec) {
  using namespace std::placeholders;
  auto callable = bind(FilterInteger, _1, str.size());
  auto it = std::find_if(vec.begin(), vec.end(), callable);
  if (it != vec.end()) {
    return {true, *it};
  } else {
    return {false, -1};
  }
}

int main() {
  using namespace std;
  using namespace std::placeholders;

  vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8};
  auto result = FindTargetInteger("123", vec);
  if (result.first) {
    std::cout << result.second << "\n";
  } else {
    std::cout << "Can't find it!" << "\n";
  }

  return 0;
}
```

# 10.27
> 除了 unique 之外，标准库还定义了名为 unique_copy 的函数，它接受第三个迭代器，表示拷贝不重复元素的目的位置。
> 编写一个程序，使用 unique_copy 将一个vector中不重复的元素拷贝到一个初始化为空的list中。
```c++
int main() {
  vector<string> vec{"2134", "2134", "2", "", "324324234", "234123413241"};
  list<string> lst;
  sort(vec.begin(), vec.end());
  unique_copy(vec.begin(), vec.end(), back_inserter(lst));
  for_each(lst.begin(), lst.end(), [](const string &s) { cout << s << " "; });
  return 0;
}
```

# 10.29
> 编写程序，使用流迭代器读取一个文本文件，存入一个vector中的string里。
```c++
int main(){
  system("chcp.com 65001");
  ifstream iss("../ch10_data/data_10_29");
  if (iss) {
    vector<string> vec;
    istream_iterator<string> is_end;
    istream_iterator<string> is_it(iss);
    while (is_it != is_end ) {
      vec.push_back(*is_it++);
    }
    for (const auto &item : vec) {
      cout << item << " ";
    }
  } else {
    cout << "Open fstream fail!" << "\n";
  }
  return 0;
}
```

# 10.30
> 使用流迭代器、sort 和 copy 从标准输入读取一个整数序列，将其排序，并将结果写到标准输出。
```c++
int main(){
  vector<int> vec;
  istream_iterator<int> is_end;
  istream_iterator<int> is_it(cin);
  while (is_it != is_end ) {
    vec.push_back(*is_it++);
  }
  sort(vec.begin(), vec.end());
  ostream_iterator<int> os_it(cout, "|");
  for (const auto &item : vec) {
    *os_it++ = item;
  }
  return 0;
}
```

# 10.31
> 修改前一题的程序，使其只打印不重复的元素。你的程序应该使用 unique_copy。
```c++
int main(){
  vector<int> vec;
  istream_iterator<int> is_end;
  istream_iterator<int> is_it(cin);
  while (is_it != is_end ) {
    vec.push_back(*is_it++);
  }
  sort(vec.begin(), vec.end());
  ostream_iterator<int> os_it(cout, "|");
  unique_copy(vec.begin(), vec.end(), os_it);
  return 0;
}
}
```

# 10.34
>使用 reverse_iterator 逆序打印一个vector。
```c++
int main() {
  list<int> lst{1, 2, 3, 4, 0, 5, 6, 7, 8, 9, 10};;
  for (auto it = lst.crbegin(); it != lst.crend(); ++it) {
    std::cout << *it << " ";
  }
  return 0;
}
```

# 10.35
> 使用普通迭代器逆序打印一个vector。
```c++
int main() {
  list<int> lst{1, 2, 3, 4, 0, 5, 6, 7, 8, 9, 10};;
  auto it = lst.cend();
  while (it != lst.cbegin()) {
    std::cout << *--it << " ";
  }
  return 0;
}
```

# 10.36
> 使用 find 在一个 int 的list 中查找最后一个值为0的元素。
```c++
int main() {
  list<int> lst{1, 2, 3, 4, 0, 5, 6, 7, 8, 9, 10};;
  auto it = std::find(lst.crbegin(), lst.crend(), 0);
  if (it != lst.crend()) {
    std::cout << *it;
  }
  return 0;
}
```

# 10.41
> 仅根据算法和参数的名字，描述下面每个标准库算法执行什么操作：
```c++
replace(beg, end, old_val, new_val);             // 将 [beg, end) old_val 替换为 new_val
replace_if(beg, end, pred, new_val);             // 将 [beg, end) 范围 满足 pred 条件的 old_val 替换为 new_val
replace_copy(beg, end, dest, old_val, new_val);  // 将 [beg, end) old_val 替换为 new_val并复制到 dest 位置
replace_copy_if(beg, end, dest, pred, new_val);  // 将 [beg, end) 范围 满足 pred 条件的 old_val 替换为 new_val并替换到 dest 位置
```