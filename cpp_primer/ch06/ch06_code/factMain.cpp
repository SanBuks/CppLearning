#include "fact.h"

int main(){
	while(true){
		unsigned long n;
		std::cout << "Please enter a number!" << std::endl;
		if(std::cin >> n){ // !cin.fail()
			try{
				std::cout << "fact of " << n << " is " << fact(n) << std::endl;
			}catch(std::exception &e){
				std::cout << e.what() << std::endl;
			}
		}else{ 
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Input number is invalid!" << std::endl;
		}

		char c;
		while(true){
			std::cout << "Try again ? y/n\n";
			if(std::cin >> c){
				if(c == 'y')
					break;
				else if(c == 'n')
					return EXIT_SUCCESS;
				else{
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
			} else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
		}

	}
	return EXIT_SUCCESS;
}
