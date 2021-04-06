# 第六章 函数

## 1. 函数基础
### 函数
- 自动对象 : 控制流经过定义对象, 执行块结束销毁对象
- 形参 : 调用函数时, 隐式初始化, 调用结束后销毁, 其求值顺序未定义
- 局部变量 : 隐藏外部变量, 调用结束后销毁
- 局部静态对象 : 第一次调用函数时初始化, 直至程序结束被释放
- 函数声明(原型) : 声明可以多次, 定义只有一次, 放在头文件中, 形参名可以省略

### 参数
- 传递方式 : 引用传递 与 值传递
- 数组名传递规则 : 数组无法被拷贝, 数组名在拷贝时会转化成指向第一个元素指针, 因此函数的参数在被重载规则进行考量时会遵守这个规则 :
```c++
void func1(int *arr1){}
//void func1(int arr1[10]){} // 参数 : 退化成指针

void func2(int arr2[][10]){}
//void func2(int (*arr2)[10]){} // 参数 : 退化成指向10个数数组的指针

void func3(int (&arr3)[10]){} // 参数 : 10个数的数组, 防止退化
// 不存在 int &arr[] 引用的数组
```

- main 函数参数 : 
```c++
int main(int argc, char *argv[]); 
// 1. argc = 参数个数+1(程序名)
// 2. argv是包含多个参数的字符串数组
//    argv[0]是程序名称
//    argv[1]开始存放参数
```

- 可变参数 : `initializer_list<T> list`
```c++
#include <initializer_list>
void f1(initializer_list<string> li){
	// li 中是常量, 不可改变
	for(auto it = li.cbegin(); it != li.cend(); ++it)
        cout<<*it;
}
f1({"123", "321", "213"});
```

### 返回值
- 每个逻辑线路上必须有返回值
- 返回值通过创建临时量来返回
- 非常量引用返回值可以将函数调用作为左值使用
- 可以通过return {a,b,c,...}; 来返回vector\<T> 类型
- main一般用\<cstdlib>中的EXIT_FAILURE或EXIT_SUCCESS来返回,main不能调用自己

### 返回复杂类型
- 类型别名 : `using/typedef`
- 函数形式 : `type (*function(...))[dimension]`
- 置尾返回类型 : `auto func(...)->type (*)[dimension]`
- decltype : `decltype(obj) *function(...)`

## 2. 函数重载
### 重载函数
- 定义 : 同一作用域中, 函数名字相同, 但是形参列表不同的函数
- 重载条件 : 形参数量或形参类型必须有不一致地方(忽略顶层const和返回类型)
- 覆盖情况 : 作用域内的定义的同名函数会覆盖掉作用域外的同名函数, 名字查找优先于类型检查

### 函数匹配
- 定义 : 重载确定,在重载集合中匹配最合适的函数进行调用
- 三种结果 : 最佳匹配, 无匹配, 二义性调用
- 三个步骤 :
    - 同名,可见函数 -> 候选函数
    - 形参与实参数量可以相等,类型可以相互转换 -> 可行函数/无匹配
    - 形参与实参类型越接近越好 -> 最佳匹配/二义性

- 最佳匹配原则 : 每个实参匹配不劣于其他函数, 至少一个匹配优于其他函数

### 匹配等级
1. 精确匹配 :
    - 类型相同
    - 数组名或函数名退化成对应指针
    - const int -> int  或 int -> const int
2. 非底层const 转换为同类型底层const (存在底层const不同的调用区别)
3. 算术类型提升
```c++
void func(int);
void func(short);
short a=3;
func(a); // 精确匹配,调用后者
func('c'); // 首先没有找到精确匹配函数,char进行类型提升,调用前者
```
4. 算数类型转换(所有的算数类型转换都一样) 或 指针转换
    - 0/nullptr -> type\*;
    - type \* -> (const) void \*;
5. 类类型转换

