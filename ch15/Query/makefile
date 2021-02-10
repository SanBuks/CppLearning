text_querys=TextQuery/TextQuery.h TextQuery/QueryResult.h UsingTools.h

query_bases=UsingTools.h \
			$(text_querys)\
			Query/Query.h\
			Query_base/Query_base.h 

binary_querys=$(query_bases) Query_base/BinaryQuery.h 

querys=Query/Query.h $(query_bases)


atest : Query.o Query_base.o BinaryQuery.o TextQuery.o Test.o
	g++ Query.o Query_base.o BinaryQuery.o TextQuery.o Test.o \
		-o atest -g -Wall -std=c++11

Test.o : $(binary_querys) Test.cpp
	g++ -c Test.cpp -g -std=c++11 -Wall

Query.o : $(querys) Query/Query.cpp
	g++ -c Query/Query.cpp -g -std=c++11 -Wall

BinaryQuery.o : $(binary_querys) Query_base/BinaryQuery.cpp
	g++ -c Query_base/BinaryQuery.cpp -g -std=c++11 -Wall 

Query_base.o : $(query_bases) Query_base/Query_base.cpp
	g++ -c Query_base/Query_base.cpp -g -std=c++11 -Wall 

TextQuery.o : $(text_querys) TextQuery/TextQuery.cpp
	g++ -c TextQuery/TextQuery.cpp -g -std=c++11 -Wall 

.PHONY : clean
clean :
	rm -f *.o atest
