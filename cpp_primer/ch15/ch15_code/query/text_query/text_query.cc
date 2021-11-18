#include "text_query.h"

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
      }
      // 插入行号 (从 0 开始)
      line_ptr->insert(no);
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

std::ostream &Print(std::ostream &os, const QueryResult &qr) {
  os << qr.word_search_ << " occurring times : " << qr.lines_->size() << "\n";
  for (auto it: *qr.lines_)
    os << "\t (line " << it + 1 << ")" << (*qr.files_)[it] << "\n";
  return os;
}