## 3. 默认实参
- 默认实参后面的参数必须有默认实参
- 调用时只能省略后部分的默认实参
- 全局变量,函数等(表达式最终可转换为参数类型)都可以作为默认实参, 但是局部变量不能
```c++
int global_var=1;
int func(int i){return i;}
int default_pargm_test(int a=global_var, int b=func(1)){
    return a+b;
}

int main(int argc, char *argv[]){
    int global_var=2; // 虽然global_var覆盖了全局变量, 但是与默认实参没有关联
    cout<<default_pargm_test();
    //结果为 2 不是 3,局部变量不能作为默认实参
    return 0;
}
```

## 4. 内联与静态函数
### 内联函数 
- `inline int func(){}` 
- 在调用点上内联展开, 不用保存寄存器拷贝赋值参数, 开销小, 缺点为链接文件较大
- 用于规模小流程简单调用频繁的函数, 最终是否优化取决于编译器

### constexpr 函数 
- `constexpr int func(){}` : 可用于静态表达式的函数
- 条件 : 
    1. 返回值和参数都是字面值类型
    2. 函数体中只有一个return语句或者空语句
    3. 函数体中可以包括类型别名 和 using语句
- 允许constexpr函数返回值不是一个常量, 字面值类型参数为常量则返回结果为常量, 否则最后会根据使用的上下文进行检查
- 隐式内联展开
> 内联与constexpr函数可以多次定义, 但定义必须一致, 两者定义都应该放在头文件中

## 5. 宏处理
- 断言 assert(expr) 定义在\<cassert>中,用法 assert(a.size()\<b.size()); 如果为假则中断程序输出信息
- #define NDEBUG 会忽略assert, 也可以将NDEBUG作为自己的测试标记, 可以在编译过程中通过加上 -D NDEBUG 来避免测试
```c++
cerr << "Error: " << __FILE__ //文件名
    << " : in function " << __func__ //当前函数名字
    // << " : in function " << __FUNCTION__ 同上
    << " at line " << __LINE__ << endl //当前行号
    << " Compiled on " << __DATE__ //编译日期
    << " at " << __TIME__ << endl //编译时间
```

