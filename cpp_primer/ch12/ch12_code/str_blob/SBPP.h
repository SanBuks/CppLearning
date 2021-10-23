#include <memory>
#include "StrBlob.h"
class SBPP{
private:
	std::shared_ptr<StrBlobPtr> sbpp;
public:
	SBPP()=default;
	SBPP(const StrBlobPtr &sbp):sbpp(std::make_shared<StrBlobPtr>(sbp)){}

	StrBlobPtr &operator*(){
		return *sbpp;
	}

	StrBlobPtr *operator->(){
		return & this->operator*();
	}
};
