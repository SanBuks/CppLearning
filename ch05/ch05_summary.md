# 第五章 语句
## 1. 语句与控制流
- 空语句 : 一般添加注释, 告诉读者用途
- 悬垂 else 问题 : 用花括号划分区域
- switch : 
```c++
case expr : break  //1. expr 是整型常量表达式
case '1': case '2': case '3' ... // 2. 一致流程写法
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

- \<stdexcept>定义一些异常类


- exception
- runtime_error
- logic_error
- bad_alloc


(5.12) 统计元音,空白符,ff,fl,fi字符的各自数量
```c++
int main(){
    string str;
    const string str_vowel="aAeEIiOoUu";
    const string fli="fli";
    if(cin>>str){
          int vowel=0, space=0, fword=0;
          auto it=cbegin(str);
          while(it!=end(str)){
             if(str_vowel.find(*it)<str_vowel.size())  //str.find() 返回-1(maxiumn of size_type)/位置
                vowel++;
             else if(isspace(*it)) 
             //tab (\t) whitespaces (\n, \v, \f, \r) space 
                space++;
             else if(*it=='f'&&(it+1)!=end(str)&&fli.find(*(it+1))<fli.size()){
             // 第一个字符是否为f ， 第二个字符是否存在 ， 第二个字符是否是fli中的字符
                if(*(it+1)=='i') // 判断三个单词中是否包含元音字符
                      vowel++;
                fword++;
                it++;  // 多移动一格
             }
             it++;
          }
          cout<<"sum: "<<str.size()<<endl;
          cout<<"vowel: "<<vowel<<endl;
          cout<<"space: "<<space<<endl;
          cout<<"fword: "<<fword<<endl;
          return 0;
    }
    cerr<<"no text!";
    return -1;
}
```
3. (5.17) 判断一个vector对象是否为另一个vector对象的前缀
```c++
 template<typename T>
 bool is_prefix(const vector<T> &vec1,const vector<T> &vec2){
    for(auto it1=cbegin(vec1),it2=cbegin(vec2);it1!=end(vec1)&&it2!=end(vec2);++it1,++it2)
          if(*it1!=*it2)
             return false;
    return true;
 }
```
4. (5.25) 用try-catch语句写出输入2个数相除处理除数为0的情况
```c++
int main(){
    int e1,e2;
    while(cin>>e1>>e2){
          try{
             if(!e2) throw runtime_error("number can't be divided by 0!\n");
             cout<<static_cast<double>(e1)/e2<<endl;
          }catch(exception e){
             cout<<e.what()<<"want to try again?y/n\n";
             char c; cin>>c; 
             if(!cin||c=='n')
                break;
          }
    }
    return 0;
}
```