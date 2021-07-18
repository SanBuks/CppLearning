# 6. 例题
1. (9.12) 对于接受一个容器创建其拷贝的构造函数,和接受两个迭代器创建拷贝的构造函数,解释它们的不同
- 接受容器进行拷贝构造需要容器类型相同,元素类型相同
- 接受迭代器进行拷贝构造容器类型可以不同,元素类型可以转换即可,后者有更强的普适性
2. (9.13)如何从一个list\<int>初始化一个vector\<double> 和 vector\<int> ? 
    ```c++
    int main(){ 
        list<int> list1{1,2,3,4};
        vector<double> vector1(list1.cbegin(),list1.cend());
        vector<int> vector2(list1.cbegin(),list1.cend());
    
        for(const auto &e : vector1) cout<<e<<" ";
        cout<<"\n";
        for(const auto &e : vector2) cout<<e<<" ";
        cout<<"\n";
        return 0;
    }
    ```
    
3. (9.14)将一个list中的char * 指针元素赋值给一个vector中的string
	```c++
    int main(){ 
        char *a="1230";
        char *b="1222";
		list<char *> vec2{a,b};        
		vector<string> vec1; // 或...vec1{vec2.cbegin(),vec2.cend()};
        vec1.assign(vec2.cbegin(),vec2.cend());
        for(const auto &e : vec1) cout<<e<<"\n";
        return 0;
    }
	```
	
4. (9.22)假定iv是一个int的vector, 对下列错误程序进行修改
	```c++
	int main(){
    	vector<int> iv={1,2,3,4,5,6,7};
    	auto it=iv.begin();
    	int mid=iv.size()/2;  
    	while(it!=iv.begin()+mid)
        	if(*it!=9){  
            	it=iv.insert(it, 2*9);  // 更新遍历的迭代器
            	it+=2;  // 跳过插入和判定的元素
            	mid++;  // 始终以原来的中点为基准
        	}
        for(const auto &it : iv)
            cout<<it<<" ";
	}
	```
	
5. (9.26)使用下面代码定义的ia, 将ia拷贝到一个vector和一个list中, 使用但迭代器版本的erase从list中删除奇数元素, 从vector中删除偶数元素.
	```c++
	int main(){
        int ia[]={0,1,1,2,3,5,8,12,21,55,89}; 
        list<int> eve(begin(ia), end(ia)); 
        vector<int> odd(begin(ia), end(ia));
        for(auto it=eve.begin(); it!=eve.end(); ++it)
            if(!(*it%2)){
                it=eve.erase(it);
                --it;
            }
	
        for(auto it=odd.begin(); it!=odd.end(); ++it)
            if(*it%2){
                it=odd.erase(it);
                --it;
            }    
	
        for(const auto &it : eve) cout<<it<<" ";
        cout<<endl;
        for(const auto &it : odd) cout<<it<<" ";
        return 0;
    }
	```
	
6. (9.28)编写函数,接受一个forward_list\<string>和两个string共三个参数,函数在链表中查找第一个string,并将第二个string插入到紧接着第一个string之后.若第一个string未在链表中,则将第二个string插入到链表末尾.
	```c++
	void func(forward_list<string> &fl, const string &s1, const string &s2){
        if(fl.begin()==fl.end()) { // 查看是不是空链表
            fl.insert_after(fl.before_begin(), s2); 
            return; 
        }
        auto pit=fl.before_begin();  // 前驱迭代器
        auto it=fl.begin();  // 遍历迭代器
        while(it!=fl.end()){
            if(*it==s1){
                fl.insert_after(it,s2);
                return ;
            }else{
                ++it;
                ++pit;
            }
        }
        fl.insert_after(pit,s2);
    }
	
	```
7. (9.43)编写一个函数,接受三个string参数s, oldval和newval.使用迭代器及insert和erase函数将s中所有oldval替换为newval(或者用下标和replace函数)测试你的程序用他替换通用的简写形式.
	```c++
	void o2n_iter(string &s, const string &oldval, const string &newval){
        for(auto it=s.begin(); it!=s.end(); ++it){
            if(*it==oldval[0]){  // 第一个字符相等进一步判断
                string::iterator pos=it; // 保留原始的位置
                auto ir=oldval.begin();  
                while(ir!=oldval.end()&&it!=s.end()){  // 遍历子串
                    if(*ir!=*it){  // 不等则退出循环
                        break;
                    }else{
                        ++ir;
                        ++it;
                    }
                }
                if(ir==oldval.end()){  // 判断是否完全匹配
                    pos=s.erase(pos, pos+oldval.size());
                    // erase(b, e)
                    s.insert(pos, newval.begin(), newval.end());
                    // insert(p, b, e)
                    return ;
                }else{  // 不匹配回到原来位置
                    it=pos;
                }
            }
        } 
    }
    
    void o2n_sub(string &s, const string &oldval, const string &newval){
        for(size_t i=0; i!=s.size(); ++i){
            if(s[i]==oldval[0]){
                size_t pos=i;
                size_t j=0;
                while(i!=s.size()&&j!=oldval.size()){
                    if(s[i]!=oldval[j]){
                        break;
                    }else{
                        ++i;
                        ++j;
                    }
                }
                if(j==oldval.size()){
                    s.replace(pos, oldval.size(), newval);
                    // replace(pos, n, str)
                    return;          
                }else{
                    i=pos;     
                } 
            }
        }
    }
	```
