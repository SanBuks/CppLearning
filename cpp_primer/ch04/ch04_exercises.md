# 4.07 整型溢出
> 溢出是何含义？写出三条将导致溢出的表达式。
```c++
// 溢出 超出类型描述范围, 发生模循环
// 64 位机器字长下:
unsigned a = 4294967295; a += 1;
int b = -2147483648;     b -= 1;
short c = 32767;         c += 1;
```

# 4.08 求值顺序
> 说明在逻辑与、逻辑或及相等性运算符中运算对象的求值顺序。

1. && 假短路
2. || 真短路
3. ? : 先判断, 真前假后
4. 逗号运算符则按对象出现顺序求值
5. 其他未定义求值顺序

# 4.09 求值顺序
> 解释在下面的if语句中条件部分的判断过程。
```c++
const char *cp = "Hello World";
if (cp && *cp)  // cp 首先是非空指针 然后其所指 char 非 '\0'
```

# 4.14 赋值语句作为判断条件
> 行下述 if 语句后将发生什么情况？
```c++
if (42 = i)   // 42 非 左值, 编译错误
if (i = 42)   // 恒为真, 逻辑错误
```

# 4.16 赋值语句作为判断条件
> 尽管下面的语句合法，但它们实际执行的行为可能和预期并不一样，为什么？应该如何修改？
```c++
if (p = getPtr() != 0)  // if ((p = getPtr()) != 0)
if (i = 1024)           // if (1024 == i)
```

# 4.17 递增运算符
> 说明前置递增运算符和后置递增运算符的区别。

- 前置递增: 先将对象 +1 后对表达式求值, 作用于左值, 返回左值
- 后置递增: 先将对象 +1 后用之前的副本对表达式求值, 作用于左值, 返回右值

# 4.19 求值顺序, 运算符优先级与递增运算符
> 假设ptr的类型是指向int的指针，vec的类型是vector\<int>， ival的类型是int，说明下面的表达式是何含义？
> 如果有表达式不正确，为什么？应该如何修改？
```c++
ptr != 0 && *ptr++        // 先判断 ptr 是否为空, 后判断 ptr 所指是否为 0, 然后指向下一个对象
ival++ && ival            // 先判断 ival 是否为 0 然后递增, 后判断 递增后的 ival 是否为 0
vec[ival++] <= vec[ival]  // 错误, 求值顺序未定义 改为 vec[ival] <= vec[ival+1]; ival++;
```

# 4.20 运算符优先级
> 假设iter的类型是vector\<string>::iterator, 说明下面的表达式是否合法。如果合法，表达式的含义是什么？如果不合法，错在何处？
```c++
// 优先级从高到低
// 左结合: ->, ., () 
// 左结合: a++
// 右结合: ++a, *a, &a, !a, ~a

(a) *iter++;          // 先 ++ 再 *  (正确, 相当与访问当前元素后迭代器 + 1)
(b) (*iter)++;        // 先 *  再 ++ (错误, string 无 后置++)
(c) *iter.empty();    // 先 .  再 *  (错误, bool无法被解引用)
(d) iter->empty();    // 先 -> 再 () (正确, 判断 string 元素是否为空)
(e) ++*iter;          // 先 *  再 ++ (错误, string 无 前置 ++ )
(f) iter++->empty();  // 先 -> 再 (), 再 ++ (正确, 判断 string 元素是否为空 后 指向下一个元素)
```

# 4.24 三目运算符结合律
> 本节的示例程序将成绩划分为high pass、pass、和fail三种，它的依据是条件运算符满足右结合律。假如条件运算符满足的是左结合律，求值的过程将是怎样的？
```c++
finalgrade = (grade > 90) ? "high pass" : (grade < 60) ? "fail" : "pass"; 
// 如果满足左结合律 以上逻辑变为如下
// grade  > 90 -> "high pass" -> "fail"
// grade <= 90  && grade < 60 -> "fail"
// grade <= 90 && grade >= 60 返回 "pass"
```

# 4.30 sizeof
> 根据4.12节中的表，在下述表达式的适当位置加上括号，使得加上括号之后的表达式的含义与原来的含义相同。
```c++
// sizeof 与 + 同级, 右结合
(a) sizeof x + y      // (sizeof(x)) + y
(b) sizeof p->mem[i]  // sizeof(p->mem[i])
(c) sizeof a < b      // sizeof(a)< b
(d) sizeof f() 		  // sizeof(f())
```

# 4.33 三目运算符与逗号运算符
> 根据4.12节中的表说明下面这条表达式的含义。
```c++
(someValue ? ++x, ++y : --x) , --y
// 逗号优先级最低, 左结合 
// 如果 someValue 为真, 递增 x, y, 否则 someValue 为假, 递减 x
// 最后 递减 y
```

# 4.37 强制类型转换
> 用命名的强制类型转换改写下列旧式的转换语句。
```c++
int i; double d; const string *ps; char *pc; void *pv;

// 1. pv = (void*) ps; 
pv = reinterpret_cast<void*>(const_cast<string*>(ps));
// 2. i = (int) *pc;
i = static_cast<int>(*pc);
// 3. pv = &d;
pv = reinterpret_cast<void*>(&d);
// 4. pc = (char*) pv;
pc = reinterpret_cast<char*>(pv);
```