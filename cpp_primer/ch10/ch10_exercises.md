# 10.04 泛型算法类型推导
> 假定 v 是一个vector<double>，那么调用 accumulate(v.cbegin(),v.cend(),0) 有何错误（如果存在的话）？

参数 0 被模板函数 推测为 int 类型, 会发生精度损失

# 10.21 lambda捕获
> 编写一个 lambda，捕获一个局部 int 变量，并递减变量值，直至它变为0。
> 一旦变量变为0，再调用lambda应该不再递减变量。lambda应该返回一个bool值，指出捕获的变量是否为0。
```c++
int main() {
  using namespace std;
  int a = 10;
  auto f_ = [&a] () -> bool {
    if (a-- != 0) {
      std::cout << a + 1 << "\n";
      return true;
    } else {
      return false;
    }
  };
  while(f_()) ;
  return 0;
}
```

# 10.25 bind使用
> 在10.3.2节的练习中，编写了一个使用partition 的biggies版本。使用 check_size 和 bind 重写此函数。
```c++
using namespace std::placeholders;
using namespace std;

bool CheckSize(const string &s, string::size_type sz) {
  return s.size() >= sz;
}

void Biggies(vector<string> &vec, vector<string>::size_type sz) {
  // 去重
  sort(vec.begin(), vec.end());
  auto iter = unique(vec.begin(), vec.end());
  vec.erase(iter, vec.end());

  // 筛选 >= size 的元素出来
  auto it = stable_partition(vec.begin(), vec.end(), bind(CheckSize, _1, sz));
  vec.erase(it, vec.end());
}

int main() {
  vector<string> vec{"2134", "2134", "2", "", "324324234", "234123413241"};
  Biggies(vec, 5);
  for_each(vec.begin(), vec.end(), [](const string &s) { cout << s << " "; });
  return 0;
}
```

# 10.26 插入迭代器用法
> 解释三种插入迭代器的不同之处。
```c++
auto it1 = back_insert(vec);          // vec 支持 push_back, 在 vec 后端插入
auto it2 = front_insert(vec);         // vec 支持 push_front, 在 vec 前端插入
auto it3 = inserter(vec, it_begin);   // vec 支持 insert, 在 vec 的 it_begin 之前插入
```

# 10.28 插入迭代器用法
> 一个vector 中保存 1 到 9，将其拷贝到三个其他容器中。分别使用inserter、back_inserter 和 front_inserter 将元素添加到三个容器中。
> 对每种 inserter，估计输出序列是怎样的，运行程序验证你的估计是否正确。
```c++
int main(){
  vector<int> vec{1,2,3,4,5,6,7,8,9};
  deque<int> vec1;
  vector<int> vec2, vec3;
  copy(vec.begin(), vec.end(), front_inserter(vec1));
  copy(vec.begin(), vec.end(), back_inserter(vec2));
  copy(vec.begin(), vec.end(), inserter(vec3, vec3.begin()));

  cout<<" origin vec : ";
  for_each(vec.begin(), vec.end(), [](const int &e){ cout<<e<<" "; });
  cout<<endl;

  cout<<" deque front_inserter : ";
  for_each(vec1.begin(), vec1.end(), [](const int &e){ cout<<e<<" "; });
  cout<<endl;  // 9 8 7 6 5 4 3 2 1

  cout<<" vector back_inserter : ";
  for_each(vec2.begin(), vec2.end(), [](const int &e){ cout<<e<<" "; });
  cout<<endl;  // 1 2 3 4 5 6 7 8 9

  cout<<" vector inserter vec.begin() : ";
  for_each(vec3.begin(), vec3.end(), [](const int &e){ cout<<e<<" "; });
  // 1 2 3 4 5 6 7 8 9
  return 0;
}
```

# 10.32 流迭代器用法
> 重写1.6节中的书店程序，使用一个vector保存交易记录，使用不同算法完成处理。
> 使用 sort 和10.3.1节中的 compareIsbn 函数来排序交易记录，然后使用 find 和 accumulate 求和。

见 Sales_item_test.cc

# 10.33 流迭代器用法
> 编写程序，接受三个参数：一个输入文件和两个输出文件的文件名。输入文件保存的应该是整数。使用 istream_iterator 读取输入文件。
> 使用 ostream_iterator 将奇数写入第一个输入文件，每个值后面都跟一个空格。将偶数写入第二个输出文件，每个值都独占一行。
```c++
int main() {
  std::ifstream ifs("../ch10_data/data_10_33");
  std::ofstream ofs1("Output1");
  std::ofstream ofs2("Output2");
  if (!ofs1 || !ofs2 ) {
    std::cout << "Open file failed!" << "\n";
    return 1;
  }

  std::istream_iterator<int> is(ifs);
  std::istream_iterator<int> is_end;
  std::ostream_iterator<int> os1(ofs1, "\n");
  std::ostream_iterator<int> os2(ofs2, "\n");

  while (is != is_end) {
    if (*is % 2) {
      *os1++ = *is++;
    } else {
      *os2++ = *is++;
    }
  }
  return 0;
}
```

# 10.37 反向迭代器用法
> 给定一个包含10 个元素的vector，将位置3到7之间的元素按逆序拷贝到一个list中。
```c++
int main() {
  vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> lst;
  auto itb = vec.crbegin();
  for (int i = 0; i < 3; ++i) ++itb;
  auto ite = itb;
  for (int i = 0; i < 5; ++i) ++ite;
  copy(itb, ite, back_inserter(lst));
  for (const auto &e: lst)
    cout << e << " ";
  return 0;
}
```

# 10.38 迭代器类别
> 列出5个迭代器类别，以及每类迭代器所支持的操作。
```c++
输入迭代器: 只读,单遍扫描,只能递增, 支持 ++,var=\*it,var=it->m,==,!= 
前向迭代器: 读写,多遍扫描,只能递增, 支持 input&output                
双向迭代器: 读写,多遍扫描,能递增减, 支持 input&output,--             
随机迭代器: 读写,多遍扫描,能递增减, 支持 <,<=,>,>=,[],+-            
输出迭代器: 只写,单遍扫描,智能递增, 支持 ++,\*it=var               
```

# 10.39 迭代器类别
> list 上的迭代器属于哪类？vector呢？
```c++
list 的迭代器 属于 双向迭代器
vector 的迭代器 属于 双向迭代器
```

# 10.40 迭代器类别要求
> 你认为 copy 要求哪类迭代器？reverse 和 unique 呢？
```c++
copy(input_it1, input_it2, output_it);
unique(forward_it1, forward_it2);  // 有序遍历去重
reverse(bi_it1, bi_it2);
```

# 10.42 特殊容器的算法
> 使用 list 代替 vector 重新实现10.2.3节中的去除重复单词的程序。
```c++
void elimDups(list<string> &words) {
  words.sort();
  words.unique();
}
```