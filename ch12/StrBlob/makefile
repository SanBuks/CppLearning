oobjects=StrBlob.h StrBlobPtr.h SBPP.h StrBlob.cpp StrBlobPtr.cpp Test.cpp
cobjects=StrBlob.cpp StrBlobPtr.cpp Test.cpp
atest: $(oobjects)
	g++ -o atest -g -Wall -std=c++11 \
		$(cobjects)	

.PHONY : clean
clean: 
	rm atest
