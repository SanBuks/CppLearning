include ../../Makefile.inc
date : date.cc date.h
	g++ ${GPP_FLAGS} date.cc -o date.exe
rundate :
	./date.exe
expr : simple_expression.h simple_expression.cc
	g++ ${GPP_FLAGS} simple_expression.cc -o expr.exe
runexpr :
	./expr.exe
atest :
	g++ ${GPP_FLAGS} test.cc -o atest.exe
runatest :
	./atest.exe
clean :
	rm -rf *.exe