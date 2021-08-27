# 第十章 泛型算法

### 1. 概述 
- 泛型算法 不会改变容器的元素个数,但是会改变元素的值和次序,同时依赖元素的类型的操作,头文件一般为 `<algorithm> <numeric>`
|算法型参模式|解释|
|---|---|
|alg(b,e,args)|[b,e)表示范围|
|alg(b,e,b2,args)|b2表示输出范围开始位置|
|alg(b,e,b2,e2,args)|[b2,e2)表示输出范围|
|alg(b,e,pre)|表示在范围中调用谓词|
|alg_if(b,e,pre)|用谓词替代原来的(b,e,val)|
|alg_copy(b,e,dest)|将结果拷贝到dest中|
> dest一般表示插入迭代器用于 \*it=var , 上述几种模式可以组合

- 泛型算法的范围可以用 con.cbegin(), begin(array), 内置数组pointer指定,规定第二个范围规定第二个序列至少与第一个一样长,否则未定义


### 2. 算法列表
|算法参数|返回值|注意事项|
|---|---|---|
|find(cit1,cit2,val)|返回指向第一个等于val的迭代器或cit2|调用==,存在find_if|
|count(cit1,cit2,val)|返回给定值出现的个数|调用==|
|accumulate(cit1,cit2,sum)|返回sum作为初始值的累加|调用sum类型的+|
|equal(cit1,cit2,cit11)|判断两个序列是否相同|调用==|
|fill(it1,it2,val)|将val赋予范围元素|调用=|
|fill_n(it1,n,val)|从it1开始将val赋予给n个元素|调用=,容器不为空或不足|
|fill_n(back_insert(vec),n,val)|和插入迭代器结合添加n个val新元素|调用=|
|copy(it1,it2,it11)|将第一范围元素拷贝到it11开始范围中,返回it22迭代器|调用=|
|replace(it1,it2,val1,val2)|将范围中val1元素替换成val2|调用=,存在replace_copy|
|unique(it1,it2)|对已排序的序列消除重复元素,返回不重复范围尾后迭代器|调用==|
|(stable\_)sort(it1,it2(,pre2))|从小到大排序|调用<,或者调用谓词|
|(stable\_)partition(it1,it2,pre1)|划分容器元素,满足谓词排在前面返回尾后|调用谓词|
|for_each(it1,it2,pre1)|对范围内每个元素进行操作|调用谓词|
|transform(it1,it2,it11,pre1)|将范围内每个元素操作后结果赋予第二个范围|调用谓词|


### 3. lambda表达式
- 可调用对象包括函数,函数指针,重载调用运算符的类和lambda表达式
- 谓词可理解为可调用对象作为函数参数执行某个动作,返回一个可以作用条件的值,按可调用对象的参数可分为一元谓词和二元谓词 
- lambda表达式表示一个可调用代码单元,一个未命名的内联函数
```c++
auto it=[capture_list] (parameter_list) mutable -> return_type {....};
// 定义一个有名的lambda对象
auto it=[](){return 42;};
// 最简洁写法 空参, 空捕获, 根据返回值推测返回类型
```
- lambda表达式函数体中如果有return语句之外的内容则返回void或者置尾指明返回类型
- lambda表达式不含有默认实参,实参与型参数目相同,只捕获局部指明的变量,static和函数体外对象不用捕获
- 传递lambda表达式的时候就定义了一个新类型和该对象,与此同时包含了值捕获和引用捕获
|捕获形式|捕获规则|
|---|---|
|[&var1,var2...]|指定捕获形式|
|[&/=]|默认所有局部变量隐捕或者值捕|
|[&,var1,var2...]|混合捕获|
|[=,&var1,var2...]|混合捕获|
> 引用捕获注意绑定的对象是否存在,尽量避免捕获指针或者引用, lambda作为对象返回时不能由引用捕获,mutable可以使值捕获改变原来的值

### 4. 参数绑定
- bind函数定义在`<functional>`中,接受可调用对象,生成新的可调用对象,绑定参数后新的可调用对象型参变少,可以作为算法谓词,参数绑定与lambda表达式捕获类似,但是可以方便复用
- `_n`是站位符,定义在std::placeholders 命名空间中,代表原来第n个参数,`auto g=bind(f,a,b,c,_2,_1)后调用g(X,Y) 等价调用 f(a,b,c,Y,X)`
- 如果要引用绑定则需要ref()或cref()函数如 `bind(f,ref(os),_1)`
```c++
bool check_size(const string &s, string::size_type sz){  // 多一个参数sz不可作为一元谓词
	return s.size()>=sz;
}
int SZ=3;
auto newcallable=bind(check_size, _1, SZ);
// 等价于调用了 check_size(const string &s); 其中sz默认绑定为了SZ
auto it=find_if(vec.begin(),vec.end(), newcallable);  // 可以作为一元谓词
```

### 5. 迭代器
#### 插入迭代器
```c++
auto it1=back_insert(vec); // 返回vec的后端插入迭代器 vec支持push_back
auto it2=front_insert(vec); // 返回vec的前端插入迭代器 vec支持push_front
auto it3=inserter(vec,vec.begin()); // 返回vec的从vec.begin()顺序插入迭代器
```

#### 反向迭代器
- forward_list 和 流迭代器不支持迭代器递减 不支持反向迭代器
- vec.rbegin() 指向 最后元素 vec.rend() 指向 首前位置 it++ 移动到前一个位置 it-- 相反
- it.base() 转换为正常迭代器 注意指向的是it的后一个位置