## 6. 函数指针
- 函数类型 : 由返回值类型, 参数数量, 参数类型决定
- 函数指针在赋值时, 函数类型必须精确匹配
- 函数指针作为返回类型格式 : `funcp_return_type (*funcname(参数列表))(函数指针参数列表){...}`
```c++
// #1. 定义函数指针的方式
bool pf_test(const string &s1, const string &s2){ // 函数定义
    return s1.size()>s2.size();
}
bool (*pf)(const string &, const string &); // 定义一个函数指针 "*"必须加括号

// #2. 两种函数指针作为参数的方式
bool pf_pargm(bool pf(const string &, const string &)); 
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
using x=void (*[10]) (void (*)()); 
/*   
      (*[10])指指针数组 如果是 (*)[10]则是指向函数类型数组的指针 (出错)
      int (*a) [13]; // 指向 int 数组的指针    
      a=nullptr;        
      int (*b[13]);  // 指针数组  
      b=nullptr;     // 出错
      b[0]=nullptr;  // 正确
     // (void (*)())表示形参列表  
     // x是指包含10个函数指针数组类型 函数是返回类型为void 形参为返回值为void形参为void的函数函数指针
*/

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

### 7. 例题
1. (6.1) 实参和形参的区别是什么?
   1. 形参是在调用函数时接受实参值的变量,由参数列表定义,调用时分配内存,结束调用时释放内存,作用域仅在函数中
   2. 实参是形参的初始值,在调用时能够求得确切的值,单项拷贝传递内容给形参,值传递实参内容不能通过函数改变(引用传)递可以)
2. (6.18) 编写函数声明
   1. bool compare(const matrix &m1, const matrix &m2);
   2. vector\<int>::iterator change_val(int e, vector\<int>::iterator it);
3. (6.25) 编写一个main函数,接受两个string,输出拼接后的string
   ```C++
      int main(int argc, char *argv[]){
       if(argc>2)
           cout<<argv[1]<<argv[2]<<endl;
       else cout<<"no enough options!"<<endl;
       return 0;
   }
   ```
4. (6.27) 编写一个函数,参数为initializer_list\<int>,计算所有数的和
   ```C++
   int clac_all(initializer_list<int> list){
       int sum=0;
       for(const auto &it:list)
           sum+=it;
       return sum;
   }
   ```
5. (6.33) 编写一个递归函数,输出vector对象的内容,调试输出vector大小
   ```C++
   void print(const vector<int> &vec, int index){
   	#ifndefine NDEBUG
   	static int times=0;//调用的第一次输出vector大小
   	++times;
   	if(times==1)
       		cout<<sizeof(vec)
   	#endif    
       	if(index>=0){
           	cout<<" "<<vec[index];
           	print(vec,index-1);
       	}
       	else cout<<"\ntraverse is over!\n";
   }
   ```
6. (6.36&37) 用4种方式声明返回10个数组引用的函数
   ```C++
   using namespace std;
   using array10=int [10];
   int a[10]={};

   int (&return_ref2array1())[10]; // 直接用类型表示
   array10 &return_ref2array2(); //类型别名
   auto return_ref2array3()->int (&)[10]; //置尾返回类型
   decltype(a) &return_ref2array4(); //decltype
   ```
7. (6.46) 能把const string &isShorter(const string &s1, const string &s2){return s1.size()<=s2.size()?s1:s2;}改成constexpr吗?
   不可以，const string& 虽然是常量引用但不是字面值类型
   返回值和参数必须是字面值类型
8. (6.48) 说明下面循环意义,assert使用合理吗?
   ```C++
   string s;
   while(cin>>s&&s!=sought){}
   //反复读入一个字符串直到读入的字符串等于sought
   assert(cin);
   /*
       对cin的状态进行判断 eofbit failbit badbit good
       其中默认调用operator bool来转换成bool形式,与good()有区别!
       bool()只有在 failbit badbit 都不为真的情况下返回真
       good()只有在 eofbit failbit badbit 都不为真的情况下返回真

       此处通过assert判断cin读入到状态如何是可以的
       1.没读对string类型cin出错 failbit -> false
       2.没读对string内容,反复读str直到读到^z导致最后没有读到内容 failbit->false
       3.只有在 cin>>s; //输入 str (后接^z或者其他字符都可以) cin状态goodbit和eofbit bool为真
   */
   ```
9. (6.50) 已知函数声明,判断下列调用重载函数的情况
   ```C++
   void f(){} // 1
   void f(int e){} // 2
   void f(int e, int f){} // 3
   void f(double e, double f=3.14){} // 4

   int main(int argc, char *argv[]){
       f(2.56, 42); // 2.56->double 42(先提升成int)->double 二异
       f(42); // 调用 2
       f(42, 0); // 调用 3
       f(2.56, 3.14); // 调用4
       return 0;
   }
   ```
10. (6.54-56) 定义一个元素是 接受2个int形参返回int的函数指针的vector,编写加减乘除4个函数,将4个函数放入vector中,最后调用
    ```C++
    // 注意 std::minus 会和自己定义的minus命名冲突
    int add(int e1, int e2){ return e1+e2; }
    int minuss(int e1, int e2){ return (e2!=0)?e1-e2:0; }
    int multiply(int e1, int e2){ return e1*e2; }
    int divide(int e1, int e2){ return e1/e2; }
    using FuncP=int (*)(int, int);
    vector<FuncP> vec;
    int main(int argc, char *argv[]){
        vec.push_back(add);
        vec.push_back(minuss);
        vec.push_back(multiply);
        vec.push_back(divide);
        cout<<vec[0](1,2)<<endl; //3
        cout<<vec[1](1,1)<<endl; //0
        cout<<vec[2](2,3)<<endl; //6
        cout<<vec[3](6,3)<<endl; //2
        return 0;
    }
    ```
