#include "query.h"

#include "query_base.h"
#include "query_result.h"

Query::Query(const std::string &str) : p_query_base_(new WordQuery(str)) {}
QueryResult Query::Eval(const TextQuery &t) const {
  return p_query_base_->Eval(t);
}
std::string Query::Rep() const {
  return p_query_base_->Rep();
}
std::ostream &operator<<(std::ostream &os, const Query &query) {
  return os << query.Rep();
}