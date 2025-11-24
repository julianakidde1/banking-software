#include "BankAccount.hpp"
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"

BankAccount* make_account();

//Task 3: IO Specifications
void statusMessage (std::string a_string); 
void errorMessage (std::string a_string);
std::string getOption();
std::string getString (std::string a_string);
double getDouble (std::string a_string); 