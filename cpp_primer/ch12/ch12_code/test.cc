#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  // shared_ptr 特殊操作
  shared_ptr<vector<int>> sp1 = make_shared<vector<int>>(10, 2);  // 根据 构造函数的参数 动态分配
  shared_ptr<vector<int>> sp2(sp1);                               // 拷贝构造 增加 引用计数
  shared_ptr<vector<int>> sp3 = make_shared<vector<int>>();
  sp3 = sp2;                                                      // 拷贝减少 sp3 引用计数, 增加 sp2 引用计数
  std::cout << sp3.unique() << " " << sp3.use_count() << "\n";    // 引用计数是否是一, 引用计数个数
                                                                  // 3 3


  return 0;
}