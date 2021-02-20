# 第11章 关联容器
### 1. 关联容器概述
#### 分类
- 关联容器分类依据 : 键值或集合; 关键字是否重复; 关键字是否有序

| 头文件名 | 对象 | 组织规则 |
| --- | --- | --- |
| `<unordered_map/set>` | `unordered_(multi_)map`<br/>`unordered_(multi_)set` | 哈希函数 |
| `<map/set>` | `(multi_)map`<br/> `(multi_)set` | 严格弱序 |

#### 基本用法
```c++
map<int, double> mp={ {1, 2.3}, {2, 2.4}, {3, 2.5} };  // 定义一个map
mp[32]=12.0;  
// 1. 搜索关键字 32
// 2. 未搜到, 将pair<const int, double>(32, 初识值)插入
//    内置类型初识值为零
// 3. 访问元素将12.0赋值
// 由于下标操作会改变map, 一般 const map 没有下标操作

auto it=mp.find(121);  // 返回关键值等于121的元素迭代器 未找到则为 mp.end()
std::cout<<it->first; // 通过迭代器访问的是pair对象 含有first和second成员分别为int 和double
```
#### 严格弱序
- 有序容器的关键字类型要求是严格弱序 :
    - 特殊 : 不能同时 <= 对方 
    - 传递 : k1<=k2 , k2<=k3 => k1<=k3 
    - 等价 : 任何一个都不 <= 对方 则二者相等
- 可以添加函数指针类型自定义弱序关系 如 `set<T, decltype(funcname)*> st;`

### 2. pair

| pair 操作 \<utility> | 描述 |
| ------------------- | ---------------- |
| pair<T1, T2> p(v1, v2) <br/>pair<T1, T2> p={v1, v2} | 初始化 |
| auto it=make_pair(v1, v2)  | 生成pair |
| p1 relop p2  | 根据 first和second成员先后 relop 比较 |
| p1 == p2<br/>p1!=p2   | 判断first 和 second 成员是否都相同 |

### 3. 关联容器操作
#### 别名

| 别名         | map\<T1, T2> mp                      | set\<T> st |
| ------------ | ------------------------------------ | ---------- |
| key\_type    | T1                                   | T          |
| mapped\_type | T2                                   | -          |
| value\_type  | pair\<const key\_type, mapped\_type> | T          |

#### 迭代器
- map迭代器指向`value_type`, 其中的`key_type`是不可改变的, set的元素也是不可改变, 因此不可以使用 写相关泛型算法
- 关联容器有自己的find操作, 比泛型搜索算法效率高
- 如果需要调用泛型算法, 则关联容器可作为源或者目的位置
```c++
// v 是顺序容器 c是关联容器
copy(c.begin(), c.end(), inserter(v, v.end()));  // 作为源
copy(v.begin(), v.end(), inserter(c, c.end())); // 作为目的位置
```

#### 插入操作

| 插入操作 | 描述 |
| ------------------- | ---------------- |
| c.insert(v)<br/>c.emplace(args)<br/>c.insert(p,v)<br/>c.emplace(p, args) |插入元素v, 如果含有迭代器p则从p所指位置搜索键值 <br />返回 pair(iterator, bool) it指向插入位置元素,如果关键字已存在则为false<br />如果键值可重复则返回 it指向插入位置元素|
| c.insert(b,e)<br/>c.insert(il) | 根据迭代器范围插入或者列表插入 返回void |


```c++
// map 一般插入方式
auto it=mp.insert({word, 1});
if(!it.second)
	it.first->second++;
```

#### 删除操作

| 删除操作 | 描述 |
| ------------------- | ---------------- |
| c.erase(k) | 删除键值为k的元素 返回size_t为删除元素的数量 |
| c.erase(p)<br/>c.erase(b,e)  | 删除迭代器p所指元素 返回其尾后迭代器<br/>删除迭代器范围元素 返回尾后迭代器|


#### 下标操作

| (unordered\_)map下标操作 | 描述 |
| ------------------- | ---------------- |
| c[k] | 返回关键字为k的元素引用, 如果不在则值初始化 |
| c.at(k) | 访问关键字为k的元素引用, 若不在则抛出`out_of_range`异常 |

> set, multiset, multimap 不支持下标操作

#### 访问操作

| 访问操作 | 描述 |
| ------------------- | ---------------- |
| c.find(k)  | 返回关键字为k的迭代器或者为尾后迭代器|
| c.count(k) | 返回关键字为k元素的数量|
| c.lower_bound(k)| 返回关键字 不小于k的 第一个元素|
| c.upper_bound(k)| 返回关键字 大于k的 第一个元素|
| c.equal_range(k)| 返回关键字为k的范围迭代器的pair|

- 三种遍历mult关联容器方式 : 	
```c++
multiset<int> s{1,2,3,6,4,8,44,1,3,213,1,3,54,64,84};
// 通过迭代器和数量遍历
auto be=s.find(1);
auto size=s.count(1);
while(size){
    cout<<*be++;
    size--;
}

// 通过 lower_bound 和 upper_bound 遍历
for(auto it=s.lower_bound(1); it!=s.upper_bound(1); ++it)
    cout<<*it;

// 通过 equal_range() 遍历
for(auto pos=s.equal_range(1); pos.first!=pos.second; ++pos.first)
    cout<<*pos.first;
```

### 4. 无序关联容器
#### 内部构造
- 无序关联容器存储桶(类似一个容器)
- 通过哈希函数将关键字映射到不同的桶中(类似一个容器), 不同关键字也可以映射到同一的桶中(以哈希函数为准)
- 哈希函数计算桶地址O(1), 桶中搜索根据桶中元素的大小

#### 基本操作
| 访问操作 | 描述 |
| ------------------- | ---------------- |
| c.bucket_count() | 返回桶个数 |
| c.max_bucket_count() | 返回桶最多可存容量 |
| c.bucket_size(n) | 返回第n个桶中有多少元素 |
| c.bucket(k) | 判断关键字在哪个桶中 |
| c.load_factor(n) | 返回平均每个桶的元素数量 float |
| c.max_load_factor(n) | 返回试图维护的平均每个桶的元素数量 float|
| c.(c)begin(n)<br/>c.(c)end(n) | 返回第n个桶的迭代器((const\_)local_iterator) |

| 重组操作 | 描述 |
| ------------------- | ---------------- |
| c.rehash(n) | 重组, 让桶数>=n && load_factor<max_load_factor |
| c.reserve(n) | 重组, 使容器可以预保存n个元素不必rehash |

#### 哈希函数
- 无序容器调用 hash\<key_type> 类型对象产生哈希值, 且为 内置类型, 指针, string 和 智能指针提供了相关模板, 但是自定义类需要自己定义相关 == 和 类似hash\<T>对象
```c++
// hasher 返回无符号数
std::size_t hasher(const Sales_data &sd){
	return std::hash<std::string>(sd.isbn());
}

// 定义了 == 运算符则可以忽略
bool eqOp(const Sales_data &lhs, const Sales_data &rhs){
	return lhs.isbn()==rhs.isbn();
}

using SD_T=unordered_multiset< Sales_data, decltype(hasher)*, decltype(eqOp)* >;
```