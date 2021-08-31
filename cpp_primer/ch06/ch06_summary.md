# 1. 函数基础
## 1.1 函数
- 函数 : 命名的代码块, 由 返回类型, 函数名, 形参列表和函数提组成, 其中返回类型不能是数组和函数
- 自动对象 : 控制流经过定义对象, 执行块结束销毁对象
- 形参变量 : 自动对象, 调用函数时隐式初始化, 求值顺序未定义
- 局部变量 : 隐藏外部变量, 调用结束后销毁
- 局部静态变量 : 控制流第一次遇到时初始化, 直至程序结束被释放 
- 函数声明 : 声明可以多次, 定义只有一次, 放在头文件中, 形参名可以省略

## 1.2 参数
### 值传递
- 局部变量改变不影响实参
- 忽略实参的顶层 const
### 引用传递
- 局部变量改变影响实参
- 底层 const 影响重载
- 尽量使用 底层 const 实参增加性能和重载范围
### 数组名传递规则
- 数组无法被拷贝, 数组名在拷贝时会退化
- 数组名在重载时会参照退化后的结果
- 数组传递时需要给与额外信息防止越界 : 结束哨兵; 迭代器范围; 起始位置和个数
```c++
void func1(int *arr1) {}
// 等价 void func1(int arr1[10]){}  // 参数 : 退化成指针

void func2(int arr2[][10]) {}
// 等价 void func2(int (*arr2)[10]){}  // 参数 : 退化成指向10个数数组的指针

void func3(int (&arr3)[10]) {  // 参数 : 10个数的数组, 防止退化
  for (auto elem : arr3) { }  // 为退化的数组名可以用于 rang-for
} 

void func4(int &arr4[10]) {}  // 错误, 引用非对象, 不存在元素为引用的数组
```

### main 函数参数
```c++
int main(int argc, char *argv[]); 
// 1. argc = 参数个数 + 1(程序名)
// 2. argv是包含多个参数的字符串数组
//    argv[0]是程序名称
//    argv[1]开始存放参数
```

### 可变参数
- initializer\_list
```c++
#include <initializer_list>
void f1(initializer_list<string> li) {
	// 1. li 中元素是实参的拷贝, 常量, 不可改变
	for(auto it = li.cbegin(); it != li.cend(); ++it)
        cout<<*it;
}
// 2. l1 与 l2 共享元素 (本身元素为常量)
initializer_list<string> l1{"1", "2", "3"};
initializer_list<string> l2 = l1;
// 3. 调用形式
f1({"123", "321", "213"});  
```

- 省略符 varargs 形参, 放置于形参列表最后

## 1.3 返回值
- 有返回值函数 : 每个逻辑线路上必须有返回值, 返回值可以转换为返回类型
- 右值返回 : 返回值通过创建临时量来返回
- 左值返回 : 非常量引用作为返回值, 可以将函数调用作为左值使用 (注意, 不能是局部对象)
- 列表初始化返回值 : 可以通过 `return {a,b,c,...};` 来返回 vector\<T> 类型
- main返回值 : 使用\<cstdlib>中的宏 EXIT_(FAILURE|SUCCESS) 返回

## 1.4 返回复杂类型
### 直接返回
```c++
// 1. 返回数组
// TYPE (*FUNC_NAME(ARG...))[DIMENSION];
int (*ReturnArrayPointer(int var))[10] {
    int (*p)[10] = new int[10][10];
    return p;
}

// 2. 返回函数指针
// RETURNTYPE (*FUNC_NAME(ARG...))(RETURN_FUNC_ARG...)[RETURN_DIMENSION]; 
int (*(*ReturnFuncPointer(int var))(int))[10] {
    return ReturnArrayPointer;
}
```

### using/typedef
```c++
// using Array2D10 = int (*)[10];
typedef int (*Array2D10)[10];
Array2D10 ReturnArrayPointer(int var) {
    int (*p)[10] = new int[10][10];
    return p;
}

// using FuncType = int (*(int))[10];
typedef int (*FuncType(int))[10];
FuncType *ReturnFuncPointer(int var) {
    return ReturnArrayPointer;
}

// using FuncTypePointer = int (*(*)(int))[10];
typedef int (*(*FuncTypePointer)(int))[10];
FuncTypePointer ReturnFuncPointer(int var1, int var2) {
    return ReturnArrayPointer;
}
```

