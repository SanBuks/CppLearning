# 9.06 插入与删除对迭代器指针引用的影响
> 下面的程序有何错误？你应该如何修改它？
```c++
list<int> lst1;
list<int>::iterator iter1 = lst1.begin(),
					iter2 = lst1.end();
while (iter1 < iter2) /* ... */
// 错误在于:
// 1. 保留尾后指针, 最容易收到插删操作影响, 虽然对于列表类型容器没有影响
// 2. list 的迭代器是双向迭代器, 没有比较操作

// 修改后为:
auto cit = lst.cbegin();
while (cit != lst.cend()) {
  std::cout << *cit++;
}
```

# 9.13 迭代器范围拷贝的特点
> 如何从一个list\<int>初始化一个vector\<double>？从一个vector\<int>又该如何创建？编写代码验证你的答案。
```c++
int main(){ 
    list<int> list1{1,2,3,4};
    // 能够转换即可
    vector<double> vector1(list1.cbegin(),list1.cend());
    vector<int> vector2(list1.cbegin(),list1.cend());

    for(const auto &e : vector1) cout<<e<<" ";
    cout<<"\n";
    for(const auto &e : vector2) cout<<e<<" ";
    cout<<"\n";
    return 0;
}
```

# 9.22 插入与删除对迭代器指针引用的影响
> 假定iv是一个int的vector，下面的程序存在什么错误？你将如何修改？
```c++
// 第一个错误, 保留暂时获取的迭代器作为哨兵
vector<int>::iterator iter = iv.begin(),
					  mid = iv.begin() + iv.size() / 2;
while (iter != mid)
	if (*iter == some_val)
		iv.insert(iter, 2 * some_val);
// 第二个错误, it 没有更新, mid 也没有更新 
// 在 vector 中插入元素后会发生两种情况
// 1. 重新分配 : 所有位置的所有访问方式都失效
// 2. 未重新分配 : 插入位置及之后所有位置的所有访问方式都失效

// 更新后
int main(){ 
  std::vector<int> iv{1, 2, 3, 4, 5};
  auto print = [](const int &item) { std::cout << item << " "; };
  refresh_vec(iv);

  auto iter = iv.begin();
  auto mid = iv.begin() + iv.size() / 2;
  while (iter != mid) {
    if (*iter % 2) {
      // 记录中间点位置
      auto size = mid - iv.begin();
      // 插到前面位置
      iter = iv.insert(iter, 2 * *iter);
      // 刷新哨兵和迭代器
      iter += 2;
      mid = iv.begin() + size + 1;
    } else {
      ++iter;
    }
  }
  std::for_each(iv.cbegin(), iv.cend(), print);
  return EXIT_SUCCESS;
}
```

# 9.25 插入与删除对迭代器指针引用的影响
> 对于第312页中删除一个范围内的元素的程序，如果 elem1 与 elem2 相等会发生什么？如果 elem2 是尾后迭代器，或者 elem1 和 elem2 皆为尾后迭代器，又会发生什么？
```c++
std::vector<int> iv{1, 2, 3, 4};
auto elem1 = iv.begin() + 1;
auto elem2 = iv.end() - 2;
std::cout << *elem1 << " " << *elem2 << "\n";
elem1 = iv.erase(elem1, elem2);
std::cout << *elem1 << "\n";
std::cout << *elem2 << "\n";  // 注意! elem2 已经无效化

// 1. 如果 elem1 == elem2 则不会发生删除, 不会无效化, 返回 elem2
// 2. 如果 elem2 == iv.end() 则把 elem1 所指元素到末尾全部删除, 返回尾后迭代器
// 3. 如果 elem1 == elem2 == iv.end() 则同 1
// 4. 可以用 erase(cit, cit); 将 const_iterator -> iterator
```

# 9.43 字符串操作
> 编写一个函数，接受三个string参数是s、oldVal 和newVal。使用迭代器及insert和erase函数将s中所有oldVal替换为newVal。测试你的程序，用它替换通用的简写形式，如，将"tho"替换为"though",将"thru"替换为"through"。

# 9.44 字符串操作
> 重写上一题的函数，这次使用一个下标和replace。
```c++
void replace1(std::string &s, 
             const std::string oldVal, 
             const std::string newVal) {
  if (oldVal == newVal) {
    return ;
  }
  std::string::size_type pos = 0; 
  while (std::string::npos != (pos = s.find(oldVal))) {
    s.erase(pos, oldVal.size());
    s.insert(pos, newVal);
  }
}

void replace2(std::string &s, 
             const std::string oldVal, 
             const std::string newVal) {
  if (oldVal == newVal) {
    return ;
  }
  std::string::size_type pos = 0; 
  while (std::string::npos != (pos = s.find(oldVal))) {
    s.replace(pos, oldVal.size(), newVal);
  }
}
```

