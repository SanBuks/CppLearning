#ifndef CPP_PRIMER_CH15_CODE_DISC_QUOTE_
#define CPP_PRIMER_CH15_CODE_DISC_QUOTE_

#include "quote.h"

class DiscQuote;
void swap(DiscQuote &lhs, DiscQuote &rhs) noexcept;

class DiscQuote : public Quote {

  friend void swap(DiscQuote &lhs, DiscQuote &rhs) noexcept;

 public:
  DiscQuote() = default;
  DiscQuote(const DiscQuote &) = default;
  DiscQuote(DiscQuote &&) noexcept;
  DiscQuote &operator=(const DiscQuote &) &;
  DiscQuote &operator=(DiscQuote &&) & noexcept;
  ~DiscQuote() override = default;

  DiscQuote(const std::string &book, const double &p,
             std::size_t qty, const double &disc)
      : Quote(book, p), quantity_(qty), discount_(disc) {}

  void swap(DiscQuote &rhs) noexcept;

  double NetPrice(std::size_t) const override = 0;
  void Debug() override;

 protected:
  std::size_t quantity_ = 0;  // 折扣适用的购买量
  double discount_ = 0.0;     // 折扣
};

void swap(DiscQuote &lhs, DiscQuote &rhs) noexcept {
  using std::swap;
  lhs.swap(rhs);
}

DiscQuote::DiscQuote(DiscQuote &&rhs) noexcept:
    Quote(std::move(rhs)), quantity_(rhs.quantity_), discount_(rhs.discount_) {}

DiscQuote &DiscQuote::operator=(const DiscQuote &rhs) &{
  if (this == &rhs) {
    return *this;
  }
  Quote::operator=(rhs);
  quantity_ = rhs.quantity_;
  discount_ = rhs.discount_;
  return *this;
}

DiscQuote &DiscQuote::operator=(DiscQuote &&rhs) & noexcept {
  if (this == &rhs) {
    return *this;
  }
  Quote::operator=(std::move(rhs));
  quantity_ = rhs.quantity_;
  discount_ = rhs.discount_;
  return *this;
}

void DiscQuote::swap(DiscQuote &rhs) noexcept {
  using std::swap;
  Quote::swap(rhs);
  swap(quantity_, rhs.quantity_);
  swap(discount_, rhs.discount_);
}

void DiscQuote::Debug() {
  Quote::Debug();
  std::cout << " quantity_: " << quantity_ << " discount_: " << discount_;
}

#endif