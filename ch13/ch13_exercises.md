(13.14-17) 假定numbered是一个类, 他有一个默认构造函数,能为每个对象生成一个唯一的序号,保存在名为mysn的数据成员中,假定numbered使用合成的拷贝控制成员,并给定如下函数
`void f(numbered s) { cout<<s.mysn<<endl; }`
1.下面代码输出什么内容?
2.定义拷贝构造函数会产生新的序号会输出什么内容?
3.如果f参数为(number& s)会输出什么内容?
`numbered a, b=a, c=b;`
`f(a); f(b); f(c);`

```
// 1. 首先会调用合成拷贝构造函数初始化b,c, 再通过值拷贝输出, 输出内容一致
// 2. 首先调用合成拷贝构造函数初始化b,c 序号不一致, 再通过值拷贝输出, 输出内容与原对象不一致
// 3. 首先调用合成拷贝构造函数初始化b,c 序号不一致, 再通过引用传递输出, 输出内容与原对象一致
```
(13.20)

(13.25) 假设定义StrBlob的类值版本, 且希望继续使用shared_ptr, 这样我们的StrBlobPtr类就仍能使用指向的weak_ptr了, 修改后的StrBlob需要一个拷贝构造函数和拷贝赋值运算符, 不需要析构函数,为什么?
```c++
class A{  // 等价StrBlob
	std::shared_ptr<int> ps;  // 对智能指针成员定义值拷贝则每个对象引用计数为1
public:
	A(const int &e=10): ps(std::make_shared<int>(e)){}

	A &operator=(const A &rhs){
		ps=std::make_shared<int>(*rhs.ps);  // 分配值拷贝, 原来分配的对象被销毁
	}

	A(const A &rhs):ps(std::make_shared<int>(*rhs.ps)){}  // 与赋值运算符类似
	~A()=default;  // 每个对象离开作用域时引用计数必定为0 则直接使用默认即可	
	void print() { std::cout<<*ps<<'\n'; }
};

```