# 9.47 字符串操作
> 编写程序，首先查找string"ab2c3d7R4E6"中每个数字字符，然后查找其中每个字母字符。编写两个版本的程序，第一个要使用find_first_of，第二个要使用find_first_not_of。
```c++
int main(){ 
  std::string example = "ab2c3d7R4E6";
  std::string number = "1234567890";
  std::string alpha = "abcdefghijklmnopqrstuvwxyz";

  for (std::string::size_type pos = 0;
       (pos = example.find_first_of(number, pos)) != std::string::npos; ++pos) {
    std::cout << example[pos] << "\n";
  }
  std::cout << "------------------\n";
  for (std::string::size_type pos = 0;
      (pos = example.find_first_not_of(number, pos)) != std::string::npos; ) {
    std::cout << example[pos++] << "\n";
  }
  return EXIT_SUCCESS;
}
```

# 9.51 字符串操作与数值转化
> 设计一个类，它有三个unsigned成员，分别表示年、月和日。为其编写构造函数，接受一个表示日期的string参数。你的构造函数应该能处理不同的数据格式，如January 1,1900、1/1/1990、Jan 1 1900 等。
```c++
// 主要参考 ch09_code/date.cc date.h
// 其中简单的词法分析函数
void Date::Parse(const std::string &date_str) {
  std::string month_str;
  std::string day_str;
  std::string year_str;

  // parse '1/1/1990' 
  if (date_str.find("/") != std::string::npos) {  
    auto first_pos_of_slash = date_str.find("/");
    auto second_pos_of_slash = date_str.find("/", first_pos_of_slash + 1);
    if (std::string::npos != first_pos_of_slash && 
        std::string::npos != second_pos_of_slash) {
      month_str = date_str.substr(0, first_pos_of_slash - 0);
      day_str   = date_str.substr(first_pos_of_slash + 1, 
                                  second_pos_of_slash - first_pos_of_slash - 1);
      year_str  = date_str.substr(second_pos_of_slash + 1, 
                                  date_str.size() - second_pos_of_slash - 1);
      try {
        month_ = std::stoi(month_str);
        day_ = std::stoi(day_str);
        year_ = std::stoi(year_str);
      } catch (const std::exception &ex) {
        throw std::runtime_error("DATE::Parse(std::string)"
                                 ":: Can't pasrse '1/1/1990' type!");
      }
    } else {
      throw std::runtime_error("DATE::Parse(std::string)"
                               ":: Can't pasrse '1/1/1990' type!");
    }
  // parse 'Jan 1 1900', 'January 1, 1900'
  } else {  
    std::stringstream ss(date_str); 
    ss >> month_str;
    auto month_iterator = MonthValue.find(month_str);
    if ( month_iterator != MonthValue.end()) {
      month_ = month_iterator->second;
      ss >> day_str;
      ss >> year_str;
      try {
        day_ = std::stoi(day_str);
        year_ = std::stoi(year_str);
      } catch (std::exception &ex) {
        throw std::runtime_error("DATE::Parse(std::string)"
                                "Can't parse 'Jan 1 1900' type!");
      }
    } else {
      throw std::runtime_error("DATE::Parse(std::string)"
                               "Can't parse 'Jan 1 1900' type!");
    }
  }
}
```

# 9.52 用栈求中缀与后缀表达式
> 使用stack处理括号化的表达式。当你看到一个左括号，将其记录下来。当你在一个左括号之后看到一个右括号，从stack中pop对象，直至遇到左括号，将左括号也一起弹出栈。然后将一个值（括号内的运算结果）push到栈中，表示一个括号化的（子）表达式已经处理完毕，被其运算结果所替代。
```c++
// 详见 ch09_code/simple_expression.cc
SimpleExpression::PosType SimpleExpression::ReadOperation(
    const std::string &expression_str, PosType start_pos,
    std::stack<std::string, std::vector<std::string>> &operations,
    std::stack<double, std::vector<double>> &numbers) {
  PosType pos = start_pos;
  // 获取当前操作符
  std::string current_operation;
  std::string valid_operation;
  while (!std::isdigit(expression_str[pos]) && 
         !std::isblank(expression_str[pos])) {
    current_operation.append(1, expression_str[pos++]);
    if (PriorityBetween.find(current_operation) != PriorityBetween.end()) {
      valid_operation = current_operation;
    }
  }
  pos -= current_operation.size() - valid_operation.size();
  current_operation = valid_operation;
  if (PriorityBetween.find(current_operation) != PriorityBetween.end()) {
    std::string &stack_operation = operations.top();
    if (PriorityBetween[stack_operation][current_operation] == "<") {
      operations.push(current_operation);
    } else if (PriorityBetween[stack_operation][current_operation] == "=") {
      operations.pop();
    } else if (PriorityBetween[stack_operation][current_operation] == ">") {
      if (stack_operation == "!") {
        double number = numbers.top(); numbers.pop();
        double result = Calc(stack_operation, number);
        numbers.push(result);
      } else {
        double number2 = numbers.top(); numbers.pop();
        double number1 = numbers.top(); numbers.pop();
        double result = Calc(number1, stack_operation, number2);
        numbers.push(result);
      }
        operations.pop();
        --pos;
    } else {
      auto error_msg = cpp_primer::string_format(
        "[ReadOperation] : Error Operation!\nAt [%d] Position\n", pos);
      throw std::runtime_error(error_msg);
    }
  } else {
    auto error_msg = cpp_primer::string_format(
      "[ReadOperation] : Error Operation!\nAt [%d] Position\n", pos);
    throw std::runtime_error(error_msg);
  }
  return pos;
}	
```