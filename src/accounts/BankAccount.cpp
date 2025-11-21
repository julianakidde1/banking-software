#include "BankAccount.hpp"
#include <iostream>

BankAccount::BankAccount(std::string first, std::string last, double initBalance){
    firstName = first;
    lastName = last;
    balance = initBalance;
}

BankAccount::BankAccount(std::string first, std::string last){
    firstName = first;
    lastName = last;
    balance = 0;
}

double BankAccount::getBalance(){
    return balance;
}

std::string BankAccount::getFirstName(){
    return firstName;
}

std::string BankAccount::getLastName(){
    return lastName;
}

void BankAccount::setFirstName(std::string name){
    firstName = name;
}

void BankAccount::setLastName(std::string name){
    lastName = name;
}

bool BankAccount::withdrawal(double amount){
    if(amount > 0){
        if(amount <= balance){
            balance = balance - amount;
            return true;
        }
        else {
            std::cout << "Withdrawal amount greater than balance." << std::endl;
            return false;
        }
    }
    else {
        std::cout << "Invalid amount to withdrawal. Must be positive."<<std::endl;
        return false;
    }
}

bool BankAccount::deposit(double amount){
    if(amount > 0){
        balance = balance + amount;
        return true;
    }
    else {
        std::cout << "Invalid amount to deposit. Must be positive." << std::endl;
        return false;
    }
}