7. (9.49)读入一个单词文件,输出最长的不含上出头部分和下出头部分的单词
	```c++
    int main(){
        string outline="bdfghijklpqty";
        string word, maxword;
        fstream fs("./input");
        while(fs){
            fs>>word;
            if(word.find_first_of(outline)==string::npos && word.size()>maxword.size())
                maxword=word;
        }   
        cout<<maxword<<" lenth is "<<maxword.size()<<endl;
        return 0;
    }
	```

7. (9.52)使用stack处理括号表达式
    ```c++
	// test.h
    #include <iostream>
    #include <stack>
    #include <vector>
    #include <cmath>
    #include <cstdlib>
    
    using namespace std;
    const int N_OPT=9;
    typedef enum{ NON=-1, ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator;
    
    const char pri[N_OPT][N_OPT]={    // 操作符优先级表
    // 			+	-	*	/	^	!	(	)	\0
    /* + */    '>','>','<','<','<','<','<','>','>',
    /* - */    '>','>','<','<','<','<','<','>','>',
    /* * */    '>','>','>','>','<','<','<','>','>',
    /* / */    '>','>','>','>','<','<','<','>','>',
    /* ^ */    '>','>','>','>','<','<','<','>','>',
    /* ! */    '>','>','>','>','>','>',' ','>','>',
    /* ( */    '<','<','<','<','<','<','<','=',' ',
    /* ) */    ' ',' ',' ',' ',' ',' ',' ',' ',' ',
    /* \0*/    '<','<','<','<','<','<','<',' ','='
    };
    
    void readNumber(const char * &p, stack<double, vector<double>> &opn){ // 读取数字
        opn.emplace(*p-'0');	
        while(isdigit(*++p))
            opn.top()=opn.top()*10+*p-'0';
        if(*p!='.') return ;  // 不含小数则直接返回
        double pro=0.1;
        while(isdigit(*++p)){
            opn.top()+=(*p-'0')*pro;
            pro/=10;
        }
    }
    
    Operator c2i(char op){  // 字符转数字
        switch(op){
            case '+' : return ADD;
            case '-' : return SUB;
            case '*' : return MUL;
            case '/' : return DIV;
            case '^' : return POW;
            case '!' : return FAC;
            case '(' : return L_P;
            case ')' : return R_P;
            case '\0' : return EOE; 
            default : exit(2); 
        }
    }
    
    char orderBetween(char op1, char op2){  // 返回栈顶操作符与当前操作符的优先级关系
        return pri[c2i(op1)][c2i(op2)];
    }
    
    double calcu(double opn, char op){  // 计算一元操作符
        switch(op){
            case '!' : {
                if(opn!=(unsigned int)opn) exit(2);
                opn=(unsigned int) opn;
                double result=1.0;
                while(opn){
                    result*=opn;
                    --opn;
                }
                return result;
            }
            default : exit(2);
        }
    }
    
    double calcu(double opn1, char op, double opn2){  // 计算二元操作符
        switch(op){
            case '+' :  return opn1+opn2;
            case '-' : 	return opn1-opn2;	
            case '*' : 	return opn1*opn2;
            case '/' : 	if(abs(opn2-0)<0.0001)	exit(3);
                        else return opn1/opn2;
            case '^' : 	return pow(opn1, opn2);
            default : exit(2);
        }
    }
    
    // test.cpp
    #include "test.h"
    
    int main(){
        stack<char, vector<char>> opt;  // 操作符栈
        stack<double, vector<double>> opn;  // 操作数栈
        opt.push('\0');  // 压入基础操作符
        const char *p="((0+(1+23)/4*5*67-8+9))*10.00+5!";
        while(!opt.empty()){
            if(isdigit(*p))  // 读取数字
                readNumber(p, opn);
            else{  // 处理操作符
                switch(orderBetween(opt.top(), *p)){
                    case '<' : 	opt.push(*p); ++p; break;  // 优先级小则压入
                    case '=' :	opt.pop(); ++p; break;  // 匹配直接弹出
                    case '>' :	{  // 优先级大则处理
                        char op=opt.top(); opt.pop();
                        double opn1, opn2, result;
                        if(op=='!'){  // 一元操作符
                            opn1=opn.top(); opn.pop();
                            result=calcu(opn1, op);
                            opn.push(result);
                        }else{  // 二元操作符
                            opn2=opn.top();	opn.pop();
                            opn1=opn.top(); opn.pop();
                            result=calcu(opn1, op, opn2);
                            opn.push(result);
                        }
                        break;
                    }
                    default : exit(2);
                }
            }
    
        }
        cout<<opn.top();
        return 0;
    }	
    ```