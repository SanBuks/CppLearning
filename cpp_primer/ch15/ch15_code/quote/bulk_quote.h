#ifndef CPP_PRIMER_CH15_CODE_BULK_QUOTE_
#define CPP_PRIMER_CH15_CODE_BULK_QUOTE_

#include "disc_quote.h"

class BulkQuote : public DiscQuote {
 public:
  // 没有数据成员 直接继承父类构造函数
  using DiscQuote::DiscQuote;
  BulkQuote() = default;
  BulkQuote(const BulkQuote &rhs) = default;
  BulkQuote(BulkQuote &&rhs) noexcept;
  BulkQuote &operator=(const BulkQuote &rhs) &;
  BulkQuote &operator=(BulkQuote &&rhs) & noexcept;
  ~BulkQuote() override = default;


  double NetPrice(std::size_t) const override;

  BulkQuote *Clone() const & override { return new BulkQuote(*this); }
  BulkQuote *Clone() && override { return new BulkQuote(std::move(*this)); }
};

double BulkQuote::NetPrice(std::size_t cnt) const {
  auto cnt_double = static_cast<double>(cnt);
  if (cnt >= quantity_) {
    return cnt_double * (1 - discount_) * price_;
  } else {
    return cnt_double * price_;
  }
}

BulkQuote &BulkQuote::operator=(const BulkQuote &rhs) &{
  if (this == &rhs) {
    return *this;
  }
  DiscQuote::operator=(rhs);
  return *this;
}

BulkQuote::BulkQuote(BulkQuote &&rhs) noexcept: DiscQuote(std::move(rhs)) {}

BulkQuote &BulkQuote::operator=(BulkQuote &&rhs) & noexcept {
  if (this == &rhs) {
    return *this;
  }
  DiscQuote::operator=(std::move(rhs));
  return *this;
}

#endif