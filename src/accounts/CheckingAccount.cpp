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
   // username is handled by AccountManager
   // checkings,first,last,balance,check1,check2,check3...
   std::string data = "checkings," +
       getFirstName() + "," +
       getLastName() + "," +
       std::to_string(getBalance());


   // adding the check log
   for (double checkAmount : checkLog) { //using for each loop to iterate thru checklog
       data += "," + std::to_string(checkAmount);
   }
   return data;
}
/// ********************************************