### decltype
```c++
// decltype(OBJ) *FUNC_NAME(ARG...)
int array[10] = {};

decltype(array) *ReturnArrayPointer(int var) {
int (*p)[10] = new int[10][10];
    return p;
}

decltype(ReturnArrayPointer) *ReturnFuncPointer(int var) {
    return ReturnArrayPointer;
}
```

### 置尾尾返回符
```c++
// auto FUNC_NAME(ARG...) -> TYPE (*)[DIMENSION]
auto ReturnArrayPointer(int var) -> int (*)[10] {
    int (*p)[10] = new int[10][10];
    return p;
}

// auto FUNC_NAME(ARG...) -> TYPE (*(*)(RETURN_FUNC_ARG...))[DIMENSION]
auto ReturnFuncPointer(int var) -> int (*(*)(int))[10] {
    return ReturnArrayPointer;
}
```

## 1.5 默认实参
- 默认实参位置要求 : 默认实参后面的参数必须有默认实参
- 默认实参调用要求 : 
    - 调用时只能省略后部分的默认实参, 前部分的默认实参需要自己填充数值, 因此一般将常用的参数放在前面
    - 在作用域内, 不能修改已存在的默认实参, 可以添加默认实参
    - 全局变量,函数等(表达式最终可转换为参数类型)都可以作为默认实参, 但是局部变量不能
```c++
// 全局变量,函数等最终可转换为参数类型都可以作为默认实参
int global_var=1;
int func(int i) {return i;}
int default_pargm_test(int a=global_var, int b=func(1)) {
    return a+b;
}

// 虽然 global_var 覆盖了全局变量, 但是与默认实参没有关联
// 总之, 局部变量不能作为默认实参
int main(int argc, char *argv[]){
    int global_var=2; 
    cout<<default_pargm_test();
    //结果为 2 不是 3,局部变量不能作为默认实参
    return 0;
}
```

# 2. 函数重载
## 2.1 重载函数
- 定义 : 同一作用域中, 函数名字相同, 但是形参列表不同的函数
- 重载条件 : 形参数量 或 形参类型必须有不一致地方 (忽略形参的顶层const 和 返回类型)
- 覆盖情况 : 作用域内的定义的同名函数会覆盖掉作用域外的同名函数, 名字查找优先于类型检查
```c++
// 非底层 const 参数 函数委托 底层 const 参数函数 进行重载
// 注意, 如果需要 非底层 const 参数 和 底层 const 参数 的函数进行重载, 则一定可以进行这样的委托!
const string &shorterString(const string &s1, const string &s2){
    return s1.size() <= s2.size() ? s1 : s2;
}
string &shorterString(string &s1, string &s2){
	return const_cast<string &>(
		shorterString(
			const_cast<const string &>(s1), 
			const_cast<const string &>(s2)
		)
	);
}
```

## 2.2 函数匹配
- 定义 : 又称重载确定, 在重载集合中匹配最合适的函数进行调用
- 三种结果 : 最佳匹配, 无匹配, 二义性调用
- 三个步骤 :
    - 作用域内可见的同名函数 -> 候选函数
    - 形参与实参数量可以相等, 类型可以相互转换 -> 可行函数 / 无匹配
    - 形参与实参类型越接近越好 -> 最佳匹配 / 二义性
- 最佳匹配原则 : 每个实参匹配不劣于其他函数, 至少一个匹配优于其他函数

## 2.3 匹配等级
1. 精确匹配 :
    - 类型相同(同类型引用)
    - 数组名或函数名退化成对应指针
    - const int -> int  或 int -> const int (值传递)
2. 非底层 const 转换为同类型底层 const (存在底层const不同的调用区别)
3. 算术类型提升
```c++
void func(int);
void func(short);
short a=3;
func(a); // 精确匹配,调用后者
func('c'); // 首先没有找到精确匹配函数,char进行类型提升,调用前者
```

4. 算数术型转换 ( 所有的算术类型转换都一样 ) 和 指针转换
    - 0/nullptr -> type\*;
    - type \* -> (const) void \*;
    - &derivedObject -> BaseClass \*
5. 类类型转换

# 3. 内联与静态函数
## 3.1 内联函数 
- 形式 : `inline int func() {}` 
- 优点 : 
    - 是一个函数但是在调用点上内联展开, 不用保存寄存器拷贝赋值参数, 开销小
    - 参数进符号表, 编译错误会返回错误提示信息, 比宏更安全
