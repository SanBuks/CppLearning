# 1. 语句与控制流
## 1.1 基本概念
- 复合语句(块) : 由一组语句组成的语句序列
- 块中的 static 变量 : 在控制流第一次到达时进行第一次也是唯一一次初始化, 生命周期一直持续到程序结束
- 空语句/空块 : 添加注释提示读者
- 悬垂 else 问题 : 规定 else 与最近尚未匹配的 if 匹配, 一般用花括号划分区域

## 1.2 switch
```c++
// 1. expr 计算值后 转换为 整型
case expr : break  
// 2. case 后跟标签一定是整型常量表达式, 
//    如果多个标签的流程一致一般写在同一行
case '1': case '2': case '3' ... 
// 3. 一定写上 default 告诉读者已经考虑默认情况
//    空 default 标签 一定以 ';' 结尾 否则语法错误
default: 
  ; 
// 4. C++ 不允许控制流跳过变量初始化语句到该变量作用域的其他位置
//    这种情况经常发生在 switch 中, 一般用语句块括号解决
int main() {
  goto A;
  int a = 0;
	
A:
  a = 4;
// note : crosses initialization of ‘int a’
  return 0;
}
```

## 1.3 range for
```c++
for (declaration : expression) ...
// 1. expression 是序列, 可以通过迭代器进行访问 如 向量对象 vec
// 2. declaration 定义变量, 通过迭代器访问 如 const auto &e

// 等价于

// 3. init-statement 只能有一条声明语句, 通过逗号分割的变量的基础类型必须一致
for (auto it = begin(expression), ot = other()); it != end(expression); ++it)
  auto var = *it;
```

## 1.4 goto
```c++
void function() {
  // 1. 跳转范围必须在同一个函数中, label 的名字可以与一般标识符一致, 不受影响
  // 2. 跳过变量初始化语句 换句话说 从变量作用域之外跳到作用域之内 会出错
  goto end;    
  int x = 10;  // x 作用域
end:           // x 作用域
  x = 42;      // x 作用域
  
begin:
  int s =3;       // s 作用域
  do {            // s 作用域
    if (...) {    // s 作用域
      break;      // s 作用域
    } else {      // s 作用域
      // 3. 从变量作用域内跳转到作用域之外,不会报错, 会将作用域内的变量自动销毁
      goto begin; // s 作用域
    }             // s 作用域
  } while (true); // s 作用域
}
```

# 2. 异常处理
## 2.1 异常处理流程
- 寻找处理异常代码层层向上, 直到 terminate 处理的标准库函数
- 异常安全代码(非常困难) : 对象状态有效, 资源无泄漏, 程序处于合理状态 
```c++
try {
  throw runtime_error("err message");
} catch (exception e1) {
  // 返回 const char * 字符串
  std::cout << e1.what(); 
} catch (exception e2) {
  ...
}
// 出现错误处理完成后跳转到 ... 执行
...  
```

## 2.2 标准库异常
- \<exception> : 定义通常类 exception, 只能默认初始化
- \<new> : 定义 bad_alloc, 只能默认初始化
- \<type_info> : 定义 bad_cast, 只能默认初始化
- 只能默认初始化的异常类, what() 返回值由编译器决定
- \<stdexcept> : 必须提供初始值, 用 what() 查看具体错误信息, 包含 exception

| 异常类 | 异常描述 |
| --- | --- |
| runtime_error | 运行时异常 |
| range_error | 查出有意义值域的范围 |
| overflow_error / underflow_error | 溢出异常 |
| logic_error | 逻辑错误 |
| domin_error | 参数对应值不存在 |
| invalid_argumen | 参数无效 |
| length_error | 创建超过类型最大长度对象 |
| out_of_range | 超出有效值范围 |