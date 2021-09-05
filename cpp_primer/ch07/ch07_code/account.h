#pragma once
#include <string>
#include <iostream>
class Account{
public:
    Account(const std::string &_owner, double _amount) : owner(_owner), amount(_amount) {}

    void calculate(){ amount += amount * interestRate;}
    double getAmount() const { return amount; }

    static double rate() { return interestRate; }
    static void rate(double);
private:
    std::string owner;
    double amount;

    static double interestRate;
};

double Account::interestRate = 0.01;
void Account::rate(double newRate){
    interestRate = newRate;
}

void testAmount(){
    Account account("James", 10000);
    Account::rate(0.80);
    account.calculate();
    std::cout<<account.getAmount();
}