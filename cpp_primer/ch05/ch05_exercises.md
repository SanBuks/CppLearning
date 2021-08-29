# 5.03 逗号运算符
> 使用逗号运算符重写1.4.1节的while循环，使它不再需要块，观察改写之后的代码可读性提高了还是降低了。
```c++
int sum = 0, val = 1;
while(val < 10)
    sum += val, ++val;
// 可读性降低
```

# 5.08 悬垂else
> 什么是“悬垂else”？C++语言是如何处理else子句的？

悬垂else : 如何匹配if else 关键字
C++ 判断 if 与 最接近的 else 匹配

# 5.13 switch
> 下面显示的每个程序都含有一个常见的编码错误，指出错误在哪里，然后修改它们。
```c++
(a) unsigned aCnt = 0, eCnt = 0, iouCnt = 0;
    char ch = next_text();
    switch (ch) {
        case 'a': aCnt++;  // break;
        case 'e': eCnt++;  // break;
        default: iouCnt++;
    }
(b) unsigned index = some_value();
    switch (index) {
        case 1:
            int ix = get_value();  // 控制流程会跳过定义语句 , 加括号
            ivec[ ix ] = index;
            break;
        default:
            ix = ivec.size()-1;    // int ix = ivec.size() - 1; 加括号
            ivec[ ix ] = index;
    }
(c) unsigned evenCnt = 0, oddCnt = 0;
    int digit = get_num() % 10;
    switch (digit) {
        case 1, 3, 5, 7, 9:  // case 1: case 3: case 5 ...
            oddcnt++;
            break;
        case 2, 4, 6, 8, 10:
            evencnt++;
            break;
    }
(d) unsigned ival=512, jval=1024, kval=4096;
    unsigned bufsize;
    unsigned swt = get_bufCnt();
    switch(swt) {
        case ival:  // case 512 :  必须是整型常量表达式
            bufsize = ival * sizeof(int);
            break;
        case jval:
            bufsize = jval * sizeof(int);
            break;
        case kval:
            bufsize = kval * sizeof(int);
            break;
    }
```

# 5.18 do while 语句局部变量作用域
> 说明下列循环的含义并改正其中的错误。
```c++
(a) do   // 没有花括号
        int v1, v2;
        cout << "Please enter two numbers to sum:" ;
        if (cin >> v1 >> v2)
            cout << "Sum is: " << v1 + v2 << endl;
    while (cin);

(b) do {
        // . . .
    } while (int ival = get_response()); // 不允许在条件处定义控制变量

(c) do {  // 不允许在 do 循环体内定义控制变量, 出循环体就销毁
        ival = get_response();
    } while (ival); 
```
