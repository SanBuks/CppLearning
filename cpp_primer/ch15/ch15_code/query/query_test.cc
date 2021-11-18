#include "query_base/query.h"
#include "query_data.h"

void TestQuery(std::ifstream &ifs) {
  TextQuery tq(ifs);
  Query q = GetBetween(1, 2, ~Query("View"));
  Print(std::cout, q.Eval(tq));
  //Query q=Query("fiery") & Query("bird") | Query("wind");
  //q.rep();
  //Query q=get_between(1, 50, ~query("In")); //| (~Query("function"));
  //print(cout, q.eval(tq));
}

void TestNotQuery(std::ifstream &ifs) {
  TextQuery tq(ifs);
  Query p = ~Query("View");
  Print(std::cout, p.Eval(tq));
}

void TestBetweenQuery(std::ifstream &ifs) {
  TextQuery tq(ifs);
  Query p = GetBetween(1, 3, ~Query("View"));
  Print(std::cout, p.Eval(tq));
}

void TestAndQuery(std::ifstream &ifs) {
  TextQuery tq(ifs);
  Query p = GetBetween(1, 3, ~Query("View")) & GetBetween(3, 4, ~Query("View"));
  Print(std::cout, p.Eval(tq));
}

void TestOrQuery(std::ifstream &ifs) {
  TextQuery tq(ifs);
  Query p = GetBetween(1, 3, ~Query("View")) | GetBetween(3, 4, ~Query("View"));
  Print(std::cout, p.Eval(tq));
}

void TestExercises(std::ifstream &ifs) {
  TextQuery tq(ifs);
  Query p = Query("fiery") & Query("bird") | Query("wind");
  Print(std::cout, p.Eval(tq));
}

int main() {
  std::system("chcp.com 65001");
  std::ifstream ifs(::data_path::kQueryDataPath);
  if (ifs) {
//    TestQuery(ifs);
//    TestNotQuery(ifs);
//    TestBetweenQuery(ifs);
//    TestAndQuery(ifs);
//    TestOrQuery(ifs);
    TestExercises(ifs);
  }
  return 0;
}
