# 第五章 语句
## 1. 语句与控制流
- 空语句 : 一般添加注释, 告诉读者用途
- 悬垂 else 问题 : 用花括号划分区域
- switch : 
```c++
case expr : break  //1. expr 计算值后转换为整型
case '1': case '2': case '3' ... // 2. case 后跟标签一定是整型常量表达式, 一致流程写法
default: ; // 3. 一定写上default 告诉读者已经考虑默认情况
// 4. 空 default 标签 一定以 ';' 结尾 否则语法错误

// 5. C++ 不允许控制流跳过变量初始化语句到该变量作用域的其他位置
int main(){
	goto A;
	int a = 0;
	
A:
	a = 4;
// note : crosses initialization of ‘int a’
	return 0;
}
```

- range for 语句
```c++
for(declaration:expression) ...
// 1. expression 是序列, 可以通过迭代器进行访问 如 向量对象 vec
// 2. declaration 定义变量, 通过迭代器访问 如 const auto &e

// 等价于

for(auto it = begin(expression); it != end(expression); ++it)
	auto var = *it;
```

## 2. 异常处理
- 异常处理流程 : 
```c++
try{
	throw runtime_error("err message");
}catch(exception e1){
	std::cout<<e1.what(); // 返回 const char * 字符串
}catch(exception e2){
	...
}
...  // 出现错误处理完成后跳转到...执行
```

- 寻找处理异常代码层层向上, 直到terminate处理的标准库函数

- `<stdexcept>` 定义一些异常类 :

| 异常类 | 异常描述 |
| --- | --- |
| exception | 通用异常\* |
| runtime_error | 运行时异常 |
| overflow_error / underflow_error | 溢出异常 |
| logic_error | 逻辑错误 |
| domin_error | 参数对应值不存在 |
| invalid_argumen | 参数无效 |
| length_error | 创建超过类型最大长度对象 |
| out_of_range | 超出有效值范围 |
| bad_alloc | `<new>`  分配异常错误\* |
| bad_cast | `<type_info>` dynamic_cast 转型错误\* |
> \* 无字符串构造函数, what() 返回值由编译器决定


