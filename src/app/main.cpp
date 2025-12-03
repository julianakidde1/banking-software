#include "BankAccount.hpp"
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"
#include "Utils.hpp"
#include "AccountManager.hpp" //Task 6

#include <iostream>


int main(){
    std::cout<<"Welcome to the banking software!"<<std::endl;

    bool finished = false;
    
    AccountManager manager; // Task 6

    while(!finished){

 
        std::string input_string = getOption();
        
        if(input_string == "0"){
            // Task 6: Calling the serialize function to save the accounts before the app exits
            manager.serialize("accounts.csv");

            statusMessage("Thank you for using the software");
            finished = true;

        }
        else if(input_string == "1"){
            std::string user = getString("Enter the username: ");
            // handled by AccountManager
            manager.addAccount(user);
        }  
        else if(input_string == "2"){
            std::string user = getString("Enter the username: ");
            double amount = getDouble("Enter Amount: ");
            manager.makeDeposit(user, amount);
        }
        else if(input_string == "3"){
            std::string user = getString("Enter the username: ");
            double amount = getDouble("Enter Amount: ");
            manager.makeWithdrawal(user, amount);
        }
        else if(input_string == "4"){
            std::string user = getString("Enter the username: ");
            manager.displayAccount(user);
        }
        else if(input_string == "5"){
            manager.addInterest();
        }
        else if(input_string == "6"){

            std::string writer = getString("Enter the username of the account writing the check: ");
            std::string receiver = getString("Enter the username of the account cashing the check: ");
            double amount = getDouble("Enter amount: ");

            manager.writeCheck(writer, receiver, amount);
        }
        else{
            errorMessage("I'm sorry, that is not a valid choice.");
        }
    }
    return 0;
}

