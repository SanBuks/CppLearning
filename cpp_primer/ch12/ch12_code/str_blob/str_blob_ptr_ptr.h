#include <memory>
#include "str_blob.h"

class StrBlobPtrPtr {
 public:
  explicit StrBlobPtrPtr(StrBlobPtr &sbp) : str_blob_ptr_ptr_(&sbp) {}
  StrBlobPtr &operator*() { return *str_blob_ptr_ptr_; }
  StrBlobPtr *operator->() { return &this->operator*(); }
 private:
  StrBlobPtr *str_blob_ptr_ptr_;
};
