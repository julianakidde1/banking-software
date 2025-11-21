#include "Utils.hpp"
#include <iostream>

BankAccount* make_account(){
    BankAccount *acct = nullptr;

    std::cout << "Enter the first name:"; 
    std::string first;
    std::cin>> first;

    std::cout << "Enter the last name:";
    std::string last;
    std::cin>> last;

    std::cout << "Would you like to make a savings (1) or checking (2) account:" << std::endl;
    std::string choice;
    std::cin>> choice;
    if(choice == "1"){
        std::cout << "Enter the interest rate:";
        std::string interest_rate_string;
        std::cin>> interest_rate_string;

        char *end;
        double interest_rate = strtod(interest_rate_string.c_str(), &end);
        if(*end == '\0'){
            if(interest_rate > 0 && interest_rate < 1){
                acct = new SavingsAccount(first, last, interest_rate);
            }
        }
        else{
            std::cout << "I'm sorry, that is not a valid interest rate." << std::endl;
        }
    }
    else if(choice == "2"){
        acct = new CheckingAccount(first, last);
    }
    else{
        std::cout << "I'm sorry, that is not a valid choice." << std::endl;
    }

    return acct;
}

