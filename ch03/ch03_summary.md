# 第三章 字符串、向量与数组
### 1. using声明
- using 声明 : using namespace::name; 简化使用命名空间中的成员
- 一般不在头文件中使用using声明, 防止命名冲突

### 2. string

#### string 基本用法

| string用法 `<string>`                                        | 解释                                                       |
| ------------------------------------------------------------ | ---------------------------------------------------------- |
| string s1;                                                   | 默认初始化                                                 |
| string s1("123");<br/>string s1(s2);<br/>string s1(20, 'c'); | 直接初始化                                                 |
| string s1="123";<br/>string s1=s2;                           | 拷贝初始化                                                 |
| os<<s1;<br/>is>>s1;                                          | 打印<br/>忽略空白符读入, 以空白符分隔                      |
| getline(is, s1);                                             | 读入一行包括`\n`但是舍去后赋予s1内容, 返回is               |
| s1[0];                                                       | 返回下标为0的引用                                          |
| s1+s2;                                                       | 忽略`\0`连接两个字符串, 返回新创的string对象               |
| s1.size(); s1.empty()                                        | 查询相关信息, 其中size() 返回 string::size_type 无符号类型 |
| s1!=s2; s1==s2; ( <, >, <=, >= )                             | 按字典序再按个数比较                                       |

> 注意, `auto a="123"+"234";`非法, 不能将两个字面值常量直接相加

#### 判断字符函数
- 定义在 `<cctype>` 中
- isalpha() 判断是否为字母
- isdigit() 判断是否为数字
- isalnum() 判断是否为字母或数字
- islower() 判断是否为小写字母 tolower()转换为小写字母
- isupper() 判断是否为大写字母 toupper()转换为大写字母
- ispunct() 判断是否为标点符号

#### 遍历字符
```c++
// for-range 语句
for(auto &it : str)  // 遍历每个元素 除末尾 `\0`
	...

// 通过string下标遍历
for(decltype(str.size()) index=0; index!=str.size(); ++index)
	... 
```

### 3. vector
#### vector基本用法

| vector用法 \<string> | 解释 |
| --- | --- |
| vector\<T> v1; | 默认初始化 |
| vector\<T> v1(v2)/(it1, it2)<br/>vector\<T> v1(n);<br/>vector\<T> v1(n, val);<br/>vector\<T> v1{val1, val2, val3}; | 拷贝初始化<br/>直接初始化<br/>指定数量默认初始化(根据类型不同有不同的初识值)<br/>列表初始化 |
| vector\<T> v1=v2;<br/>vector\<T> v1={val1, val2, val3}; | 拷贝初始化 |
| v1.push\_back(val); | 在末尾插入元素 |
| v1[0]; | 返回下标为0的引用 |
| v1.size(); v1.empty() | 查询相关信息, 其中size()返回 vector\<T>::size_type 无符号类型 |
| v1!=v2; v1==v2; ( <, >, <=, >= ) | 按字典序和个数比较 |

- vector 是模板类, 根据类型进行实例化, 默认初始化时会对各个元素进行值初始化
- `vector<string> a{10};` 列表初始化, 先按元素初识值列表初始化 如果无法执行则按指定数量初始化
- range-for语句或其他循环语句内不应该改变容器大小

### 4. iterator

| iterator用法 \<iterator> | 解释 |
| --- | --- |
| c.(c)begin(); <br/>c.(c)end(); | 获取首和尾后迭代器 |
| == != | 判断迭代器是否指向同一个位置  |
| ++it; <br/>--it; | 移动到下一个或上一个位置 |
| (\*it).func(); <br/>it->func(); | 解引用后调用成员函数 |
| it+(-)n; it+(-)=n; | 向后(前)移动n个位置 |
| 比较操作符 | 越前越小,越后越大(只有随机访问迭代器有比较操作符) |
|iter1-iter2 |两个之间的间距 是difference_type 类型带符号类型|

> 注意对容器修改可能会导致迭代器失效, 解非法迭代器行为未定义

