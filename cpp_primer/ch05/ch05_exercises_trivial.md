# 5.01
> 什么是空语句？什么时候会用到空语句？

空语句是只含分号的语句, 用于循环体

# 5.02
> 什么是块？什么时候会用到块？

块是一个作用域, 用花括号括起来的语句序列, 一般循环体要用到

# 5.04
> 说明下列例子的含义，如果存在问题，试着修改它。
```c++
while (string::iterator iter != s.end()) { /* . . . */ }
// 没有对控制变量进行修改, 死循环
while(iter!=s.end()){
    ...
    ++iter;
}

while (bool status = find(word)) { /* . . . */ } 
    if (!status) { /* . . . */ } // 不在作用域内

while (bool status = find(word)){
    if (!status) { /* . . . */ }
}
```

# 5.05
> 写一段自己的程序，使用if else语句实现把数字转换为字母成绩的要求。
```c++
const vector<string> level = { "F", "D", "C", "B", "A", "A++"};

std::string gradeDiv(unsigned score){
	if(score > 100) throw std::runtime_error("invalid score!");
	string result;
	if(score < 60) result = level[0];
	else result = level[score/10-5];

	if(score != 100){
		if(score % 10 > 7) result += "+";
		if(score % 10 < 3) result += "-";
	}
	return result;
}
```

# 5.06
> 改写上一题的程序，使用条件运算符代替if else语句。
```c++
std::string gradeDiv(unsigned score){
	if(score > 100) throw std::runtime_error("invalid score!");
	string result;
	(score < 60) ? result = level[0] : result = level[score/10-5];
	if(score != 100)
		result += (score % 10 > 7) ? "+" : (score % 10 < 3) ? "-" : "";
	return result;
}

```

# 5.07
> 改写下列代码段中的错误。
```c++
(a) if (ival1 != ival2) 
		ival1 = ival2   // 缺分号
    else 
    	ival1 = ival2 = 0;

(b) if (ival < minval)  // 缺括号
		minval = ival;
    	occurs = 1;

(c) if (int ival = get_value())
    	cout << "ival = " << ival << endl;
    if (!ival)          // ival是局部变量 
    	cout << "ival = 0\n";

(d) if (ival = 0)       // if(0 == ival)
    	ival = get_value();
```

# 5.09
> 编写一段程序，使用一系列if语句统计从cin读入的文本中有多少元音字母。
```c++
void countChar(ifstream &ifs){
	char c;
	int numA , numE , numI , numO , numU , numOther; 
	numA = numE = numI = numO = numU = numOther = 0;

	while(ifs>>c){
		switch(c){
			case 'a':
				++numA;
				break;
			case 'e':
				++numE;
				break;
			case 'i':
				++numI;
				break;
			case 'o':
				++numO;
				break;
			case 'u':
				++numU;
				break;
			default :
				++numOther;
		}
	}
	cout<<"number of a : "<<numA<<endl;
	cout<<"number of e : "<<numE<<endl;
	cout<<"number of i : "<<numI<<endl;
	cout<<"number of o : "<<numO<<endl;
	cout<<"number of u : "<<numU<<endl;
	cout<<"number of other : "<<numOther<<endl;
}
```

# 5.10
> 我们之前实现的统计元音字母的程序存在一个问题：如果元音字母以大写形式出现，不会被统计在内。编写一段程序，既统计元音字母的小写形式，也统计元音字母的大写形式，也就是说，新程序遇到'a'和'A'都应该递增aCnt的值，以此类推。
```c++
void countChar(ifstream &ifs){
	char c;
	int numA , numE , numI , numO , numU , numOther; 
	numA = numE = numI = numO = numU = numOther = 0;

	while(ifs>>c){
		switch(c){
			case 'A': case 'a':
				++numA;
				break;
			case 'E': case 'e':
				++numE;
				break;
			case 'I': case 'i':
				++numI;
				break;
			case 'O': case 'o':
				++numO;
				break;
			case 'U': case 'u':
				++numU;
				break;
			default :
				++numOther;
		}
	}
	cout<<"number of a : "<<numA<<endl;
	cout<<"number of e : "<<numE<<endl;
	cout<<"number of i : "<<numI<<endl;
	cout<<"number of o : "<<numO<<endl;
	cout<<"number of u : "<<numU<<endl;
	cout<<"number of other : "<<numOther<<endl;
}
```

