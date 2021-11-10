#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <cstring>
#include <memory>

#include "str_blob.h"
#include "str_blob_data.h"
#include "str_blob_ptr_ptr.h"

void StrBlobTest() {
  StrBlob str1;
  StrBlob str2 = {"123", "234", "345"};
  const StrBlob str3(str2);

  // test for exception
  try {
    str1.PopBack();
    std::cout << "Error Test Failed\n";
  } catch (std::out_of_range &ex) {
    std::cout << "Error Test Passed\n";
  }

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
}

void StrBlobPtrTest() {
  StrBlob str = {"123", "234", "345"};
  for (auto it = str.Begin(); it != str.End(); ++it) {
    std::cout << it.curr() << " : " << *it << " ";
  }
  std::cout << "\n";
}

void ConstStrBlobPtrTest() {
  StrBlob str = {"123", "234", "345"};
  for (auto it = str.CBegin(); it != str.CEnd(); ++it) {
    std::cout << it.curr() << " : " << *it << " ";
  }
  std::cout << "\n";
}

void ReadFileTest() {
  std::ifstream ifs(data_path::kStrBlobDataPath);
  StrBlob strb;
  if (!ifs) {
    std::cout << "open file error!\n";
    return;
  }
  std::string str;
  while (ifs >> str)
    strb.PushBack(str);
  ifs.close();
  for (auto it = strb.Begin(); it != strb.End(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << "\n" << strb[1] << "\n";
}

int main() {
//  StrBlobTest();
//  StrBlobPtrTest();
//  ConstStrBlobPtrTest();
//  ReadFileTest();
//  StrBlobPtrPtrTest();
  return 0;
}
