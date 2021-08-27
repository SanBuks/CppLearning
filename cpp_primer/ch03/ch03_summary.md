
# 1. using声明
- using 声明 : using namespace::name; 简化使用命名空间中的成员
- 一般不在头文件中使用using声明, 防止命名冲突

# 2. string

## 2.1 string 基本用法
```c++
std::string s1;  // 默认初始化
std::string s2("123");  // 拷贝初始化
std::string s3= "123";  // 赋值拷贝初始化
std::string s4(s1); // 同上
std::string s5 = s1;  // 同上
std::string s6(2, 'c');  // 个数 + 字符 初始化

std::cint >> s1;  // 读入 s1, 忽略空白符读入, 以空白符分隔
std::getline(std::cin, s1);  // 读入一行包括`\n`但是舍去后赋予s1内容, 返回is

std::cout << s2;  // 打印 s2

assert(!s3.empty() && s.size() > 1);  // 返回是否为空; 字符个数 (string 不包含 \0)
std::string::size_type size = s.size();  // 字符个数大小

assert(s4 != s5 || s4 < s5);  // 按字典序再按个数比较

s5[0] = 'x';  // 下标返回引用
s6 = s5 + s4;  // 忽略`\0`连接两个字符串, 返回新创的string对象
auto a="123"+"234;  // 非法, 不能将两个字面值常量直接相加
```


## 2.2 判断字符函数

