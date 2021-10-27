#ifndef CPP_PRIMER_CH12_CODE_TEXT_QUERY_H_
#define CPP_PRIMER_CH12_CODE_TEXT_QUERY_H_

#include <vector>
#include <map>
#include <set>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>

#include "query_result.h"

class TextQuery {
 public:
  // 输入文件
  explicit TextQuery(std::ifstream &);
  // 输出结果
  QueryResult Query(const std::string &str) const;
 private:
  // 存放 文本文件的 每一行
  std::shared_ptr<StrBlob> files_;
  // 存放 单词 对应 行集合
  std::map<std::string, std::shared_ptr<std::set<size_t>>> mp_;
};

TextQuery::TextQuery(std::ifstream &ifs) : files_(new StrBlob) {
  // 不用在循环内构造对象
  std::string text;
  std::string word;
  std::istringstream iss;
  while (getline(ifs, text)) {
    files_->PushBack(text);
    // 清空 istringstream 内容
    iss.str(std::string());
    iss.clear();
    iss.str(text);
    size_t no = files_->Size() - 1;
    while (iss >> word) {
      auto &line_ptr = mp_[word];
      // 不存在 创建新的 set
      if (!line_ptr) {
        line_ptr.reset(new std::set<size_t>);
      } else {
      // 存在 直接插入行号 (从 0 开始)
        line_ptr->insert(no);
      }
    }
  }
}

QueryResult TextQuery::Query(const std::string &str) const {
  static std::shared_ptr<std::set<size_t>> nodata(new std::set<size_t>);
  auto re = mp_.find(str);
  if (re == mp_.end())  {
    return {str, nodata, files_};
  } else {
    return {str, re->second, files_};
  }
}

#endif