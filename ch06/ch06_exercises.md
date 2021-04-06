### 7. 例题
1. (6.1) 实参和形参的区别是什么?
   1. 形参是在调用函数时接受实参值的变量,由参数列表定义,调用时分配内存,结束调用时释放内存,作用域仅在函数中
   2. 实参是形参的初始值,在调用时能够求得确切的值,单项拷贝传递内容给形参,值传递实参内容不能通过函数改变(引用传)递可以)
2. (6.18) 编写函数声明
   1. bool compare(const matrix &m1, const matrix &m2);
   2. vector\<int>::iterator change_val(int e, vector\<int>::iterator it);
3. (6.25) 编写一个main函数,接受两个string,输出拼接后的string
   ```C++
      int main(int argc, char *argv[]){
       if(argc>2)
           cout<<argv[1]<<argv[2]<<endl;
       else cout<<"no enough options!"<<endl;
       return 0;
   }
   ```
4. (6.27) 编写一个函数,参数为initializer_list\<int>,计算所有数的和
   ```C++
   int clac_all(initializer_list<int> list){
       int sum=0;
       for(const auto &it:list)
           sum+=it;
       return sum;
   }
   ```
5. (6.33) 编写一个递归函数,输出vector对象的内容,调试输出vector大小
   ```C++
   void print(const vector<int> &vec, int index){
   	#ifndefine NDEBUG
   	static int times=0;//调用的第一次输出vector大小
   	++times;
   	if(times==1)
       		cout<<sizeof(vec)
   	#endif    
       	if(index>=0){
           	cout<<" "<<vec[index];
           	print(vec,index-1);
       	}
       	else cout<<"\ntraverse is over!\n";
   }
   ```
6. (6.36&37) 用4种方式声明返回10个数组引用的函数
   ```C++
   using namespace std;
   using array10=int [10];
   int a[10]={};

   int (&return_ref2array1())[10]; // 直接用类型表示
   array10 &return_ref2array2(); //类型别名
   auto return_ref2array3()->int (&)[10]; //置尾返回类型
   decltype(a) &return_ref2array4(); //decltype
   ```
7. (6.46) 能把const string &isShorter(const string &s1, const string &s2){return s1.size()<=s2.size()?s1:s2;}改成constexpr吗?
   不可以，const string& 虽然是常量引用但不是字面值类型
   返回值和参数必须是字面值类型
8. (6.48) 说明下面循环意义,assert使用合理吗?
   ```C++
   string s;
   while(cin>>s&&s!=sought){}
   //反复读入一个字符串直到读入的字符串等于sought
   assert(cin);
   /*
       对cin的状态进行判断 eofbit failbit badbit good
       其中默认调用operator bool来转换成bool形式,与good()有区别!
       bool()只有在 failbit badbit 都不为真的情况下返回真
       good()只有在 eofbit failbit badbit 都不为真的情况下返回真

       此处通过assert判断cin读入到状态如何是可以的
       1.没读对string类型cin出错 failbit -> false
       2.没读对string内容,反复读str直到读到^z导致最后没有读到内容 failbit->false
       3.只有在 cin>>s; //输入 str (后接^z或者其他字符都可以) cin状态goodbit和eofbit bool为真
   */
   ```
9. (6.50) 已知函数声明,判断下列调用重载函数的情况
   ```C++
   void f(){} // 1
   void f(int e){} // 2
   void f(int e, int f){} // 3
   void f(double e, double f=3.14){} // 4

   int main(int argc, char *argv[]){
       f(2.56, 42); // 2.56->double 42(先提升成int)->double 二异
       f(42); // 调用 2
       f(42, 0); // 调用 3
       f(2.56, 3.14); // 调用4
       return 0;
   }
   ```
10. (6.54-56) 定义一个元素是 接受2个int形参返回int的函数指针的vector,编写加减乘除4个函数,将4个函数放入vector中,最后调用
    ```C++
    // 注意 std::minus 会和自己定义的minus命名冲突
    int add(int e1, int e2){ return e1+e2; }
    int minuss(int e1, int e2){ return (e2!=0)?e1-e2:0; }
    int multiply(int e1, int e2){ return e1*e2; }
    int divide(int e1, int e2){ return e1/e2; }
    using FuncP=int (*)(int, int);
    vector<FuncP> vec;
    int main(int argc, char *argv[]){
        vec.push_back(add);
        vec.push_back(minuss);
        vec.push_back(multiply);
        vec.push_back(divide);
        cout<<vec[0](1,2)<<endl; //3
        cout<<vec[1](1,1)<<endl; //0
        cout<<vec[2](2,3)<<endl; //6
        cout<<vec[3](6,3)<<endl; //2
        return 0;
    }
    ```