# 5.11
> 修改统计元音字母的程序，使其也能统计空格、制表符、和换行符的数量。
```c++
void countChar(ifstream &ifs){
	char c;
	int numA , numE , numI , numO , numU , numSpace , numLF , numVHT , numOther; 
	numA = numE = numI = numO = numU = numSpace = numLF = numVHT = numOther = 0;
    // basic_istream& get(char_type& ch);
	while(ifs.get(c)){
		switch(c){
			case 'A': case 'a':
				++numA;
				break;
			case 'E': case 'e':
				++numE;
				break;
			case 'I': case 'i':
				++numI;
				break;
			case 'O': case 'o':
				++numO;
				break;
			case 'U': case 'u':
				++numU;
				break;
			case ' ':
				++numSpace;
				break;
			case '\n': 
				++numLF;
				break;
			case '\v': case '\t':
				++numVHT;
				break;
			default :
				++numOther;
		}
	}
	cout<<"number of a : "<<numA<<endl;
	cout<<"number of e : "<<numE<<endl;
	cout<<"number of i : "<<numI<<endl;
	cout<<"number of o : "<<numO<<endl;
	cout<<"number of u : "<<numU<<endl;
	cout<<"number of other : "<<numOther<<endl;
	cout<<"number of space : "<<numSpace<<endl;
	cout<<"number of LF : "<<numLF<<endl;
	cout<<"number of VHT : "<<numVHT<<endl;
}
```

# 5.12
> 修改统计元音字母的程序，使其能统计含以下两个字符的字符序列的数量：ff、fl和fi。
```c++
void countChar(ifstream &ifs){
	char c;
	int numFi, numFl, numFf;
	numFi = numFl = numFf = 0;
	while(ifs.get(c)){
		if(c=='f'){
			if(ifs.get(c)){
				switch(c){
					case 'i':
						++numFi;
						break;
					case 'l':
						++numFl;
						break;
					case 'f':
						++numFf;
						break;
					default :
						;
				}
			}
		}
	}
	cout<<"number of fi : "<<numFi<<endl;
	cout<<"number of fl : "<<numFl<<endl;
	cout<<"number of ff : "<<numFf<<endl;
}
```

# 5.14
> 编写一段程序，从标准输入中读取若干string对象并查找连续重复出现的单词，所谓连续重复出现的意思是：一个单词后面紧跟着这个单词本身。要求记录连续重复出现的最大次数以及对应的单词。如果这样的单词存在，输出重复出现的最大次数；如果不存在，输出一条信息说明任何单词都没有连续出现过。 例如：如果输入是：
how now now now brown cow cow
那么输出应该表明单词now连续出现了3次。
```c++
void showDupliWord(ifstream &ifs){
	bool exists = false;
	int maxTimes = 0;
	string word, currWord, resultWord;
	if(ifs>>currWord){
		int times = 1;
		while(ifs>>word){
			if(word == currWord){
				++times;
				exists = true;
			}
			else{
				if(times > maxTimes){
					maxTimes = times;
					resultWord = currWord;
				}
				currWord = word;
				times = 1;
			}
		}
	}else{
		cout<<"can't open file!\n";
		return;
	}

	if(exists)
		cout<<resultWord<<" : "<<maxTimes;
}
```

# 5.15
>说明下列循环的含义并改正其中的错误。
```c++
(a) for (int ix = 0; ix != sz; ++ix) { /* ... */ }
    if (ix != sz) // 没有在循环体内
    	// . . .

(b) int ix;
    for (ix != sz; ++ix) { /* ... */ }  // 少写初识化语句

(c) for (int ix = 0; ix != sz; ++ix, ++sz) { /*...*/ } // 可能产生死循环
```

