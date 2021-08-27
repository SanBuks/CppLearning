# 4. 随机数
## rand 函数 
- 生成均匀分布的伪随机整数 [0, RAND_MAX], RAND_MAX 最小为 32767 因具体库实现而异
- 通过mod 运算产生的随机数不是准确的均匀分布, 比预期值要小
- 不支持随机浮点值
- 范围有限

## 随机数引擎和分布
### 对象与模板
- `default_random_engine random_e`
- `uniform_int_distribution<class IntType = int>`
- `uniform_real_distribution<class RealType = double>`
- `normal_distribution<class RealType = double>`
- `explicit bernoulli_distribution( double p=0.5 );`

### 其他函数
- 取整 (四舍五入, 向非0方向入) : 
```c++
float roundf( float arg );
double round( double arg );
long double roundl( long double arg );

long lroundf( float arg );
long lround( double arg );
long lroundl( long double arg );

long long llroundf( float arg );
long long llround( double arg );
long long llroundl( long double arg );
```

- 获取时间数 :   `std::chrono::system_clock::now().time_since_epoch().count();`


### 使用范例

```c++
#include <iostream>
#include <random>
#include <chrono>

int main() {
  // 线性同余发生器引擎 : x_n = (x_n-1 * a + c) % m
  // 生成无符号随机整数
  // static 维持状态
  static std::default_random_engine random_e;

  // 获取 随机种子
  unsigned seed = 
    std::chrono::system_clock::now().time_since_epoch().count(); 

  // 设置 随机种子
  random_e.seed(seed);

  // 获取 随机值
  std::default_random_engine::result_type random_val = random_e();
  std::cout << "RANDOM VALUE is " << random_val << "\n";

  // 前进 10 个状态
  random_e.discard(10);
  std::cout << "RANDOM VALUE(advanced 10 value ) is " <<  random_e() << "\n";

  // 获取 最大值 & 最小值
  std::cout << "MAX VALUE is " << random_e.max() << "\n";
  std::cout << "MIN VALUE is " << random_e.min() << "\n";

  // 设置 均匀分布的范围( a > b 未定义)
  // static 维持状态
  static std::uniform_int_distribution<unsigned> u(0, 10);

  // 重置状态
  u.reset();

  // 获取 分布的一个随机数
  std::cout << "RANDOM VALUE(uniform) is " << u(random_e) << "\n";

  // 获取 分布的最大最小值
  std::cout << "MAX VALUE is " << u.max() << " " << u.b() << "\n";
  std::cout << "MIN VALUE is " << u.min() << " " << u.a() << "\n";
  return 0;
}
```