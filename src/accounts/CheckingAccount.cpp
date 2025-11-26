#include "CheckingAccount.hpp"

bool CheckingAccount::writeCheck(BankAccount &a, double amount){
    bool success = withdrawal(amount);

    if(success){
        a.deposit(amount);
        checkLog.push_back(amount);
    }

    return success;
}

std::string CheckingAccount::toString(){
    return "Checking Account Balance: $" + std::to_string(getBalance());
}

std::list<double> CheckingAccount::getCheckLog(){
    return checkLog;
}

//*********Task 5 
std::string CheckingAccount::serialize()
{ 
   //drafting:...std::string printed_string = getFirstName() + ","+ getLastName() + "," + getCheckLog() ;
    return std::string();
}
/// ********************************************
