#ifndef CPP_PRIMER_CH12_CODE_STR_BLOB_PTR_ERROR_MESSAGE_H_
#define CPP_PRIMER_CH12_CODE_STR_BLOB_PTR_ERROR_MESSAGE_H_

struct StrBlobPtrError {
  static constexpr const char *kUnBoundError =       "Unbound StrBlobPtr";
  static constexpr const char *kIncrefPastEnd =      "Increment Past End";
  static constexpr const char *kDecrefPastBegin =    "Decrement Past Begin";
  static constexpr const char *kDerefPastEnd =       "Deref Past End";
  static constexpr const char *kNotSameStrBlob =     "Not Same StrBlob";
};

#endif