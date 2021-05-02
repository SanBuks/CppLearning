#include <memory>
class Widget {
  class WidgetImpl;
 public:
  explicit Widget(int number);
  ~Widget();
  Widget(const Widget &rhs) = delete;
  Widget(Widget &&rhs);
  Widget &operator =(const Widget &rhs) = delete;
  Widget &operator =(Widget &&rhs);

  void show();
 private:
  std::unique_ptr<WidgetImpl> Pimpl;
};