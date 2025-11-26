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

 
        std::string input_string = getOption();
        
        if(input_string == "0"){

            statusMessage("Thank you for using the software");
            finished = true;
        }
        else if(input_string == "1"){

            std::string user = getString("Enter the username: ");

            if(accts.find(user) != accts.end()){
                errorMessage("Sorry, that username is taken");
            }
            else{
                BankAccount* acct = make_account();

                if(acct != nullptr){
                    accts[user] = acct;
                }
            }
        }  
        else if(input_string == "2"){

            std::string user = getString("Enter the username: ");

            if(accts.find(user) != accts.end()){

                double deposit_amount = getDouble("Enter Ammount: ");
                
                accts[user]->deposit(deposit_amount);
            
            }
            else{
                errorMessage("I'm sorry, that account does not exist");
            }
        }
        else if(input_string == "3"){
    
            std::string user = getString("Enter the username: ");

            if(accts.find(user) != accts.end()){

                double withdrawal_amount = getDouble("Enter Ammount: ");
                accts[user]->withdrawal(withdrawal_amount);
            }
            else{
                errorMessage("I'm sorry, that account does not exist");
            }
        }
        else if(input_string == "4"){
            std::string user = getString("Enter the username: ");

            if(accts.find(user) != accts.end()){
                std::cout<<accts[user]->toString()<<std::endl;
            }
            else{
                errorMessage("I'm sorry, that account does not exist");
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

            std::string user = getString("Enter the username of the account writing the check: ");

            if(accts.find(user) != accts.end()){
                BankAccount *acct = accts[user];

                if(dynamic_cast<CheckingAccount*>(acct)){
                    CheckingAccount *c = dynamic_cast<CheckingAccount*>(acct);
         
                    std::string target_account = getString("Enter the username of the account cashing the check:");

                    if(accts.find(user) != accts.end()){
              
                        double check_amount = getDouble("Enter Ammount: ");
                        c->writeCheck(*accts[user], check_amount);
                    }
                    else {
                        errorMessage("The given account does not exist");
                    }
                }
                else{
                    errorMessage("The given account is not a checking account");   
                }
            }
            else{
                errorMessage("I'm sorry, that account does not exist");
            }
        }
        else{
            errorMessage("I'm sorry, that is not a valid choice.");
        }
    }

    std::map<std::string, BankAccount*>::iterator it;

    for (it = accts.begin(); it != accts.end(); it++){
        BankAccount *acct = it->second;
        delete acct;
    }

    return 0;
}

