#ifndef CPP_PRIMER_CH15_CODE_QUERY_QUERY_H
#define CPP_PRIMER_CH15_CODE_QUERY_QUERY_H

#include <utility>
#include "text_query.h"

class QueryBase;
class Query;

Query operator~(const Query &lhs);
Query operator|(const Query &lhs, const Query &rhs);
Query operator&(const Query &, const Query &);
Query GetBetween(std::size_t, size_t, const Query &);

// Query 本质是封装多态基类的指针
class Query {

  friend Query operator~(const Query &lhs);
  friend Query operator|(const Query &lhs, const Query &rhs);
  friend Query operator&(const Query &, const Query &);
  friend Query GetBetween(size_t, size_t, const Query &);

 public:
  explicit Query(const std::string &str);
  Query(const Query &rhs) = default;
  Query(Query &&rhs) = default;
  Query &operator=(const Query &rhs) = default;
  Query &operator=(Query &&rhs) = default;
  ~Query() = default;

  QueryResult Eval(const TextQuery &t) const;
  std::string Rep() const;

 private:
  explicit Query(std::shared_ptr<QueryBase> p_query_base)
      : p_query_base_(std::move(p_query_base)) {}
  // 指向 QueryBase 继承体系
  std::shared_ptr<QueryBase> p_query_base_;
};

#endif