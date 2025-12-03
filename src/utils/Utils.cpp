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

//Task 3: IO Specifications
void statusMessage (std::string a_string){
    std::cout <<"Status:"<< a_string << std::endl;
}
void errorMessage (std::string a_string){
    std::cout <<"Error:"<< a_string << std::endl;
}    
std::string getOption(){
    std::string input; 
    std::cout<<"Options"<<std::endl;
    std::cout<<"0) Exit"<<std::endl;
    std::cout<<"1) Make account"<<std::endl;
    std::cout<<"2) Deposit to existing account"<<std::endl;
    std::cout<<"3) Withdraw from existing account"<<std::endl;
    std::cout<<"4) Display existing account"<<std::endl;
    std::cout<<"5) Accrue Interest"<<std::endl;
    std::cout<<"6) Write a check"<<std::endl;
    std::cout<<"What would you like to do (Input single number):"<<std::endl;

    std::cin >> input; 
    return input; 

}

std::string getString (std::string a_string){
    std::string string_input;
    std::cout<< a_string << std::endl; 
    std::cin >> string_input;

    return string_input;

}

double getDouble (std::string a_string) {
    std::string string_input;
    std::cout<< a_string << std::endl; 
    std::cin >> string_input;

   char *end;
        double double_input = strtod(string_input.c_str(), &end);
        if(*end == '\0'){
            return double_input; 
        }
        else{
            std::cout << "Invalid input; it should be a double." << std::endl;
        }
}

