# 9.01
> 对于下面的程序任务，vector、deque和list哪种容器最为适合？解释你的选择的理由。如果没有哪一种容器优于其他容器，也请解释理由。
```c++
(a) 读取固定数量的单词，将它们按字典序插入到容器中。 list
(b) 读取未知数量的单词，总是将单词插入到末尾。删除操作在头部进行。 deque
(c) 从一个文件读取未知数量的整数。将这些数排序，然后将它们打印到标准输出。 vector
```

# 9.02
> 定义一个list对象，其元素类型是int的deque。
```c++
std::list<std::deque<int>> lst;
```

# 9.03
> 构成迭代器范围的迭代器有何限制？

- 左闭右开区间 : [a, b)
- assert(iterb - itera >= 0)

# 9.04
> 编写函数，接受一对指向vector\<int>的迭代器和一个int值。在两个迭代器指定的范围中查找给定的值，返回一个布尔值来指出是否找到。
```c++
bool is_finded(std::vector<int>::const_iterator beg,
               std::vector<int>::const_iterator end, 
               const int &val) {
  if (beg > end) {
    return false;
  }
  while (beg != end) {
    if (*beg++ == val) {
      return true;
    }
  }
  return false;
}
```

# 9.05
> 重写上一题的函数，返回一个迭代器指向找到的元素。注意，程序必须处理未找到给定值的情况。
```c++
std::vector<int>::const_iterator is_finded(std::vector<int>::const_iterator beg,
                                           std::vector<int>::const_iterator end, 
                                           const int &val) {
  if (beg > end) {
    return end;
  }
  while (beg != end) {
    if (*beg == val) {
      return beg;
    }
    ++beg;
  }
  return end;
}

int main() {
  std::vector<int> vec{1, 2, 3, 4, 5, 6};
  // 通过 chrono 类 获取现在的时间计数
  unsigned long seeds = std::chrono::system_clock::
                          now().time_since_epoch().count();
  // 随机化引擎
  std::default_random_engine e(seeds);
  // 随机化
  std::shuffle(vec.begin(), vec.end(), e);
  auto print = [](const int &item) { std::cout << item << " "; };		

  std::for_each(vec.cbegin(), vec.cend(), print);
  std::cout << "\n";

  auto target = is_finded(vec.cbegin(), vec.cend(), 3);
  *vec.erase(target, target) = 999;
  std::for_each(vec.cbegin(), vec.cend(), print);
  std::cout << "\n";

  return EXIT_SUCCESS;
}
```

# 9.07
> 为了索引int的vector中的元素，应该使用什么类型？
```c++
std::vector<int>::size_type i = 0;
```

# 9.08
> 为了读取string的list中的元素，应该使用什么类型？如果写入list，又应该使用什么类型？
```c++
std::vector<std::string>::const_iterator;  // 读
std::vector<std::string>::iterator;  // 写
```

# 9.09
> begin和cbegin两个函数有什么不同？

- begin 普通迭代器
- cbegin 常量迭代器

# 9.10
> 下面4个对象分别是什么类型？
```c++
vector<int> v1;  // vector
const vector<int> v2;  // const vector
auto it1 = v1.begin(), it2 = v2.begin();  
// vector<int>::iterator, vector<int>::const_iterator (const 成员函数重载)
auto it3 = v1.cbegin(), it4 = v2.cbegin();
// vector<int>::const_iterator, vector<int>::const_iterator
```

# 9.11
> 对6种创建和初始化vector对象的方法，每一种都给出一个实例。解释每个vector包含什么值。
```c++
std::vector<int> vec_default;  // 默认初始化, 空
std::vector<int> vec_num(3);  // 值初始化, 0, 注意跟 array 有区别
std::vector<int> vec_num_copy(3, {3});  // 给定值初始化, [3, 3, 3]
std::vector<int> vec_initializer_list{1, 2, 3, 4, 5};  // 列表初始化
std::vector<int> vec_copy(vec_default);  // 拷贝初始化
std::vector<int> vec_interator_copy(vec_default.cbegin(), vec_default.cend());  // 范围拷贝初始化
```

# 9.12
> 对于接受一个容器创建其拷贝的构造函数,和接受两个迭代器创建拷贝的构造函数,解释它们的不同。

- 接受容器进行拷贝构造需要容器类型相同, 元素类型相同
- 接受迭代器进行拷贝构造容器类型可以不同, 元素类型可以转换即可, 后者有更强的普适性