```c++
// 二分查找, 返回 <= e 的最大位置的迭代器, 如果指向首前修正为第一个元素
template<typename T>
typename std::vector<T>::const_iterator find(const std::vector<T> &vec, const T &e){
    auto lo=vec.begin();
    auto hi=vec.end();
    while(lo!=hi){
        auto mid=lo+(hi-lo)/2;
        if(e<*mid) hi=mid;
        else lo=mid+1; // *mid<=e
    }
    --lo;
    if(vec.begin()>lo) return ++lo;
    return lo;  
}
```

### 5. 数组
#### 定义与初始化
- 定义数组时下标一定是一个常量表达式, 通常设定为一个size_t无符号类\<cstddef>中 或 std::size_t
- 数组元素一定是一个对象, 不存在引用的数组
- 无法被拷贝,赋值但可用于for range语句
```c++
const char str[7]="123";  // 存在字符串常量到常量字符数组的转化, 注意大小一定容下('\0')
```

- 理解复杂声明 : 从内至外, 从右至左
```c++
int *ptr[10]; // ptr是个含有10个元素的数组, 元素类型为 int *
int (*ptr)[10];  // ptr是一个指针, 指向含有10个int的数组
```

#### 数组与指针
- `int *beg=begin(array_name);` 获取首元素指针 `<iterator>` 
- `int *end=end(array_name);` 获取尾后指针 `<iterator>`
- 指针相减类型为ptrdiff_t, 带符号类型与迭代器的 difference_type 类似
- 不同类型指针不能比较, 空指针相减为0

```c++
int arr[4]={1,2,3,4};
int *p=arr+2;  // 指向 元素 3
std::cout<<&arr<<std::endl; // 	0x7fff0416fae0  第一个元素地址
std::cout<<arr+1<<std::endl; // 0x7fff0416fae4  第二个元素地址
std::cout<<&arr+1<<std::endl; // 0x7fff0416faf0  尾后地址
std::cout<<p[-1]; // 指向 元素 2 内置数组下表类型可以为负号
```

#### C风格字符
```c++
const char p[]={'a', 'b', 'c', '\0'}; // 1. Null terminated 字符数组
// const char p[]="abc";

const char *q=p;
std::string str(q, q+strlen(q));
// 2. 字符数组转换成string
// std::string str(std::begin(p), std::end(p));
std::cout<<str<<std::endl;

const char *cstr=str.c_str(); 
// 3. string转换成字符数组指针 注意是const 防止string发生变化, 最好拷贝一份
char *cstrtemp = new char [strlen(str.c_str())+1];
strcpy(cstrtemp, str.c_str());
std::cout<<cstr<<std::endl;
```

#### 多维数组
- (1) 下标 遍历多维数组
```c++
int ia[3][4];
for(size_t row=0;row<3;++row)
    for(size_t col=0;col<4;++col)
        cout<<ia[row][col]<<" ";
```

- (2) 指针 遍历多维数组
```c++
int ia[3][4];
for(int (*row)[4]=ia;row!=ia+3;++row)
    for(int *col=*row;col!=*row+4;++col) 
        cout<<*col<<" ";

// 或者用auto
for(auto row=ia;row!=ia+3;++row){
    for(auto col=*row;col!=*row+4;++col)
        cout<<*col<<" ";
```

- (3) for-range 遍历多维数组
```c++
//若以 const auto row ：ia ，在数组元素拷贝时
//会将int[]类型转成数组内首元素的指针即int *类型，&用来防止数组类型退化			   
int ia[3][4];
for(const auto (&row) : ia){  
    for(const auto &col : row)
        cout<<col<<" "; 
  
int ia[3][4];
for(const int (&row)[4] : ia)//同上
    for(const int &col : row)
        cout<<col<<" ";
```

- (4) 类型别名 遍历多维数组
```c++
int ia[3][4]={};
for(decltype(ia[0]) &row : ia)  // & 可加可不加
    for(decltype(ia[0][0]) col : row)
        cout<<col<<" ";
```