- 缺点 : 
    - 只用于规模小流程简单调用频繁的函数
    - 最终是否优化取决于编译器缺点
    - 内联过多, 链接文件较大

## 3.2 constexpr函数 
- 形式 : `constexpr int func() {}` (隐式内联)
- 用途 : 可用于静态表达式
- 条件 : 
    1. 返回值和参数都是字面值类型 (字面值, const 基本类型, 静态对象的指针和引用, 字面值常量类)
    2. 函数体中只有一个return语句 或 空语句
    3. 函数体中可包括 类型别名 和 using语句
- 允许返回值不是常量 : 字面值类型参数为常量则返回结果为常量, 最后编译器会根据上下文进行检查
> 内联与constexpr函数可以多次定义, 但定义必须一致, 两者定义都应该放在头文件中

# 4. 宏处理与调试
- 断言 assert
```c++
#include <cassert>
int main(){
	int a = 2;
	assert(a == 3); // 如果为假则中断程序输出信息
// Assertion `a == 3' failed.
	return 0;
}
```

- \#define NDEBUG 会忽略 assert, 可以将 NDEBUG 作为自己的测试标记 也可以 -D NDEBUG 来避免测试
```c++
# ifndef NDEBUG
std::cerr << "Error: " << __FILE__ //文件名
    << " : in function " << __func__ //当前函数名字
    // << " : in function " << __FUNCTION__ 同上
    << " at line " << __LINE__ << endl //当前行号
    << " Compiled on " << __DATE__ //编译日期
    << " at " << __TIME__ << endl //编译时间
# endif
```

# 5. 函数指针
- 函数类型 : 由返回值类型, 参数数量, 参数类型(只要不同即可)决定 (跟重载不一样的地方)
- 函数指针在赋值时, 函数类型必须精确匹配
- 函数指针作为返回类型格式 : `funcp_return_type (*funcname(参数列表))(函数指针参数列表){...}`
```c++
// #1. 定义函数指针的方式
bool pf_test(const string &s1, const string &s2){ // 函数定义
    return s1.size()>s2.size();
}
bool (*pf)(const string &, const string &); // 定义一个函数指针 "*"必须加括号

// #2. 两种函数指针作为参数的方式
// 自动转换为函数指针
bool pf_pargm(bool pf(const string &, const string &)); 
// 显示声明为函数指针
bool pf_pargm(bool (*pf)(const string &, const string &));

// #3. 三种对函数类型和函数指针做类型别名的方式
typedef bool Func1(const string &, const string &); // typedef类型别名 Func 是函数类型
typedef bool (*FuncP1)(const string &, const string &); // typedef类型别名 FuncP 是函数类型的指针

typedef decltype(pf_test) Func2; // decltype(函数名) 表示函数类型 （在decltype中函数名不会退化成函数指针）
typedef decltype(pf_test) *FuncP2; // decltype(函数名)* 表示函数类型的指针
typedef decltype(pf) FuncP2; // decltype(函数指针） 表示函数类型的指针（与函数名不一样）

using Func3=bool (const string &, const string &); // using 表示 Func3 是 函数类型
using FuncP3=bool (*)(const string &, const string &); // using 表示 FuncP3 是函数类型指针

// #4. 两种函数指针作返回值的方式
bool (*pf_return1(FuncP1 p))(const string &, const string &){ return p; } // 函数指针作为返回值
auto pf_return2(FuncP1 p)->bool (*)(const string &, const string &){ return p; }; // 用置尾法定义函数指针作为返回值

// #5. 指针数组和数组指针的区别
/*
(*[10])指指针数组 如果是 (*)[10]则是指向函数类型数组的指针
int (*a) [13]; // 指向 int 数组的指针    
int (*b[13]);  // 指针数组  
*/

using x = void (*[10]) (void (*)()); 
// (void (*)())表示形参列表  
// x 是指包含10个函数指针数组类型 函数是返回类型为void 形参为返回值为void形参为void的函数函数指针

int main(int argc, char *argv[]){
    // #6. 函数指针的三种赋值
    pf=nullptr; 
    pf=pf_test;
    pf=&pf_test;

    // #7. 通过函数指针调用函数两种形式
    bool b1=pf("123","456"); 
    bool b2=(*pf)("123","456");
    return 0;
}
```