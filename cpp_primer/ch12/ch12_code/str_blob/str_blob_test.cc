#include "str_blob.h"

#include <iostream>
//#include "str_blob_ptr_ptr.h"

//#include <fstream>


void StrBlobTest() {
  StrBlob str1;
  StrBlob str2 = {"123", "234", "345"};
  const StrBlob str3(str2);

  // str1.PopBack(); // test for exception

  str1 = str2;

  str2.PopBack();
  str2.PushBack("1111");

  for (StrBlob::RankType i = 0; i != str1.Size(); ++i) {
    std::cout << str3[i] << " ";
  }
  std::cout << "\n";

  std::cout << "use count is " << str3.UseCount() << "\n";
  std::cout << "front is " << str3.Front() << "\n";
  std::cout << "back is " << str3.Back() << "\n";

//  for (auto it = str1.begin(); it != str1.end(); ++it)
//    std::cout << *it << " ";
//  std::cout << "\n";
//  for (auto it = str1.begin(); it != str1.end(); ++it)
//    std::cout << *it << " ";
//  std::cout << "\n";
}

//void readFile_test() {
//  std::ifstream ifs("data");
//  StrBlob strb;
//  if (!ifs) {
//    std::cout << "open file error!\n";
//    return;
//  }
//  std::string str;
//  while (ifs >> str)
//    strb.push_back(str);
//  ifs.close();
//  for (auto it = strb.begin(); it != strb.end(); ++it)
//    std::cout << *it << " ";
//  std::cout << "\n" << strb[1];
//}

//void StrBlobPtr_test() {
//  StrBlob str = {"123", "234", "345"};
//  auto it = str.begin();
//  std::cout << *(it + (str.size() - 1));
//}

//void SBPP_test(){
//	StrBlob str={"123", "234", "345"};
//	auto it=str.begin();
//	SBPP sbpp(it+1);
//	std::cout<<**sbpp<<std::endl;
//	std::cout<<sbpp->getcurr()<<std::endl;
//}

//void test_temp() {
//  StrBlob str1;
//  StrBlob str2 = {"123", "234", "345"};
//  str1 = str2;
//  for (auto it = str1.begin(); it != str1.end(); ++it)
//    std::cout << *it << " ";
//  std::cout << "\n";
//}

int main() {
//  StrBlobTest();
  //readFile_test();
  //StrBlobPtr_test();
  //SBPP_test();
  return 0;
}
