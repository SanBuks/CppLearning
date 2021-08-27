# 第八章 IO库

## 1. IO类
### 1.1 继承体系

![cpp_stream_hierarchy](D:\Project\cpp_learning\ch08\image\cpp_stream_hierarchy.png)

- IO对象不可拷贝不可被赋值(深度拷贝, 同步, 缓冲等问题)
- 与 C stream 同步, 写数据前刷新 C stream, 反过来同理
- 提供并发保障

### 1.2 特殊类型 IO
- 数值 : 读入数字时必须开头否则设为0
- 布尔 : 输入输出默认均以数字表示, 否则发生错误
- 字符 : 默认跳过空白字符
- 字符指针 : 输入输出文字内容, 输入时跳过空白符直到读到空白符或EOF为止, 用 setw(80) 限制输入长度防止缓冲区溢出
- void\* : 输入输出某个指针值, 任何类型指针可以通过 `static_cast<void*>(xxx)` 转换

### 1.3 条件状态

![cpp_stream_iostate_interface](D:\Project\cpp_learning\ch08\image\cpp_stream_iostate_interface.png)

- 条件状态定义在 `ios_base` 中,  类型为 `iostate` 是掩码类型, `stream_buf` 可被多个 stream 共享因此不存在状态标志
- 条件状态只表示过去发生的事, 需要 clear() 或 保存操作前的状态作为对比, 才能判断后来发生的变化
- 条件非正常则不会改动输入对象

-------

- `rdstate()` 返回状态标志
- `setstate(iostate state)` 设置状态标志, 可以通过掩码位运算达到修改多个状态
- `clear(iostate state = ios_base::goodbit)` 修改状态标志 

### 1.4 异常





### 刷新输出缓冲
1. 正常程序结束
2. 缓冲区满
3. cout\<\<unitbuf (相反设置nounitbuf)
4. endl,ends,flush
5. 关联流读写
> 注意！程序崩溃缓冲区不会自动刷新

#### 关联输入和输出流
1. cin.tie() : 返回关联流的指针 或 空指针
2. cin.tie(&os) : 在绑定之前先返回关联流的指针 或 空指针

### 2. 文件流

#### 读写
1. fstream fs("filename") : 创建fs并以open方式打开本地目录下的filename文件
2. fs.open("filename") : 打开filename
3. fs.close() : 关闭绑定的文件 在析构时会自动调用
4. fs.is_open() : 判断是否打开且未关闭

#### 文件模式
1. out : 只能对 ofstream 或 fstream 设定, 且与trunc是默认打开模式 (in同理)
2. trunc : 前提设定 out (截断的意思是首先清空文件内容)
3. app :  前提 没有设定 trunc 
5. ate :   可以用于任意文件 打开文件后定位到末尾,
6. binary : 可以用于任意文件 以二进制方式打开
7. 一次设置多个模式的方式  : `ofstream ofs("filenma", ofstream::out | ofstream::trunc);` 

### 3. string流

#### 读写
1. stringstream strm(str) :  绑定str字符串
2. strm.str() : 返回string拷贝
3. strm.str(str1) : 替换strm所绑定的字符串

#### 

### 4. 例题
1. (8.1) 编写函数,接受一个istream&参数,返回istream&参数,读取数据打印在标准输出流中,遇到结束标识停止,返回前复位
```c++
istream& func(istream & is){
    string s;
    while(is>>s){
        cout<<s<<endl;
    }
    is.clear();
    return is；
}
```
2. (8.4&8.5) 编写函数,以读的方式打开文件,将一行/一个单词作为独立元素存于vector中
```c++
ifstream& func(ifstream & ifs, vector<string> svector){
    string s;
    if(ifs) cout<<"ifs is fail!"<<endl;
    while(getline(ifs,s)) // while(ifs>>s)
    // istream& getline (istream&  is, string& str, char delim); delim is extreacted and discarded 
    // istream& getline (istream&  is, string& str); delim='\n'
        svector.push_back(s);
    return ifs;
}
```

3. (8.11) 重写本节程序,将record的定义移到while循环之外,验证你设想的修改方法是否正确
```c++
// 注意,每一行之后是否有空白符留存对于读写有很大的影响,需要特别关注
struct PersonInfo{
    string name;
    vector<string> phones;
};
int main(int argc, char *argv[]){
    string line, word;
    vector<PersonInfo> people;
    ifstream ifs("input");
    istringstream record;
    if(ifs){
        while(getline(ifs, line)){
            PersonInfo info;
            record.str(line);
            record.clear();  // 恢复record状态位
            record>>info.name;
            while(record>>word){ 
// 用 good() 如果每一行不以空白符结尾则会最后一个数据没有读取
                info.phones.push_back(word);
            }
            people.push_back(info);
        }
    }
    // 将结果打印
    for(const auto & it : people){
        cout<<it.name<<ends;
        for(const auto & str : it.phones)
            cout<<str<<ends;
        cout<<endl;
    }
}
```
4. 重写本接电话号码程序,从一个命名文件而非cin读取数据
```c++
struct PersonInfo{
    string name;
    vector<string> phones;
};

bool valid(const string &s){  // 合格号码:10个任意数字
    if(s.size()!=10) return false;
    for(const auto & c : s){
        if(c>'9'||c<'0')
            return false;
    }
    return true;
}
int main(int argc, char *argv[]){
    string line, word;
    vector<PersonInfo> people;
    ifstream ifs("input");
    istringstream record;
    if(ifs){
        while(getline(ifs, line)){
            PersonInfo info;
            record.str(line);
            record.clear();
            record>>info.name;
            while(record>>word){ 
                info.phones.push_back(word);
            }
            people.push_back(info);
        }
    }
    for(const auto & entry : people){
        ostringstream formatted, badNums;  // 存放 正确号码 和 错误号码
        for(const auto & nums : entry.phones)
            if(!valid(nums)) 
                badNums<<" "<<nums;
            else 
                formatted<<" "<<nums;    
        if(badNums.str().empty()){
            cout<<entry.name<<" "
            <<formatted.str()<<endl;            
        }else{
            cerr<<"number error: "<<entry.name
                <<" invalid numbers: "<<badNums.str()<<endl;
        }
    }
}
```