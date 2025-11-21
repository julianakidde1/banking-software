#include "BankAccount.hpp"
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"
#include "Utils.hpp"

#include <iostream>
#include <map>

int main(){
    std::cout<<"Welcome to the banking software!"<<std::endl;

    bool finished = false;

    std::map<std::string, BankAccount*> accts;

    while(!finished){
        std::cout<<"Options"<<std::endl;
        std::cout<<"0) Exit"<<std::endl;
        std::cout<<"1) Make account"<<std::endl;
        std::cout<<"2) Deposit to existing account"<<std::endl;
        std::cout<<"3) Withdraw from existing account"<<std::endl;
        std::cout<<"4) Display existing account"<<std::endl;
        std::cout<<"5) Accrue Interest"<<std::endl;
        std::cout<<"6) Write a check"<<std::endl;
        std::cout<<"What would you like to do (Input single number):"<<std::endl;

        std::string input_string;
        std::cin>> input_string;
        if(input_string == "0"){
            std::cout << "Thank you for using the software" << std::endl;
            finished = true;
        }
        else if(input_string == "1"){
            std::cout << "Enter the username:"; 
            std::string user;
            std::cin>> user;

            if(accts.find(user) != accts.end()){
                std::cout << "Sorry, that username is taken" << std::endl;
            }
            else{
                BankAccount* acct = make_account();

                if(acct != nullptr){
                    accts[user] = acct;
                }
            }
        }  
        else if(input_string == "2"){
            std::cout << "Enter the username:"; 
            std::string user;
            std::cin>> user;

            if(accts.find(user) != accts.end()){
                std::cout << "Enter amount:";
                std::string deposit_amount_string;
                std::cin>> deposit_amount_string;
                
                char *end;
                double deposit_amount = strtod(deposit_amount_string.c_str(), &end);
                if(*end == '\0'){
                    accts[user]->deposit(deposit_amount);
                }
                else{
                    std::cout << "I'm sorry, that is not a deposit amount." << std::endl;
                }
            }
            else{
                std::cout << "I'm sorry, that account does not exist" << std::endl;
            }
        }
        else if(input_string == "3"){
            std::cout << "Enter the username:"; 
            std::string user;
            std::cin>> user;

            if(accts.find(user) != accts.end()){
                std::cout << "Enter amount:";
                std::string withdrawal_amount_string;
                std::cin>> withdrawal_amount_string;
                
                char *end;
                double withdrawal_amount = strtod(withdrawal_amount_string.c_str(), &end);
                if(*end == '\0'){
                    accts[user]->withdrawal(withdrawal_amount);
                }
                else{
                    std::cout << "I'm sorry, that is not a withdrawal amount." << std::endl;
                }
            }
            else{
                std::cout << "I'm sorry, that account does not exist" << std::endl;
            }
        }
        else if(input_string == "4"){
            std::cout << "Enter the username:"; 
            std::string user;
            std::cin>> user;

            if(accts.find(user) != accts.end()){
                std::cout<<accts[user]->toString()<<std::endl;
            }
            else{
                std::cout << "I'm sorry, that account does not exist" << std::endl;
            }
        }
        else if(input_string == "5"){
            std::map<std::string, BankAccount*>::iterator it;

            for(it = accts.begin(); it != accts.end(); it++){
                if(dynamic_cast<SavingsAccount*>(it->second)){
                    SavingsAccount *s = dynamic_cast<SavingsAccount*>(it->second);
                    s->accrueInterest();
                }
            }
        }
        else if(input_string == "6"){
            std::cout << "Enter the username of the account writing the check:"; 
            std::string user;
            std::cin>> user;

            if(accts.find(user) != accts.end()){
                BankAccount *acct = accts[user];

                if(dynamic_cast<CheckingAccount*>(acct)){
                    CheckingAccount *c = dynamic_cast<CheckingAccount*>(acct);
                    std::cout << "Enter the username of the account cashing the check:"; 
                    std::string target_account;
                    std::cin>> target_account;

                    if(accts.find(user) != accts.end()){
                        std::cout << "Enter amount:";
                        std::string check_amount_string;
                        std::cin>> check_amount_string;
                        
                        char *end;
                        double check_amount = strtod(check_amount_string.c_str(), &end);
                        if(*end == '\0'){
                            c->writeCheck(*accts[user], check_amount);
                        }
                        else{
                            std::cout << "I'm sorry, that is not a withdrawal amount." << std::endl;
                        }
                    }
                    else {
                        std::cout << "The given account does not exist" << std::endl;
                    }
                }
                else{
                    std::cout << "The given account is not a checking account" << std::endl;
                }
            }
            else{
                std::cout << "I'm sorry, that account does not exist" << std::endl;
            }
        }
        else{
            std::cout << "I'm sorry, that is not a valid choice." << std::endl;
        }
    }

    std::map<std::string, BankAccount*>::iterator it;

    for (it = accts.begin(); it != accts.end(); it++){
        BankAccount *acct = it->second;
        delete acct;
    }

    return 0;
}