#include <iostream>
#include "Sales_data.h"
void test_construct(){
    Sales_data s1;
    Sales_data s2("test");
    Sales_data s3("test", 2, 30);
    Sales_data s4(std::cin);

    print(std::cout, s1); std::cout<<"\n";
    print(std::cout, s2); std::cout<<"\n";
    print(std::cout, s3); std::cout<<"\n";
    print(std::cout, s4); std::cout<<"\n";
}

void test_combine(){
    Sales_data total;
    if(read(std::cin, total)){
        Sales_data trans;
        while(read(std::cin, trans)){
            if(total.isbn() == trans.isbn())
                total.combine(trans);
            else{
                print(std::cout, total);
                std::cout<<"\n";
                total = trans;
            } 
        }
        print(std::cout, total);
    }else{
        std::cerr << "No data!\n";
    }
}

void test_combine_refactor(){ 
    Sales_data total(std::cin);
    if(std::cin){
        Sales_data trans(std::cin);
        while(std::cin){
            if(total.isbn() == trans.isbn())
                total.combine(trans);
            else{
                print(std::cout, total);
                std::cout<<"\n";
                total = std::move(trans);
            } 
            trans = std::move(Sales_data(std::cin));
        }
        print(std::cout, total);
    }else{
        std::cerr << "No data!\n";
    }
}

int main(int argc, char *argv[]){
    test_combine_refactor();
    return 0;
}