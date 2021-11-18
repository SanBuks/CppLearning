#include "query_base.h"

#include <set>
#include <algorithm>

QueryResult WordQuery::Eval(const TextQuery &text_query) const {
  return text_query.Query(query_word_);
}
std::string WordQuery::Rep() const {
  return query_word_;
}

QueryResult NotQuery::Eval(const TextQuery &text_query) const {
  auto result = query_.Eval(text_query);
  auto ret_lines = std::make_shared<std::set<size_t>>();
  auto beg = result.Begin();
  auto end = result.End();
  auto sz = result.GetFiles()->Size();

  // result_size() <= file_size()
  // set 是有序的
  for (size_t n = 0; n != sz; ++n) {
    // 如果 result 遍历完 或者 result 的元素不在结果中则直接插入
    if (beg == end || *beg != n) {
       ret_lines->insert(n);
    // 只有当 result 存在剩余元素时 才增加 迭代器
    } else if (beg != end) {
      ++beg;
    }
  }
  return {Rep(), ret_lines, result.GetFiles()};
}
std::string NotQuery::Rep() const {
  return "~(" + query_.Rep() + ")";
}
Query operator~(const Query &rhs) {
  return Query(std::shared_ptr<QueryBase>(new NotQuery(rhs)));
}

QueryResult BetweenQuery::Eval(const TextQuery &text_query) const {
  auto result = query_.Eval(text_query);
  auto ret_lines = std::make_shared<std::set<size_t>>();
  for (auto beg = result.Begin(); beg != result.End(); ++beg) {
    if ((low_ > high_) || (*beg >= low_ && *beg <= high_)) {
      ret_lines->insert(*beg);
    }
  }
  return {Rep(), ret_lines, result.GetFiles()};
}
std::string BetweenQuery::Rep() const {
  std::stringstream oss;
  oss << "(Between(" << query_.Rep()
      << ")[" << (low_ + 1) << "," << (high_ + 1) << "])";
  return oss.str();
}
Query GetBetween(size_t low, size_t high, const Query &query) {
  return Query(std::shared_ptr<QueryBase>(
        new BetweenQuery(low - 1, high - 1, query)));
}

std::string BinaryQuery::Rep() const {
  return "(" + query_lhs_.Rep() +
         " " + operator_str_ +
         " " + query_rhs_.Rep() + ")";
}
QueryResult OrQuery::Eval(const TextQuery &text) const {
  auto left = query_lhs_.Eval(text);
  auto right = query_rhs_.Eval(text);

  auto ret_lines = std::make_shared<std::set<size_t>>(left.Begin(), left.End());
  ret_lines->insert(right.Begin(), right.End());
  return {Rep(), ret_lines, left.GetFiles()};
}
Query operator|(const Query &lhs, const Query &rhs) {
  return Query(std::shared_ptr<QueryBase>(new OrQuery(lhs, rhs)));
}

QueryResult AndQuery::Eval(const TextQuery &text) const {
  auto left = query_lhs_.Eval(text);
  auto right = query_rhs_.Eval(text);
  auto ret_lines = std::make_shared<std::set<size_t>>();
  std::set_intersection(left.Begin(), left.End(), right.Begin(), right.End(),
                        inserter(*ret_lines, ret_lines->begin()));
  return {Rep(), ret_lines, left.GetFiles()};
}
Query operator&(const Query &lhs, const Query &rhs) {
  return Query(std::shared_ptr<QueryBase>(new AndQuery(lhs, rhs)));
}