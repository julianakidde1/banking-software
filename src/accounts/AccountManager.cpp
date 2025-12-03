#include <iostream>
#include "AccountManager.hpp"
#include "Utils.hpp"
#include "SavingsAccount.hpp"
#include "CheckingAccount.hpp"

AccountManager::AccountManager(){
    numAccounts = 0;
}

void AccountManager::addAccount(std::string username){
    if(accountmanager.find(username) == accountmanager.end()){
        BankAccount* newAccount = make_account();

        if(newAccount != nullptr){
            accountmanager[username] = newAccount;
            numAccounts++;
            std::cout << "Account created successfully for " << username << "." << std::endl;
        }
        else{
            std::cout << "Error: Username " << username << " already exists." << std::endl;
        }
    }
}
void AccountManager::deleteAccount(std::string username){
    auto it = accountmanager.find(username);
    if (it != accountmanager.end()){
        delete it->second;
        accountmanager.erase(it);
        numAccounts--;
        std::cout << "Account for " << username << " deleted." << std::endl;
    }
    else{
        std::cout << "Error: Account " << username << " does not exist." << std::endl;
    }

}
void AccountManager::displayAccount(std::string username){
    auto it = accountmanager.find(username);
    if (it != accountmanager.end()){
        std::cout << it->second->toString() << std::endl;
    }
    else{
        std::cout << "Error: Account " << username << " does not exist." << std::endl;
    }

}
void AccountManager::makeWithdrawal(std::string username, double amount){
    auto it = accountmanager.find(username);
    if (it != accountmanager.end()) {
        if(it->second->withdrawal(amount)){
            std::cout << "Withdrawal successful. New balance: " << it->second->getBalance() << std::endl;
        }
    }
    else{
        std::cout << "Error: Account " << username << " does not exist." << std::endl;
    }
}
void AccountManager::makeDeposit(std::string username, double amount){
    auto it = accountmanager.find(username);
    if (it != accountmanager.end()) {
        if(it->second->deposit(amount)){
            std::cout << "Deposit successful. New balance: " << it->second->getBalance() << std::endl;
        }
    }
    else{
        std::cout << "Error: Account " << username << " does not exist." << std::endl;
    }
}
void AccountManager::addInterest(){
    for (auto const& pair : accountmanager){
        SavingsAccount* savings = dynamic_cast<SavingsAccount*>(pair.second);

        if(savings){
            savings->accrueInterest();
        }
    }
    std::cout << "Interest added to all savings accounts." << std::endl; 
}
void AccountManager::writeCheck(std::string checkWriter, std::string checkReceiver, double amount){
    auto writeIt = accountmanager.find(checkWriter);
    auto receiverIt = accountmanager.find(checkReceiver);

    if (writeIt != accountmanager.end() && receiverIt != accountmanager.end()) {
        CheckingAccount* writer = dynamic_cast<CheckingAccount*>(writeIt->second);
        if(writer){
            if(writer->writeCheck(*(receiverIt->second), amount)){
                std::cout << "Check written successfully!" << std::endl;
            }
        }
        else{
            std::cout << "Error: Writer account " << checkWriter << " is not a checking account." << std::endl;
        }
    }
    else{
        std::cout << "Error: One or both account usernames provided do not exist." << std::endl;
    }
}
int AccountManager::getNumAccounts(){
    return numAccounts;
}

AccountManager::~AccountManager(){
    for (auto const& pair : accountmanager){
        delete pair.second;
    }
    accountmanager.clear();
}