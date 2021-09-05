#ifndef CH07_CH07_CODE_WINDOW_MGR_H
#define CH07_CH07_CODE_WINDOW_MGR_H

#include <vector>
#include <string>

class Screen;
class Window_mgr {
 public:
  using ScreenIndex = std::vector<Screen>::size_type;
  void clear(ScreenIndex);
  void print(ScreenIndex);
  ScreenIndex addScreen(const Screen &);
  Window_mgr();

 private:
  // 类内初始值为空 合法
  // 类内初始值为具体构造参数 不合法
  std::vector<Screen> screens{};
};

#endif