# 9.14
> 将一个list中的char * 指针元素赋值给一个vector中的string
```c++
int main(){ 
  const char *a="1230";
  const char *b="1222";
  std::list<const char *> vec2{a,b};        
  std::vector<std::string> vec1;
  // 存在 const char * -> string 的构造函数
  vec1.assign(vec2.cbegin(),vec2.cend());
  for (const auto &e : vec1) {
    std::cout << e << "\n";
  }
  return EXIT_SUCCESS;
}
```

# 9.15
> 编写程序，判定两个vector\<int>是否相等。
```c++
std::vector<int> s1{1, 2, 3, 4, 5};
std::vector<int> s2{1, 2, 3, 4, 5};
assert(s1 == s2);
```

# 9.16 
> 重写上一题的程序，比较一个list中的元素和一个vector中的元素。
```c++
bool compare_between_vec_list(const std::vector<int> &vec, 
                              const std::list<int> &list) {
  if (vec.size() != list.size()) {
    return false;
  }
  auto it1 = vec.cbegin(); 
  auto it2 = list.cbegin();
  for (; it1 != vec.cend() && it2 != list.cend(); ++it1, ++it2) {
    if (*it1 != *it2) {
      return false;
    }
  }
  return true;
}

int main(){ 
  std::vector<int> s1{1, 2, 3, 4, 5};
  std::list<int> s2{1, 2, 3, 4, 5};
  std::cout << compare_between_vec_list(s1, s2);
  return EXIT_SUCCESS;
}
```

# 9.17
> 假定c1和c2是两个容器，下面的比较操作有何限制？
```c++
if (c1 < c2)
// c1 和 c2 必须是相同类型, 相同类型的元素的容器
// 元素类型要支持关系运算符
```

# 9.18
> 编写程序，从标准输入读取string序列，存入一个deque中。编写一个循环，用迭代器打印deque中的元素。
```c++
int main(){ 
  std::string s;
  s.reserve(100);
  std::cin >> s;
  std::deque<char> deq(s.begin(), s.end());
  for (const auto &item : deq) {
    std::cout << item << " ";
  }
  return EXIT_SUCCESS;
}
```

# 9.19
> 重写上一题的程序，用list替代deque。列出程序要做出哪些改变。
```c++
std::deque<char> deq -> std::list<char> lst
```

# 9.20
> 编写程序，从一个list\<int>拷贝元素到两个deque中。值为偶数的所有元素都拷贝到一个deque中，而奇数值元素都拷贝到另一个deque中。
```c++
int main(){ 
  std::list<int> lst{1, 2, 3, 4, 5};
  std::deque<int> de1;
  std::deque<int> de2;
  auto divide = [&de1, &de2](const int &item) {
    if (item % 2) {
      de1.push_back(item);
    } else {
      de2.push_back(item);
    }
  };
  std::for_each(lst.begin(), lst.end(), divide);
  for (const int &item : de1) {
    std::cout << item << " ";
  }
  std::cout << "\n";
  for (const int &item : de2) {
    std::cout << item << " ";
  }
  return EXIT_SUCCESS;
}
```

# 9.21 
> 如果我们将第308页中使用insert返回值将元素添加到list中的循环程序改写为将元素插入到vector中，分析循环将如何工作。

- 相当于插入位置的首插法

# 9.23
> 在本节第一个程序中，若c.size() 为1，则val、val2、val3和val4的值会是什么？
```c++
// 同一个值
auto val = *c.begin();  // value
auto val2 = c.front();  // value
auto val3 = *(--c.end());  // value
auto val4 = c.back();  // value
```

# 9.24
> 编写程序，分别使用at、下标运算符、front 和 begin 提取一个vector中的第一个元素。在一个空vector上测试你的程序。
```c++
std::vector<int> iv{};
auto val1 = iv.at(0);
auto val2 = iv[0];
auto val3 = *iv.begin();
auto val4 = *--iv.end();
// terminate called after throwing an instance of 'std::out_of_range'
//  what():  vector::_M_range_check: __n (which is 0) >= this->size() (which is 0)
```

