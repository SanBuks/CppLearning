#include <iostream>
#include <string>
#include <climits>
#include <memory>

void LockMutex(int *) {
  std::cout << "Lock! \n";
}

void UnlockMutex(int *) {
  std::cout <<"Unlock \n";
}


class Lock {
 public:
  explicit Lock(int *metex_ptr) : mutex_ptr_(metex_ptr, Deleter) {  
    LockMutex(mutex_ptr_.get());
  }
 private:
  void Deleter(int *p) {
    UnlockMutex(p);
  }
  std::shared_ptr<int> mutex_ptr_;
};

int main() {
  {
    int *p = new int(3);
    Lock lock(p);
  }
  return 0;
}