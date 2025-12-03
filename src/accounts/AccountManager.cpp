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
            statusMessage("Account created succesffully for " + username);
        }
    }
    else{
        errorMessage("Username " + username + " is already taken.");
    }
}
void AccountManager::deleteAccount(std::string username){
    auto it = accountmanager.find(username);
    if (it != accountmanager.end()){
        delete it->second;
        accountmanager.erase(it);
        numAccounts--;
        statusMessage("Account for " + username + " deleted.");
    }
    else{
        errorMessage("Account " + username + " does not exist.");
    }

}
void AccountManager::displayAccount(std::string username){
    auto it = accountmanager.find(username);
    if (it != accountmanager.end()){
        std::cout << it->second->toString() << std::endl;
    }
    else{
        errorMessage("Account " + username + " is already taken.");
    }

}
void AccountManager::makeWithdrawal(std::string username, double amount){
    auto it = accountmanager.find(username);
    if (it != accountmanager.end()) {
        if(it->second->withdrawal(amount)){
            statusMessage("Withdrawal successful! New Balance: " + std::to_string(it->second->getBalance()));
        }
    }
    else{
        errorMessage("Account " + username + " does not exist.");
    }
}
void AccountManager::makeDeposit(std::string username, double amount){
    auto it = accountmanager.find(username);
    if (it != accountmanager.end()) {
        if(it->second->deposit(amount)){
            statusMessage("Deposit successful! New Balance: " + std::to_string(it->second->getBalance()));
        }
    }
    else{
        errorMessage("Account " + username + " does not exist.");
    }
}
void AccountManager::addInterest(){
    for (auto const& pair : accountmanager){
        SavingsAccount* savings = dynamic_cast<SavingsAccount*>(pair.second);

        if(savings){
            savings->accrueInterest();
        }
    }
    statusMessage("Interest added to all savings accounts.");
}
void AccountManager::writeCheck(std::string checkWriter, std::string checkReceiver, double amount){
    auto writeIt = accountmanager.find(checkWriter);
    auto receiverIt = accountmanager.find(checkReceiver);

    if (writeIt != accountmanager.end() && receiverIt != accountmanager.end()) {
        CheckingAccount* writer = dynamic_cast<CheckingAccount*>(writeIt->second);
        if(writer){
            if(writer->writeCheck(*(receiverIt->second), amount)){
                statusMessage("Check written successfully!");
            }
        }
        else{
            errorMessage("Writer account " + checkWriter + " is not a checking account.");
        }
    }
    else{
        errorMessage("One or both account usernames provided do not exist.");
    }
}
int AccountManager::getNumAccounts(){
    return numAccounts;
}

void AccountManager::serialize(std::string filename){
    std::ofstream file(filename);

    if (!file.is_open()){
        std::cout << "Error: Could not open file for writing." << std::endl;
        return;
    }
    else{
        for (std::pair< std::string, BankAccount*> pair : accountmanager) {
            std::string username = pair.first;
            BankAccount* bAccount = pair.second;
            file << username << "," << bAccount->serialize() << std::endl;
        }
    }

    file.close();
    statusMessage("Accounts successfully serialized to file.");
}

// Task 7

void AccountManager::deserialize(std::string filename){
   std::ifstream file(filename);


   if (!file.is_open()) {
       std::cout << "Error: Could not open file for reading." << std::endl;
       return;
   }


   std::string line;


   while (std::getline(file, line)){
    
    if (line.empty())
        continue;

    std::stringstream ss(line);
    std::string field;
    std::vector<std::string> parts;


    while(std::getline(ss, field, ',')){
        parts.push_back(field);
    }

    std::string username = parts[0];
    std::string acctType = parts[1];
    std::string first = parts[2];
    std::string last = parts[3];
    double balance = std::stod(parts[4]);


    BankAccount* account = nullptr;

    if (acctType == "savings") {
        // savings,first,last,balance,interestRate
        double rate = std::stod(parts[5]);
        account = new SavingsAccount(first, last, balance, rate);


    } else if (acctType == "checkings"){
        // checkings,first,last,balance,check1,check2,...
        CheckingAccount* c = new CheckingAccount(first, last, balance);
        
        for (size_t i = 5; i < parts.size(); i++)
        {
            double amount = std::stod(parts[i]);
            c->getCheckLog().push_back(amount);
        }

        account = c;


    } else {
        std::cout << "Unknown account type." << acctType << std::endl;
    }


    if (account != nullptr) {
        accountmanager[username] = account;
        numAccounts += 1; 
    }

    file.close();
    std::cout << "Status: Accounts successfully deserialized from file." << std::endl;

   }


}

AccountManager::~AccountManager(){
    for (auto const& pair : accountmanager){
        delete pair.second;
    }
    accountmanager.clear();
}