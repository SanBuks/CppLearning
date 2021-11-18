#ifndef CPP_PRIMER_CH15_CODE_BASKET_H
#define CPP_PRIMER_CH15_CODE_BASKET_H

#include <iostream>
#include <set>

class Basket {
 public:
  Basket() = default;
  Basket(const Basket &rhs) = delete;
  Basket(Basket &&rhs) = delete;
  Basket &operator=(const Basket &rhs) = delete;
  Basket &operator=(Basket &&rhs) = delete;
  ~Basket() = default;

  void AddItem(const Quote &sale) {
    items.insert(std::shared_ptr<Quote>(sale.Clone()));
  }
  void AddItem(Quote &&sale) {
    items.insert(std::shared_ptr<Quote>(std::move(sale).Clone()));
  }
  double TotalReceipt(std::ostream &) const;

 private:
  static bool compare(const std::shared_ptr<Quote> &lhs,
                      const std::shared_ptr<Quote> &rhs);
  std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare};
};

bool Basket::compare(const std::shared_ptr<Quote> &lhs,
                    const std::shared_ptr<Quote> &rhs) {
  return lhs->isbn() < rhs->isbn();
}

double Basket::TotalReceipt(std::ostream &os) const {
  double sum = 0.0;
  for (auto it = items.cbegin();
       it != items.cend();
       it = items.upper_bound(*it)) {
    sum += PrintTotal(os, **it, items.count(*it));
  }
  os << "Total sum: " << sum << std::endl;
  return sum;
}

#endif