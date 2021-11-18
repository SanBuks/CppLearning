#ifndef CPP_PRIMER_CH15_CODE_QUOTE_
#define CPP_PRIMER_CH15_CODE_QUOTE_

#include <iostream>
#include <utility>

class Quote;
double PrintTotal(std::ostream &os, const Quote &item, size_t n);
void swap(Quote &lhs, Quote &rhs) noexcept;

class Quote {

  friend void swap(Quote &lhs, Quote &rhs) noexcept;

 public:
  Quote() = default;
  Quote(const Quote &) = default;
  Quote(Quote &&) noexcept;
  Quote &operator=(const Quote &) &;
  Quote &operator=(Quote &&) & noexcept;
  virtual ~Quote() = default;

  Quote(std::string book_no, double price)
      : book_no_(std::move(book_no)), price_(price) {}

  void swap(Quote &rhs) noexcept;

  std::string isbn() const { return book_no_; }

  virtual Quote *Clone() const & { return new Quote(*this); }
  virtual Quote *Clone() && { return new Quote(std::move(*this)); }
  virtual double NetPrice(std::size_t n) const {
    return static_cast<double>(n) * price_;
  }
  virtual void Debug();

 protected:
  double price_ = 0.0;   // 不打折的原价格

 private:
  std::string book_no_;  // ISBN 编号
};

double PrintTotal(std::ostream &os, const Quote &item, size_t n) {
  double ret = item.NetPrice(n);
  os << "ISBN: " << item.isbn() << " "
     << "sold: " << n << " "
     << "total due: " << ret << "\n";
  return ret;
}

void swap(Quote &lhs, Quote &rhs) noexcept {
  using std::swap;
  lhs.swap(rhs);
}

Quote::Quote(Quote &&rhs) noexcept
    : book_no_(std::move(rhs.book_no_)), price_(rhs.price_) {}

Quote &Quote::operator=(const Quote &rhs) & {
  if (this == &rhs) {
    return *this;
  }
  Quote temp(rhs);
  swap(temp);
  return *this;
}

Quote &Quote::operator=(Quote &&rhs) & noexcept {
  if (this == &rhs) {
    return *this;
  }
  book_no_ = std::move(rhs.book_no_);
  price_ = rhs.price_;
  return *this;
}

void Quote::swap(Quote &rhs) noexcept {
  using std::swap;
  swap(book_no_, rhs.book_no_);
  swap(price_, rhs.price_);
}

void Quote::Debug() {
  std::cout << "book_no: " << book_no_<< " price: " << price_;
}
#endif