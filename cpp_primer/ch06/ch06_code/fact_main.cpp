#include "fact.h"
#include <iostream>
#include <climits>
#include <limits>
#include <stdexcept>

int main(){
	while(true){
		unsigned long n;
		std::cout << "Please enter a number!" << std::endl;
		if(std::cin >> n){
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
                    // 忽略流中的剩余字符直到遇到 '\n'
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
			} else {
                // 流出错 bad or fail, 清除状态
				std::cin.clear();
                // 忽略流中的剩余字符直到遇到 '\n'
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
		}

	}
	return EXIT_SUCCESS;
}