#### 迭代器类别
- 每个算法要求迭代器的最低操作支持不同,注意算法的迭代器种类(编译器有时不会给出警告)
- 每个容器的迭代器种类也不一样,如 list 双向, vector,array,deque,string随机, 
|迭代器|功能|支持的操作|算法举例|
|---|---|---|---|
|输入迭代器|只读,单遍扫描,只能递增|==,!=,++,var=\*it,var=it->m|find,accumulate|
|输出迭代器|只写,单遍扫描,智能递增|++,\*it=var|copy,ostream_iterator|
|前向迭代器|读写,多遍扫描,只能递增|输出与输入操作|replace|
|双向迭代器|读写,多遍扫描,能递增减|输出与输入操作,--|reverse|
|随机访问迭代器|读写,躲遍扫描,能递增减|双向操作,<,<=,>,>=,[],it+=n,it1-it2|sort|

### 6. 特定容器算法
- 对于链表一类的容器,其迭代器类别不是随机访问迭代器,通用版本算法会造成过高代价,因此定义了几种特殊算法,这几中算法会改变容器
|算法|注意事项|
|---|---|
|lst.merge(lst2(,pre)|将有序的lst2移动合并到有序的lst中,<可替换为pre|
|lst.remove(val)|删除==val的元素,val可替换为pre|
|lst.reverse()|反转|
|lst.sort()|排序的元素,<可替换为pre|
|lst.unique()|唯一化排序的列表,==可替换为pre|
|lst.splice(p,lst2)|将lst2所有元素按原顺序移动到p之前的位置,两个链表类型相同且不是同一个|
|lst.splice(p,lst2,p2)|将lst2从p2开始的元素按原顺序移动到p之前的位置,可以是相同链表|
|lst.splice(p,lst2,b,e)|将lst2[b,e)范围元素按原顺序移动到p之前的位置,p不在范围中,可以是相同链表|
|lst.splice_after(args)|移动到p之后,args同上|

### 7. 例题
1. (10.19&10.25) 用stable_partition重写biggies函数(用check_size和bind重写)
```c++
using namespace std::placeholders;
bool check_size(const string &s, string::size_type sz){
	return s.size()>=sz;
}
void biggies(vector<string> &vec, vector<string>::size_type sz){
	sort(vec.begin(), vec.end());
	auto iterase=unique(vec.begin(), vec.end());
	vec.erase(iterase, vec.end());  // 去重
	stable_sort(vec.begin(), vec.end(), 
		[](const string &s1, const string &s2){ return s1.size()<s2.size(); });  // 按长度排序

	auto it=stable_partition(vec.begin(), vec.end(),
		[sz](const string &s1){ return s1.size()>sz; });  // 划分长度
	//	auto it=stable_partition(vec.begin(), vec.end(), bind(check_size, _1, sz)); // bind 重写
	int size=it-vec.begin();
	cout<<"count of word whose size >"<<sz<<" : "<<size<<endl;
	for_each(vec.begin(), it, [](const string &s1){ cout<<s1<<" "; });
}
```
2. (10.28)一个vector中保存1到9,将其拷贝到三个其他容器中.分别使用inserter,back_inserter和front_inserter将元素添加到三个容器中.对每种inserter,估计输出序列是怎样的.
```c++
int main(){
	vector<int> vec{1,2,3,4,5,6,7,8,9};
	deque<int> vec1;
	vector<int> vec2,vec3;
	copy(vec.begin(), vec.end(), front_inserter(vec1));
	copy(vec.begin(), vec.end(), back_inserter(vec2));
	copy(vec.begin(), vec.end(), inserter(vec3, vec3.begin()));

	cout<<" origin vec : ";
	for_each(vec.begin(), vec.end(), [](const int &e){ cout<<e<<" "; });
	cout<<endl;

	cout<<" deque front_inserter : ";
	for_each(vec1.begin(), vec1.end(), [](const int &e){ cout<<e<<" "; });
	cout<<endl;  // 9 8 7 6 5 4 3 2 1

	cout<<" vector back_inserter : ";
	for_each(vec2.begin(), vec2.end(), [](const int &e){ cout<<e<<" "; });
	cout<<endl;  // 1 2 3 4 5 6 7 8 9

	cout<<" vector inserter vec.begin() : ";
	for_each(vec3.begin(), vec3.end(), [](const int &e){ cout<<e<<" "; });
	// 1 2 3 4 5 6 7 8 9
	return 0;
}
```
3. (10.37) 给定一个包含10个元素的vector,将位置3到7之间的元素按逆序拷贝到一个list中
```c++
int main(){
	vector<int> vec{1,2,3,4,5,6,7,8,9,10};
	list<int> lst;
	auto itb=vec.crbegin(); for(int i=0; i<3; ++i) ++itb;
	auto ite=itb; for(int i=0; i<5; ++i) ++ite;
	copy(itb, ite, back_inserter(lst));
	for(const auto &e : lst)
		cout<<e<<" ";
	return 0;
}
```
4. (10.40) 列出copy,reverse,unique要求迭代器的种类
```c++
copy(input_it1, input_it2, output_it);
reverse(bi_it1, bi_it2);
unique(forward_it1, forward_it2);
```

5. (10.42) 使用list替代vector重新实现去除重复单词的程序
```c++
void elimDups(list<string> &words){
	words.sort();
	words.unique();
}
```