# 9.26
> 使用下面代码定义的ia，将ia拷贝到一个vector和一个list中。是用单迭代器版本的erase从list中删除奇数元素，从vector中删除偶数元素。
```c++
int main() {
  int ia[] = {0, 1, 1, 2, 3, 5, 8, 12, 21, 55, 89}; 
  std::list<int> eve(std::begin(ia), std::end(ia)); 
  std::vector<int> odd(std::begin(ia), std::end(ia));
  for (auto it = eve.begin(); it != eve.end(); ++it) {
    if(!(*it % 2)){
        it = eve.erase(it);
        --it;
    }
  }

  for (auto it = odd.begin(); it != odd.end(); ++it) {
    if(*it % 2){
        it = odd.erase(it);
        --it;
    }    
  }

  for (const auto &it : eve) std::cout << it << " ";
  std::cout << std::endl;
  for (const auto &it : odd) std::cout << it << " ";

  return EXIT_SUCCESS;
}
```

# 9.27
> 编写程序，查找并删除forward_list\<int>中的奇数元素。
```c++
int main(){ 
  int ia[] = {0, 1, 1, 2, 3, 5, 8, 12, 21, 55, 89}; 
  std::forward_list<int> flist(std::begin(ia), std::end(ia));
  if (!flist.empty()) {
    auto pit = flist.before_begin();
    auto it = flist.begin();  // 注意 it + 1 是非法的
    while (it != flist.end()) {
      if (*it % 2) {
        it = flist.erase_after(pit);
      } else {
        ++it;
        ++pit;
      }
    }
  }
  std::for_each(flist.begin(), flist.end(), print);
  return EXIT_SUCCESS;
}
```


# 9.28
> 编写函数，接受一个`forward_list<string>`和两个`string`共三个参数。函数应在链表中查找第一个`string`，并将第二个`string`插入到紧接着第一个`string`之后的位置。若第一个`string`未在链表中，则将第二个`string`插入到链表末尾。
```c++
void func(std::forward_list<std::string> &fl, 
          const std::string &s1, const std::string &s2) {
  auto pit = fl.before_begin();
  auto it = fl.begin();
  bool is_inserted = false;
  while (it != fl.end()) {
    if (*it == s1) {
      it = fl.insert_after(it, s2);
      pit = it;
      ++it;
      is_inserted = true;
    } else {
      ++it;
      ++pit;
    }
  }
  if (!is_inserted) {
    fl.insert_after(pit, s2);
  }
}
```

# 9.29
> 假定vec包含25个元素，那么vec.resize(100)会做什么？如果接下来调用vec.resize(10)会做什么？

resize(100) , 可默认插入, 按照给定的分配器原位默认构造, 值初始化
resize(10), 减小容器为开始 10 个元素

# 9.30
> 接受单个参数的resize版本对元素类型有什么限制（如果有的话）？

元素类型必须有默认构造函数 

# 9.31
> 第316页中删除偶数值元素并复制奇数值元素的程序不能用于list或forward_list。为什么？修改程序，使之也能用于这些类型。
```c++
// list 和 forward_list 迭代器不支持 += 操作
int main() {
// forward_list
  std::forward_list<int> flist{1, 2, 3, 4, 5, 6};
  auto it = flist.begin();
  auto pit = flist.before_begin();
  while (it != flist.end()) {
    if (*it % 2) {
      it = flist.insert_after(it, *it);
      pit = it++;
    } else {
      it = flist.erase_after(pit);
    }
  }
  std::for_each(flist.begin(), flist.end(), print_int);
  return EXIT_SUCCESS;
}
// list
int main(){ 
  std::list<int> list{1, 2, 3, 4, 5, 6};
  auto it = list.begin();
  while (it != list.end()) {
    if (*it % 2) {
      it = list.insert(it, *it);
      it++;
      it++;
    } else {
      it = list.erase(it);
    }
  }
  std::for_each(list.begin(), list.end(), print_int);
  return EXIT_SUCCESS;
}
```

# 9.32
> 在第316页的程序中，向下面语句这样调用insert是否合法？如果不合法，为什么？
```c++
iter = vi.insert(iter, *iter++);  // 不合法, 求值顺序未定义
```

# 9.33
> 在本节最后一个例子中，如果不将insert的结果赋予begin，将会发生什么？编写程序，去掉此赋值语句，验证你的答案。
```c++
void test() {
// 在 begin 之前插入元素, 会导致 begin 及之后的迭代器都失效, 产生未定义操作
  std::vector<int> vec{1, 2, 3, 4, 5, 6};
  auto it = vec.begin();
  while (it != vec.end()) {
    if (*it % 2) {
      it++;
      vec.insert(it, *it);
      it++;
    } else {
      it = vec.erase(it);
    }
  }
  std::for_each(vec.begin(), vec.end(), print_int);
  // 1 2 3 4 5 6 
}
```

