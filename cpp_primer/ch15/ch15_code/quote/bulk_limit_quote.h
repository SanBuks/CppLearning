#ifndef CPP_PRIMER_CH15_CODE_BULK_LIMIT_QUOTE_
#define CPP_PRIMER_CH15_CODE_BULK_LIMIT_QUOTE_

#include "disc_quote.h"

class BulkLimitQuote : public DiscQuote {
 public:
  BulkLimitQuote() = default;
  BulkLimitQuote(const BulkLimitQuote &) = default;
  BulkLimitQuote(BulkLimitQuote &&) noexcept;
  BulkLimitQuote &operator=(const BulkLimitQuote &) &;
  BulkLimitQuote &operator=(BulkLimitQuote &&) & noexcept;
  ~BulkLimitQuote() override = default;

  BulkLimitQuote(const std::string &book_no, double price,
                 std::size_t quantity, double disc, std::size_t max_qty)
      : DiscQuote(book_no, price, quantity, disc), max_qty_(max_qty) {}

  BulkLimitQuote *Clone() const & override {
    return new BulkLimitQuote(*this);
  }
  BulkLimitQuote *Clone() && override {
    return new BulkLimitQuote(std::move(*this));
  }
  double NetPrice(std::size_t n) const override;
  void Debug() override;

 private:
  std::size_t max_qty_ = 0;
};

double BulkLimitQuote::NetPrice(std::size_t n) const {
  auto n_double = static_cast<double>(n);
  if (n < quantity_) {
    return n_double * price_;
  } else if (quantity_<= n && n <= max_qty_) {
    return n_double * price_ * (1 - discount_);
  } else {
    auto max_qty_double = static_cast<double>(max_qty_);
    return (n_double - max_qty_double) * price_ + max_qty_double * price_ * (1 - discount_);
  }
}

BulkLimitQuote &BulkLimitQuote::operator=(const BulkLimitQuote &rhs) & {
  if (this == &rhs) {
    return *this;
  }
  DiscQuote::operator=(rhs);
  max_qty_ = rhs.max_qty_;
  return *this;
}

BulkLimitQuote::BulkLimitQuote(BulkLimitQuote &&rhs) noexcept
    : DiscQuote(std::move(rhs)), max_qty_(rhs.max_qty_) {}

BulkLimitQuote &BulkLimitQuote::operator=(BulkLimitQuote &&rhs) & noexcept {
  if (this == &rhs) {
    return *this;
  }
  DiscQuote::operator=(std::move(rhs));
  max_qty_ = rhs.max_qty_;
  return *this;
}

void BulkLimitQuote::Debug() {
  DiscQuote::Debug();
  std::cout << " max_qty: " << max_qty_;
}

#endif