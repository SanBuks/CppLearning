#include <iostream>
#include <memory>
#include <vector>

#include "quote.h"
#include "bulk_quote.h"
#include "bulk_limit_quote.h"
#include "basket.h"

void QuoteTest() {
  Quote quote("Quote", 20.2);
  quote.Debug();
  std::cout << " " << quote.NetPrice(30) << "\n";

  PrintTotal(std::cout, quote, 30);
}

void BulkQuoteTest() {
  BulkQuote bq("BulkQuote", 23.3f, 25, 0.2f);
  bq.Debug();
  std::cout << " " << bq.NetPrice(25) << "\n";

  PrintTotal(std::cout, bq, 25);
}

void BulkLimitQuoteTest() {
  BulkLimitQuote blq1("BulkLimitQuote1", 23.3f, 25, 0.2F, 30);
  BulkLimitQuote blq2("BulkLimitQuote2", 23.3f, 25, 0.2F, 60);

  PrintTotal(std::cout, blq1, 30);
  PrintTotal(std::cout, blq1, 31);
  PrintTotal(std::cout, blq2, 31);
}

void VectorTest() {
  double sum = 0.0;
  std::vector<std::shared_ptr<Quote>> vec;
  vec.push_back(std::make_shared<Quote>("Quote q", 50));
  vec.push_back(std::make_shared<BulkQuote>("BulkQuote bq", 23.3, 25, 0.2));
  for (const auto &it: vec) {
    sum += it->NetPrice(80);
  }
  std::cout << sum << std::endl;  // $ = 5491.2
}

void BasketTest() {
  Basket basket;
  Quote m1("q", 20);

  for (int i = 0; i < 11; i++) {
    // 测试调用 左值
    basket.AddItem(m1);
  }
  for (int i = 0; i < 11; i++) {
    // 测试调用 右值
    basket.AddItem(Quote("q", 50));
  }
  for (int i = 0; i < 11; i++) {
    basket.AddItem(BulkQuote("bq", 23.3, 3, 0.2));
  }
  for (int i = 0; i < 11; i++) {
    basket.AddItem(BulkLimitQuote("blq", 23.3, 4, 0.2F, 10));
  }
  basket.TotalReceipt(std::cout);
}

int main() {
  QuoteTest();
  std::cout << "--------\n";
  BulkQuoteTest();
  std::cout << "--------\n";
  BulkLimitQuoteTest();
  std::cout << "--------\n";
  VectorTest();
  std::cout << "--------\n";
  BasketTest();
  return 0;
}