# 5.16
> while循环特别适用于那种条件不变、反复执行操作的情况，例如，当未达到文件末尾时不断读取下一个值。 for循环更像是在按步骤迭代，它的索引值在某个范围内一次变化。根据每种循环的习惯各自编写一段程序，然后分别用另一种循环改写。 如果只能使用一种循环，你倾向于哪种？为什么？

按情况选择使用

# 5.17
> 假设有两个包含整数的vector对象，编写一段程序，检验其中一个vector对象是否是另一个的前缀。 为了实现这一目标，对于两个不等长的vector对象，只需挑出长度较短的那个，把它的所有元素和另一个vector对象比较即可。 例如，如果两个vector对象的元素分别是0、1、1、2 和 0、1、1、2、3、5、8，则程序的返回结果为真。
```c++
bool isPrefix(const vector<int> &vecA, const vector<int> &vecB){
	if(vecA.size() <= vecB.size()){
		for(size_t i = 0; i != vecA.size(); ++i)
			if(vecA[i] != vecB[i])
				return false;
		return true;
	}else 
		return isPrefix(vecB, vecA);
}


int main(){

	vector<int> a{ 0, 2, 1, 2 };
	vector<int> b{ 0, 1, 1, 2, 3, 5, 8 };
	cout<<isPrefix(a, b)<<endl; 

	vector<int> c{ 0};
	vector<int> d{ 0, 1, 1, 2, 3, 5, 8 };
	cout<<isPrefix(d, c)<<endl; 

	return 0;
}
```

# 5.19
> 编写一段程序，使用do while循环重复地执行下述任务： 首先提示用户输入两个string对象，然后挑出较短的那个并输出它。
```c++
void showShortStr(){
	do{
		string str1, str2;
		cout<<"Enter two string\n";
		if(cin>>str1>>str2)
			str1.size()<str2.size() ? cout<<str1 : cout<<str2;
		cout<<endl;
	}while(cin);
}
```

# 5.20
> 编写一段程序，从标准输入中读取string对象的序列直到连续出现两个相同的单词或者所有的单词都读完为止。 使用while循环一次读取一个单词，当一个单词连续出现两次时使用break语句终止循环。 输出连续重复出现的单词，或者输出一个消息说明没有任何单词是连续重复出现的。
```c++
string currWord, word;
bool duplicated = false;
if(cin>>currWord){
    while(cin>>word){
        if(word == currWord){
            duplicated = true;
            break;
        }else
            currWord = word;
    }
}
if(duplicated) cout<<"duplicated word is "<<currWord;
else cout<<"no duplicated word";
```

# 5.21
> 修改5.5.1节练习题的程序，使其找到的重复单词必须以大写字母开头。
```c++
string currWord, word;
bool duplicated = false;
if(cin>>currWord){
    while(cin>>word){
        if(word == currWord && !word.empty() && word[0] <= 'Z' && word[0] >= 'A'){
            duplicated = true;
            break;
        }else
            currWord = word;
    }
}
if(duplicated) cout<<"duplicated word is "<<currWord;
else cout<<"no duplicated word";
```


# 5.22
> 本节的最后一个例子跳回到begin，其实使用循环能更好的完成该任务，重写这段代码，注意不再使用goto语句。
```c++
int sz = get_size();
while(sz <= 0)
	sz = get_size();
```

# 5.23
> 编写一段程序，从标准输入读取两个整数，输出第一个数除以第二个数的结果。

# 5.24
> 修改你的程序，使得当第二个数是0时抛出异常。先不要设定catch子句，运行程序并真的为除数输入0，看看会发生什么？

# 5.25
> 修改上一题的程序，使用try语句块去捕获异常。catch子句应该为用户输出一条提示信息，询问其是否输入新数并重新执行try语句块的内容。
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