# 9.34
> 假定vi是一个保存int的容器，其中有偶数值也有奇数值，分析下面循环的行为，然后编写程序验证你的分析是否正确。
```c++
iter = vi.begin();
while (iter != vi.end())
	if (*iter % 2)
		iter = vi.insert(iter, *iter);  // it 指向插入的元素
	++iter;  // it 指向原来的元素
// 产生死循环
```

# 9.35
> 解释一个vector的capacity和size有何区别。

- capacity 标识保留的空间大小, 存在未被分配的空间
- size 标识当前元素的大小

# 9.36
> 一个容器的capacity可能小于它的size吗？

- 不可能

# 9.37
> 为什么list或array没有capacity成员函数？

- list 是链表结构, 插入时间快, 不需要倍增分配预留空间
- array 是不可变容器, 不存在扩容情况

# 9.38
> 编写程序，探究在你的标准实现中，vector是如何增长的。
```c++
// 倍增扩容
int main(){ 
  std::vector<int> vec;
  std::ofstream ofs("test.txt", std::fstream::ate | std::fstream::trunc);
  if (ofs) {
    for (int i = 0; i < 256; ++i) {
      vec.push_back(1);
      ofs << "capacity : " << vec.capacity() << " "
          << "size : " << vec.size() << "\n";
    }
  }
  return EXIT_SUCCESS;
}
```


# 9.39
> 解释下面程序片段做了什么：
```c++
// 读入字符串到容器中, 然后值初始化扩增当前元素个数一半的空间
vector<string> svec;
svec.reserve(1024);
string word;
while (cin >> word)
	svec.push_back(word);
svec.resize(svec.size() + svec.size() / 2);
```

# 9.40
> 如果上一题的程序读入了256个词，在resize之后容器的capacity可能是多少？如果读入了512个、1000个、或1048个呢？

在倍增扩容的策略下, capacity 为下 512, 1024, 2048, 2048

# 9.41
> 编写程序，从一个vector\<char>初始化一个string。
```c++
std::vector<char> vec{'a', 'b', 'c'};
std::string str(vec.begin(), vec.end());
std::cout << str;
```

# 9.42 
> 假定你希望每次读取一个字符存入一个string中，而且知道最少需要读取100个字符，应该如何提高程序的性能？
```c++
std::string s;
s.reserve(100);
for (int i = 0; i < 100; ++i) {
  s.push_back('s');
}
std::cout << s;
```

# 9.45
> 编写一个函数，接受一个表示名字的string参数和两个分别表示前缀（如"Mr."或"Mrs."）和后缀（如"Jr."或"III"）的字符串。使用迭代器及insert和append函数将前缀和后缀添加到给定的名字中，将生成的新string返回。

# 9.46
> 重写上一题的函数，这次使用位置和长度来管理string，并只使用insert。
```c++
void addPrefixSuffix1(const std::string &prefix, std::string &name, 
                      const std::string &suffix) {
  name.append(" ");
  name.insert(0, prefix);
  name.append(suffix);
}

void addPrefixSuffix2(const std::string &prefix, std::string &name, 
                      const std::string &suffix) {
  name.insert(name.size(), " ");
  name.insert(0, prefix);
  name.insert(name.size(), suffix);
}
```

# 9.48
> 假定name和numbers的定义如325页所示，numbers.find(name)返回什么？

std::string::nops

# 9.49
> 读入一个单词文件,输出最长的不含上出头部分和下出头部分的单词
```c++
int main(){
    string outline = "bdfghijklpqty";
    string word, maxword;
    fstream fs("./input");
    while (fs) {
        fs >> word;
        if (word.find_first_of(outline) == string::npos && 
            word.size() > maxword.size()) {
            maxword=word;
        }
    }   
    cout << maxword << " lenth is " << maxword.size() << endl;
    return 0;
}
```

# 9.50
> 编写程序处理一个vector\<string>，其元素都表示整型值。计算vector中所有元素之和。修改程序，使之计算表示浮点值的string之和。
```c++
int main(){ 
  std::vector<std::string> vec{"123.2", "23.9", "33.5", "dsf2"};
  double sum = 0.0;
  for (const auto& item : vec) {
    try {
      double val = std::stod(item);
      sum += val;
    } catch (std::exception &ex) {
      std::cout << item << " ";
      std::cout << ex.what() << "\n";
    }
  }
  std::cout << "\n" << sum;
  return EXIT_SUCCESS;
}
```