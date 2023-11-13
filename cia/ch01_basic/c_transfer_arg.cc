#include <iostream>
#include <thread>

int main() {
  char buff[100] = "Hello Concurrent World!\n";
  auto a_func = [](const std::string &str) { std::cout << str; };
//std::thread t(a_func, buff);  // buff 以  char * 保存在线程空间中,  线程运行时才隐式构造成一个对象, 仍然存在资源被释放风险
  std::thread ta(a_func, std::string(buff));  // 显示构造右值对象副本防止资源释放风险
  ta.join();

// 简要过程 万能引用 &&(thread ctor) -> decay(type) ->  ype && -> invoke
  int c = 3;
  auto b_func = [](int &i) { std::cout << ++i << "\n"; };
//  std::thread tb(b_func, c);  // 以左值形式传递, 最终 invoke 时会出现右值
  std::thread tb(b_func, std::ref(c));  // 避免传递右值
  tb.join();
}


