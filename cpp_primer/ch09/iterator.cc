#include <vector>
#include <string>
#include <deque>

#include <list>
#include <forward_list>

#include <array>

#include <iterator>

#include <iostream>
#include <cassert>
#include <algorithm>
#include <utility>
#include <initializer_list>

template<typename T>
void print_container(const T& v) {
  std::for_each(v.begin(), v.end(), 
      [] (std::vector<int>::const_reference item) {
        std::cout<< item << "\n"; 
      });
}

class Test {
private :
  std::string m_name;
public :
  Test(std::string name) : m_name(name) {}
  Test() : m_name("2") {}
  std::string name() { return m_name; }
  std::string name() const { return m_name; }
};

int main() {
  std::forward_list<Test> flst{{"1"}, {"2"}, {"3"}, {"4"}};
  std::vector<Test> vec{{"1"}, {"2"}, {"3"}, {"4"}};

  auto bbit = flst.before_begin();
  auto cbbit = flst.cbefore_begin();

  auto resutl_it1 = flst.insert_after(bbit, {"2"});
  auto resutl_it2 = flst.insert_after(bbit, 3, {"2"});
  auto resutl_it3 = flst.insert_after(bbit, vec.begin(), vec.end());
  auto resutl_it4 = flst.insert_after(bbit, {{"1"}, {"2"}, {"3"}, {"4"}});
  auto resutl_it4 = flst.emplace_after(bbit, "3");

  auto resutl_it5 = flst.erase_after(flst.before_begin());
  auto resutl_it6 = flst.erase_after(flst.before_begin(), flst.end());

  return EXIT_SUCCESS;
}