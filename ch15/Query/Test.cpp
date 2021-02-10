#include "./Query/Query.h"

int main(){
	std::ifstream ifs("data");
	if(ifs){
		TextQuery tq(ifs);
		//Query q=Query("fiery") & Query("bird") | Query("wind");
		//q.rep();
		Query q=get_between(1,50, ~Query("In")); //| (~Query("function"));
		print(cout, q.eval(tq));	
	}
	return 0;
}
