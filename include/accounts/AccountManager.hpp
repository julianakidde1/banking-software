#ifndef ACCOUNTMANAGER_HPP
#define ACCOUNTMANAGER_HPP

#include <string>
#include <map>
#include <fstream> //task 5
#include <sstream> // task 7
#include <vector> // task 7
#include "BankAccount.hpp"

class AccountManager{
public:
    AccountManager();
    void addAccount(std::string username);
    void deleteAccount(std::string username);
    void displayAccount(std::string username);
    void makeWithdrawal(std::string username, double amount);
    void makeDeposit(std::string username, double amount);
    void addInterest();
    void writeCheck(std::string checkWriter, std::string checkReceiver, double amount);
    int getNumAccounts();

    ///Task 5 ****
    void serialize(std::string filename);

    //Task 7
    void deserialize(std::string filename);

    
    ~AccountManager();



private:
    int numAccounts;
    std::map<std::string, BankAccount*> accountmanager;

};

#endif