![](https://raw.githubusercontent.com/SanBuks/Cpp_Learning/master/cpp_primer/image/ch03_cctype.png)

## 2.3 遍历字符与转换字符
```c++
// for-range 语句
for (auto &it : str)  // 遍历每个元素 除末尾 `\0`
	it = toupper(it);  // 转化为大写

// 通过string下标遍历
for (decltype(str.size()) index=0; index!=str.size(); ++index)
	str[index] = tolower(str[index]);  // 转化为小写
```

# 3. vector
## 3.1 vector 基本用法
```c++
std::vector<int> s1;  // 默认初始化
std::vector<int> s2(s1);  // 拷贝初始化
std::vector<int> s3 = {1, 2, 3};  // 列表赋值初始化
std::vector<int> s4({1, 2, 3});  // 列表拷贝初始化
std::vector<int> s5(2);  // 值初始化
std::vector<int> s6(2, 'c');  // 个数 + 元素初始化

std::vector<string> a{10};  // 列表初始化, 先按列表初始化 如果无法执行则值初始化

a.push_back("123");  // 在末尾插入元素
a.[0] = "321";  // 返回下标为0的引用
s1 != s2; // 按字典序和个数比较
s1 == s2; 
```

## 3.2 其他要点
- 容器的值初始化 : 会创建一个值初始化元素, 然后将该元素赋予容器中每个元素, 基本类型则默认为 0, 其他类型则默认初始化
- vector 是模板类, 根据类型进行实例化
- range-for语句或其他循环语句内不应该改变容器大小

# 4. iterator

| iterator用法 \<iterator> | 解释 |
| --- | --- |
| c.(c)begin(); <br/>c.(c)end(); | 获取首和尾后迭代器 |
| == != | 判断迭代器是否指向同一个位置  |
| ++it; <br/>--it; | 移动到下一个或上一个位置 |
| (\*it).func(); <br/>it->func(); | 解引用后调用成员函数 |
| it+(-)n; it+(-)=n; | 向后 (前) 移动n个位置 |
| 比较操作符 | 越前越小, 越后越大 (限于随机访问迭代器) |
|iter1-iter2 |两个之间的间距 是difference_type 类型带符号类型|

> 注意对容器修改可能会导致迭代器失效, 解非法迭代器行为未定义

```c++
// 二分查找, 返回 <= e 的最大位置的迭代器, 如果指向首前修正为第一个元素
template<typename T>
typename std::vector<T>::const_iterator find(const std::vector<T> &vec, const T &e) {
    auto lo = vec.begin();
    auto hi = vec.end();
    while(lo != hi){
        auto mid= lo + (hi - lo) / 2;
        if(e < *mid) hi = mid;  // [mid, end) > e
        else lo = mid + 1;  // [0, mid) <= e
    }
    --lo;
    if(vec.begin() > lo) return ++lo;
    return lo;
}
```

# 5. 数组
## 5.1 定义与初始化
- 定义数组时下标一定是一个常量表达式, 通常设定为一个 std::size_t 无符号类
- 数组元素一定是一个左值, 不存在引用的数组
- 无法被拷贝, 赋值但可用于for range语句
```c++
const char str[7]="123";  // 存在字符串常量到常量字符数组的转化, 注意大小一定容下('\0')
```

- 理解复杂声明 : 从内至外, 从右至左
```c++
int *ptr1[10]; // ptr1 是个含有10个元素的数组, 元素类型为 int *
int (*ptr2)[10];  // ptr2 是一个指针, 指向含有10个int的数组
int &ptr3[10];  // 出错, ptr3 不存在引用的数组
```

## 5.2 数组与指针
```c++
#include <iterator>
int a[10];
auto beg = std::begin(a);  //  获取首元素指针
auto end = std::end(a);  // 获取尾后指针
ptrdiff_t diff = end - beg;  // 指针相减类型为ptrdiff_t, 空指针相减为0
int length = (sizeof(a) / sizeof(int));
assert(length == diff);

vector<int> vec(beg, end);  // 通过指针初始化
```


```c++
int arr[4] = {1, 2, 3, 4};
int *p = arr + 2;  // 指向 元素 3
std::cout << &arr << std::endl; // 	0x7fff0416fae0  数组的开始地址, 也是第一个元素地址
std::cout << arr + 1 << std::endl; // 0x7fff0416fae4  第二个元素地址
std::cout << &arr + 1 << std::endl; // 0x7fff0416faf0  第二个数组开始地址, 也是尾后地址
std::cout << p[-1]; // 指向 元素 2 内置数组下表类型可以为负号, 容器的下标类型不是有符号类型
```

## 5.3 C 风格字符
```c++
// 1. Null terminated 字符数组
const char p[] = {'a', 'b', 'c', '\0'};
// const char p[] = "abc";

const char *q = p;
// 2. 字符数组转换成string
std::string str(q, q + strlen(q));
// std::string str(std::begin(p), std::end(p));
std::cout << str << std::endl;

const char *cstr = str.c_str(); 
// 3. string转换成字符数组指针 注意是const 防止string发生变化, 最好拷贝一份
char *cstrtemp = new char [strlen(str.c_str())+1];
strcpy(cstrtemp, str.c_str());
std::cout << cstr << std::endl;
```

## 5.4 多维数组
- (1) 下标 遍历多维数组
```c++
int ia[3][4];
for (size_t row = 0; row < 3; ++row)
    for (size_t col = 0; col < 4; ++col)
        cout<<ia[row][col]<<" ";
```

- (2) 指针 遍历多维数组
```c++
int ia[3][4];
for (int (*row)[4] = ia; row != ia + 3; ++row)
    for (int *col = *row; col != *row + 4; ++col) 
        cout<<*col<<" ";

// 或者用auto
for (auto row = ia; row != ia + 3; ++row)
    for (auto col = *row; col != *row + 4; ++col)
        cout<<*col<<" ";
```

- (3) for-range 遍历多维数组
```c++
//若以 const auto row ：ia ，在数组元素拷贝时
//会将int[]类型转成数组内首元素的指针即int *类型，&用来防止数组类型退化			   
int ia[3][4];
for(const auto (&row) : ia){  
    for(const auto &col : row)
        cout << col << " "; 
  
int ia[3][4];
for(const int (&row)[4] : ia)//同上
    for(const int &col : row)
        cout << col << " ";
```

- (4) 类型别名 遍历多维数组
```c++
int ia[3][4]={};
for(decltype(ia[0]) &row : ia)  // & 可加可不加
    for(decltype(ia[0][0]) col : row)
        cout << col << " ";
```