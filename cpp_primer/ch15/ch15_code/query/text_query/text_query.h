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

#endif