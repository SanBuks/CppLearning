#ifndef CPP_PRIMER_CH15_CODE_QUERY_QUERY_BASE_H
#define CPP_PRIMER_CH15_CODE_QUERY_QUERY_BASE_H

#include <string>
#include <memory>
#include <utility>

#include "query.h"

class QueryBase {

  friend class Query;

 public:
  virtual ~QueryBase() noexcept = default;
  // 派生类通过 指针多态调用 需要调整为 public

 protected:
  // 禁止用户直接使用
  QueryBase() = default;
  QueryBase(const QueryBase &rhs) = default;
  QueryBase(QueryBase &&rhs) = default;
  QueryBase &operator=(const QueryBase &rhs) = default;
  QueryBase &operator=(QueryBase &&rhs) = default;

 private:
  virtual QueryResult Eval(const TextQuery &) const = 0;
  virtual std::string Rep() const = 0;
};

class WordQuery : public QueryBase {

  friend class Query;

 public:
  ~WordQuery() override = default;

 protected:
  WordQuery() = default;
  WordQuery(const WordQuery &rhs) = default;
  WordQuery(WordQuery &&rhs) = default;
  WordQuery &operator=(const WordQuery &rhs) = default;
  WordQuery &operator=(WordQuery &&rhs) = default;

  explicit WordQuery(std::string query_word)
      : query_word_(std::move(query_word)) {
    std::cout << "WordQuery Constructor" << "\n";
  }

  QueryResult Eval(const TextQuery &text_query) const override;
  std::string Rep() const override;

 private:
  std::string query_word_;
};

class NotQuery : public QueryBase {

  friend Query operator~(const Query &);

 public:
  NotQuery() = delete;
  ~NotQuery() override = default;
  QueryResult Eval(const TextQuery &text_query) const override;
  std::string Rep() const override;

 protected:
  NotQuery(const NotQuery &rhs) = default;
  NotQuery(NotQuery &&rhs) = default;
  NotQuery &operator=(const NotQuery &rhs) = default;
  NotQuery &operator=(NotQuery &&rhs) = default;

  explicit NotQuery(Query query_base)
      : query_(std::move(query_base)) {
    std::cout << "WordQuery Constructor" << "\n";
  }

 private:
  Query query_;
};

class BetweenQuery : public QueryBase {

  friend Query GetBetween(size_t, size_t, const Query &query);

 private:
  BetweenQuery(size_t low, size_t high, Query query)
      : low_(low), high_(high), query_(std::move(query)) {
    std::cout << "BetweenQuery" << "\n";
  }

  std::string Rep() const override;
  QueryResult Eval(const TextQuery &text_query) const override;
  size_t low_;
  size_t high_;
  Query query_;
};

class BinaryQuery : public QueryBase {
 protected:
  BinaryQuery(Query query_lhs_, Query query_rhs_, std::string operator_str)
      : query_lhs_(std::move(query_lhs_)), query_rhs_(std::move(query_rhs_)),
        operator_str_(std::move(operator_str)) {}

  std::string Rep() const override;

  Query query_lhs_;
  Query query_rhs_;
  std::string operator_str_;
};

class OrQuery : public BinaryQuery {
  friend Query operator|(const Query &, const Query &);
  OrQuery(Query query_lhs, Query query_rhs)
      : BinaryQuery(std::move(query_lhs), std::move(query_rhs), "|") {
    std::cout << "OrQuery" << "\n";
  }
  QueryResult Eval(const TextQuery &) const override ;
};

class AndQuery : public BinaryQuery {
  friend Query operator&(const Query &, const Query &);
  AndQuery(Query query_lhs, Query query_rhs)
      : BinaryQuery(std::move(query_lhs), std::move(query_rhs), "&") {
    std::cout << "AndQuery" << "\n";
  }
  QueryResult Eval(const TextQuery &) const override;
};

#endif