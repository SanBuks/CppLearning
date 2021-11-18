#ifndef CPP_PRIMER_CH12_CODE_STR_BLOB_ERROR_MESSAGE_H_
#define CPP_PRIMER_CH12_CODE_STR_BLOB_ERROR_MESSAGE_H_

struct StrBlobError {
  static constexpr const char *kPopBackEmptyError = "PopBack On Empty StrBlob";
  static constexpr const char *kFrontEmptyError =   "Front On Empty StrBlob";
  static constexpr const char *kBackEmptyError =    "Back On Empty StrBlob";
  static constexpr const char *kDerefPastEndError = "Deref Past End StrBlob";
};

#endif