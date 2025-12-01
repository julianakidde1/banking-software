#include <iostream>
#include "AccountManager.hpp"

AccountManager::AccountManager(){
    numAccounts = 0;
}

void AccountManager::addAccount(std::string username){

}
void AccountManager::deleteAccount(std::string username){

}
void AccountManager::displayAccount(std::string username){

}
void AccountManager::makeWithdrawal(std::string username, double amount){

}
void AccountManager::makeDeposit(std::string username, double amount){

}
void AccountManager::addInterest(){

}
void AccountManager::writeCheck(std::string checkWriter, std::string checkReceiver, double amount){

}
int AccountManager::getNumAccounts(){

}

void AccountManager::serialize(std::string filename)
{
   std::ofstream file(filename);

   if (!file.is_open()) {
       std::cout << "Error: Could not open file for writing." << std::endl;
       return;
   }
   else
   {
       for (std::pair< std::string, BankAccount*> pair : accountmanager) { 
           std::string username = pair.first;
           BankAccount* bAccount = pair.second;

           // username + account data from either of the other 2 serialize functions
           // Example: username1 + savings,first,last,balance,rate
           file << username << "," << bAccount->serialize() << std::endl; //writing into the file
       }
   }
  
   file.close();
   std::cout << "Status: Accounts successfully serialized to file." << std::endl;
}

AccountManager::~AccountManager(){}