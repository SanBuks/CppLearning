# 第三章 字符串、向量与数组
### 1. using声明
- using 声明 : using namespace::name; 简化使用命名空间中的成员
- 一般不在头文件中使用using声明, 防止命名冲突

### 2. string

#### string 基本用法

| string用法 `<string>`                                          | 解释                                                       |
| ------------------------------------------------------------ | ---------------------------------------------------------- |
| string s1;                                                   | 默认初始化                                                 |
| string s1("123");<br/>string s1(s2);<br/>string s1(20, 'c'); | 直接初始化                                                 |
| string s1="123";<br/>string s1=s2;                           | 拷贝初始化                                                 |
| os<<s1;<br/>is>>s1;                                          | 打印<br/>忽略空白符读入, 以空白符分隔                      |
| getline(is, s1);                                             | 读入一行包括`\n`但是舍去后赋予s1内容, 返回is               |
| s1[0];                                                       | 返回下标为0的引用                                          |
| s1+s2;                                                       | 忽略`\0`连接两个字符串, 返回新创的string对象               |
| s1.size(); s1.empty()                                        | 查询相关信息, 其中size() 返回 string::size_type 无符号类型 |
| s1!=s2; s1==s2; ( <, >, <=, >= )                             | 按字典序和个数比较                                         |

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

### 2. vector
#### vector基本用法

| vector用法 `<string>`                                        | 解释                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| vector\<T> v1;                                               | 默认初始化                                                   |
| vector\<T> v1(v2);<br/>vector\<T> v1(n);<br/>vector\<T> v1(n, val);<br/>vector\<T> v1{val1, val2, val3}; | 直接初始化<br/>指定数量默认初始化(根据类型不同有不同的初识值)<br/>列表初始化 |
| vector\<T> v1=v2;<br/>vector\<T> v1={val1, val2, val3};      | 拷贝初始化                                                   |
| v1.push\_back(val);                                          | 在末尾插入元素                                               |
| v1[0];                                                       | 返回下标为0的引用                                            |
| v1.size(); v1.empty()                                        | 查询相关信息, 其中size()返回 vector\<T>::size_type 无符号类型 |
| v1!=v2; v1==v2; ( <, >, <=, >= )                             | 按字典序和个数比较                                           |

- vector 是模板类, 根据类型进行实例化, 默认初始化时会对各个元素进行值初始化
- `vector<string> a{10};` 列表初始化, 先按元素初识值列表初始化 如果无法执行则按指定数量初始化
- range-for语句内不应该改变容器大小

### 3. iterator
- vec.begin() 指向首元素 vec.end() 指向尾后元素 vec.cbegin() 返回const迭代器
- ++it = 指向下一个元素
- \*iter 返回迭代器所指元素的引用 
- iter->men 等价 (\*iter).men 
- iter1-iter2 = 两个之间的间距 是difference_type 类型带符号类型可为负数,迭代器所指元素的秩越大则在表达式中的值越大
```c++
template<typename T>
auto find(const vector<T> &vec,const T &e){//二分查找
    auto lo=vec.begin();
    auto hi=vec.end();
    while(lo<hi){
        auto mid=lo+(hi-lo)/2;
        if(e<*mid) hi=mid;
        else lo=mid+1; // *mid<=e
    }
    return --lo;  //返回 <= e 的最大位置
}
int main(){
    std::ios_base::sync_with_stdio(false);
    vector<int> vec{1,2,5,7,88,102,333,456,555};
    cout<<*find(vec,12);
    return 0;
}
```

### 4. 数组
- 定义数组时下标一定是一个常量表达式,通常设定为一个size_t无符号类\<cstddef>中
- 数组名无法被拷贝,赋值 但是可以用于for range语句
- 复杂类型数组从右向左理解 int \*ptr[10]; ptr指向10个整型指针数组
- 复杂类型数组从中间向外理解 int (\*ptr)[10]; ptr是指向10个整型数组的指针

### 5. 指针
- int \*beg=begin(array_name); 获取首元素指针 int \*end=end(array_name); 获取尾后指针
- 指针相减类型为ptrdiff_t,带符号类型
- 不同类型指针不能比较,空指针相减为0
- 内置数组下表类型可以为负号,如 int \*p=&a[2]; 则\*p[-1]=a[1] , \*p[-2]=a[0]

### 6. 例题
1. (3.27) txt_size()是一个无参函数,返回值是int
    1. 可以作为常量表达式,如int a[txt_size()];
    2. 参见可被constexpr修饰的函数条件

2. (3.28) 在不同内存区定义数组时,默认初始化变量不同 
    1. string sa[10]; 在静态区还是堆栈区定义都为空串
    2. int ia[10]; 在静态区定义默认为0,在堆栈区定义随机
    3. int ia[10]={}; 在静态区还是堆栈区定义都为0

3. (3.29) 数组对比vector的缺点
    1. 大小固定,无法动态扩充
    2. 没有迭代器进行安全访问,需要寻址访问容易出现溢出
    3. 不支持泛型接口

4. (3.43-3.45) 多种方式遍历多维数组
```c++
    // #1 下标 遍历多维数组
    int ia[3][4];
    for(size_t row=0;row<3;++row)
        for(size_t col=0;col<4;++col)
            cout<<ia[row][col]<<" ";

    // #2 指针 遍历多维数组
    int ia[3][4];
    for(int (*row)[4]=ia;row!=ia+3;++row)
        for(int *col=*row;col!=*row+4;++col) 
            cout<<*col<<" ";

    // #3 指针-auto 遍历多维数组
    int ia[3][4];
    for(auto row=ia;row!=ia+3;++row){
        for(auto col=*row;col!=*row+4;++col)
            cout<<*col<<" ";

    // #4 for-range 遍历多维数组(*)
    //若以 const auto row ：ia ，在数组元素拷贝时
    //会将int[]类型转成数组内首元素的指针即int *类型，&用来防止数组类型退化			   
    int ia[3][4];
    for(const auto (&row) : ia){  
        for(const auto &col : row)
            cout<<col<<" ";
            
    // #5 for-range 显性遍历多维数组
    int ia[3][4];
    for(const int (&row)[4] : ia)//同上
        for(const int &col : row)
            cout<<col<<" ";

    // #6 类型别名 遍历多维数组
    int ia[3][4]={};
    for(decltype(ia[0]) &row : ia)  // & 可加可不加
        for(decltype(ia[0][0]) col : row)
            cout<<col<<" ";
```