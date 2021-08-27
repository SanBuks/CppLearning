

### 17.28
> 编写函数，每次调用生成并返回一个均匀分布的随机unsigned int。

### 17.29
> 修改上一题中编写的函数，允许用户提供一个种子作为可选参数。

### 17.30\*
> 再次修改你的程序，此次增加两个参数，表示函数允许返回的最小值和最大值。
```c++
#include <iostream>
#include <random>
#include <chrono>
#include <climits>

unsigned long RandomUL(
    unsigned long seed = 0, 
    unsigned long min = 0, 
    unsigned long max = std::numeric_limits<unsigned long>::max()) {
  static unsigned long seed_ = seed;
  static std::default_random_engine random_e(seed_);
  static unsigned long min_ = min;
  static unsigned long max_ = max;
  static std::uniform_int_distribution<unsigned long> uniform_d(min_, max_);

  if (seed_ != seed ) {
    seed_ = seed;
    random_e.seed(seed);
  }
  if (min_ != min || max_ != max) {
    uniform_d = std::uniform_int_distribution<unsigned long>(min, max);
  }

  return uniform_d(random_e);
}

int main() {
  unsigned long seed = 
    std::chrono::system_clock::now().time_since_epoch().count();

  for (unsigned i = 0; i != 10; ++i){
    std::cout << RandomUL(seed) << " ";
  } 
  std::cout << "\n";

  for (unsigned i = 0; i != 10; ++i){
    std::cout << RandomUL(seed, 1, 10) << " ";
  } 
  std::cout << "\n";
  for (unsigned i = 0; i != 10; ++i){
    std::cout << RandomUL(seed, 1, 100) << " ";
  } 
  std::cout << "\n";
  return 0;
}
```

### 17.31\*
> 对于本节中的游戏程序，如果在do循环内定义b和e，会发生什么？
```c++
// 每次循环都会重新生成, 状态相同, 随机数相同
void play(){
  static std::default_random_engine e;
  static std::bernoulli_distribution b(0.56);
  std::string resp;
  do {
    bool first = b(e);
    std::cout << (first ? "You lost!" : "You win!") << "\n";
    std::cout << "play again? Enter Y or N" << "\n";
    std::cin >> resp;
    while (!std::cin || (resp != "Y" && resp != "N")) {
        std::cout << "Please Enter Y or N" << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::size_t>::max());
        std::cin >>resp;
    }
    if (resp == "Y") {
      continue;
    }
    if (resp == "N") {
      break;
    } 
  } while (true);
}
```

### 17.32
> 如果我们在循环内定义resp，会发生什么？

resp 在条件判断中未定义

### 17.33
> 修改11.3.6节中的单词转换程序，允许对一个给定单词有多种转换方式，每次随机选择一种进行实际转换。
```c++

```