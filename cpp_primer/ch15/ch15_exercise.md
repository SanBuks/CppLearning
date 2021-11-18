# 15.01 虚函数定义
> 什么是虚成员？

- 从声明形式上来说, 在类内中声明为 virtual 的非构造非静态函数
- 从使用方式上来说, 通过引用或指针调用, 会根据运行时对象类型的不同而调用不同的虚函数

# 15.02 private 和 protected
> protected 访问说明符与 private 有何区别？

- protected 禁止用户调用其成员, 可以让派生类函数和友元调用
- private 禁止用户调用其成员, 禁止派生类函数和友元调用

# 15.08 静态和动态类型
> 给出静态类型和动态类型的定义。

- 静态类型在编译时已知, 是定义时声明的类型
- 动态类型在运行时才知, 表示内存中的对象类型

# 15.09 静态和动态类型
> 在什么情况下表达式的静态类型可能与动态类型不同？请给出三个静态类型与动态类型不同的例子。

```c++
// 通过指针和引用调用对象接口时
Base &b = derived;
Base *p = &derived;
p->test();
```

# 15.13 调用父类函数
> 给定下面的类，解释每个 print 函数的机理：在上述代码中存在问题吗？如果有，你该如何修改它？
```c++
class base {
public:
  string name() { return basename;}
  virtual void print(ostream &os) { os << basename; }
private:
  string basename;
};

class derived : public base {
public:
  void print(ostream &os) {   // 覆盖父类虚函数
    print(os);                // 产生无限自调用, 应该修改为 base::print(os);
    os << " " << i; 
  }
private:
  int i;
};
```

# 15.14 多态
> 给定上一题中的类以及下面这些对象，说明在运行时调用哪个函数：
```c++
base bobj;     base *bp1 = &bobj;   base &br1 = bobj;
derived dobj;   base *bp2 = &dobj;   base &br2 = dobj;

bobj.print();  // 静态 base    
dobj.print();  // 静态 derived

bp1->name();   // 静态 base 非虚函数
bp2->name();   // 静态 derived 非虚函数  

br1.print();   // 动态 base
br2.print();   // 动态 derived
```

# 15.18 多态
> 假设给定了第543页和第544页的类，同时已知每个对象的类型如注释所示，判断下面的哪些赋值语句是合法的。解释那些不合法的语句为什么不被允许：
```c++
Base *p = &d1;  // d1  的类型是 Pub_Derv               - 用户合法
p = &d2;        // d2  的类型是 Priv_Derv              - 用户非法
p = &d3;        // d3  的类型是 Prot_Derv              - 用户非法
p = &dd1;       // dd1 的类型是 Derived_from_Public    - 用户合法
p = &dd2;       // dd2 的类型是 Derived_from_Private   - 用户非法
p = &dd3;       // dd3 的类型是 Derived_from_Protected - 用户非法
```

# 15.19 继承类向基类的可转换性
> 假设543页和544页的每个类都有如下形式的成员函数：
```c++
void memfcn(Base &b) { b = *this; }
Base *p = &d1;  // d1  的类型是 Pub_Derv               - 派生类中合法
p = &d2;        // d2  的类型是 Priv_Derv              - 派生类中合法
p = &d3;        // d3  的类型是 Prot_Derv              - 派生类中合法
p = &dd1;       // dd1 的类型是 Derived_from_Public    - 派生类中合法
p = &dd2;       // dd2 的类型是 Derived_from_Private   - 派生类中非法
p = &dd3;       // dd3 的类型是 Derived_from_Protected - 派生类中合法
```

# 15.20 继承类向基类的可转换性
> 编写代码检验你对前面两题的回答是否正确。

参考 summary

# 15.24 虚析构函数
> 哪种类需要虚析构函数？虚析构函数必须执行什么样的操作？

- 实现多态的派生类的基类需要定义虚析构函数
- 虚析构函数 先销毁属于自己的数据成员然后沿继承链不断向上重复该过程
- 虚析构函数 组织合成的移动操作

# 15.31 query 表达式调用顺序
> 已知 s1, s2 , s3 , 和 s4 都是 string，判断下面的表达式分别创建了什么样的对象：
```c++
Query(s1) | Query(s2) & ~Query(s3);
// ( OrQuery , NotQuery) -> AndQuery
Query(s1) | (Query(s2) & ~Query(s3));
// ( WordQuery , AndQuery) -> OrQuery  位与 > 位亦或  > 位或
(Query(s1) & (Query(s2)) | (Query(s3) & Query(s4)));
// ( AndQuery , AndQuery) -> OrQuery
```

# 15.34 query 表达式调用顺序
> 针对图15.3构建的表达式：

(a) 例举出在处理表达式的过程中执行的所有构造函数。
(b) 例举出 cout << q 所调用的 rep。
(c) 例举出 q.eval() 所调用的 eval。

```c++
Query q = Query("fiery") & Query("bird") | Query("wind");
/*
逻辑上遵循树顺序结构
1. consturctor : 
WordQuery temp1("fiery");
WordQuery temp2("bird");
AndQuery temp3(temp1, temp2, "&");
WordQuery temp4("wind");
OrQuery temp5(temp3, temp4, "|");

2. q.rep() :
               temp5->rep()
(           temp3->rep()        | temp4->rep())
( (temp1->rep() & temp2->rep()) | temp4->rep())
(        (fiery & bird)         | temp4->rep())
(        (fiery & bird)         | wind)

3. q.eval() :
                        temp5->eval()
(           temp3->eval()        | temp4->eval())
((temp1->eval() & temp2->eval()) | set(wind))
(  ( set(fiery) & set(bird) )    | set(wind))

*/
```

# 15.37 query 重构
> 如果在派生类中含有 shared_ptr<Query_base> 类型的成员而非 Query 类型的成员，则你的类需要做出怎样的改变？

1. 改变构造函数接口
2. 改变重载符号函数的接口
3. 继承类可以通过 shared_ptr 调用 rep 和 eval, 必须让rep 和 eval 开放
4. Query 类可以不定义, 作为 QueryBase 别名使用即可