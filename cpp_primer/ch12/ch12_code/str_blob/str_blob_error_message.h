#ifndef CPP_PRIMER_CH12_CODE_STR_BLOB_ERROR_MESSAGE_H_
#define CPP_PRIMER_CH12_CODE_STR_BLOB_ERROR_MESSAGE_H_

struct StrBlobErrorMessage {
  static const std::string kPopBackEmptyError;
  static const std::string kFrontEmptyError;
  static const std::string kBackEmptyError;
};

const std::string StrBlobErrorMessage::kPopBackEmptyError = "PopBack on empty StrBlob";
const std::string StrBlobErrorMessage::kFrontEmptyError   = "Front on empty StrBlob";
const std::string StrBlobErrorMessage::kBackEmptyError    = "Back on empty StrBlob";

#endif