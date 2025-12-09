#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include "BankAccount.hpp"
#include "SavingsAccount.hpp"
#include "CheckingAccount.hpp"
#include <sstream>
#include <iostream>


BOOST_AUTO_TEST_SUITE(bank_account_suite, * boost::unit_test::timeout(10))

// Placeholder test case
BOOST_AUTO_TEST_CASE(placeholder_test) {
    BOOST_CHECK_EQUAL(1, 1);
}

// Helper to capture std::cout during a test
struct CoutRedirect {
    std::streambuf* old;
    std::stringstream buffer;

    CoutRedirect() : old(std::cout.rdbuf(buffer.rdbuf())) {}
    ~CoutRedirect() {
        std::cout.rdbuf(old);
    }
};

//Constructer and getters
BOOST_AUTO_TEST_CASE(ConstructorWithBalance_SetsFields) {
    CheckingAccount acc("Raffi", "Hovhannisyan", 150.0);
    BankAccount& base = acc;

    BOOST_CHECK_EQUAL(base.getFirstName(), "Raffi");
    BOOST_CHECK_EQUAL(base.getLastName(), "Hovhannisyan");
    BOOST_CHECK_EQUAL(base.getBalance(), 150.0);
}

BOOST_AUTO_TEST_CASE(ConstructorWithoutBalance_DefaultsToZero) {
    CheckingAccount acc("Kevorg", "Hanounik");
    BankAccount& base = acc;

    BOOST_CHECK_EQUAL(base.getFirstName(), "Kevorg");
    BOOST_CHECK_EQUAL(base.getLastName(), "Hanounik");
    BOOST_CHECK_EQUAL(base.getBalance(), 0.0);
}

//Setters
BOOST_AUTO_TEST_CASE(Setters_UpdateNames) {
    CheckingAccount acc("Raffi", "Hovhannisyan", 100.0);
    BankAccount& base = acc;

    acc.setFirstName("Kevork");
    acc.setLastName("Hanounik");

    BOOST_CHECK_EQUAL(base.getFirstName(), "Kevork");
    BOOST_CHECK_EQUAL(base.getLastName(), "Hanounik");
}

//deposit()
BOOST_AUTO_TEST_CASE(Deposit_PositiveAmount_SucceedsAndAdds) {
    CheckingAccount acc("Raffi", "Hovhannisyan", 100.0);
    BankAccount& base = acc;

    bool result = base.deposit(50.0);

    BOOST_CHECK_EQUAL(result, true);
    BOOST_CHECK_EQUAL(base.getBalance(), 150.0);
}

BOOST_AUTO_TEST_CASE(Deposit_NonPositiveAmount_FailsAndPrints) {
    CheckingAccount acc("Raffi", "Hovhannisyan", 100.0);
    BankAccount& base = acc; 
    CoutRedirect capture;  // redirect std::cout

    bool result = base.deposit(0.0);

    BOOST_CHECK_EQUAL(result, false);
    BOOST_CHECK_EQUAL(base.getBalance(), 100.0);

    std::string out = capture.buffer.str();
    BOOST_CHECK(out.find("Invalid amount to deposit") != std::string::npos);
}

//withdrawal()
BOOST_AUTO_TEST_CASE(Withdrawal_ValidAmount_SucceedsAndSubtracts) {
    CheckingAccount acc("Raffi", "Hovhannisyan", 100.0);
    BankAccount& base = acc;

    bool result = base.withdrawal(40.0);

    BOOST_CHECK_EQUAL(result, true);
    BOOST_CHECK_EQUAL(base.getBalance(), 60.0);
}

BOOST_AUTO_TEST_CASE(Withdrawal_TooLarge_FailsAndPrints) {
    CheckingAccount acc("Raffi", "Hovhannisyan", 100.0);
    BankAccount& base = acc;
    CoutRedirect capture;

    bool result = base.withdrawal(150.0);

    BOOST_CHECK_EQUAL(result, false);
    BOOST_CHECK_EQUAL(base.getBalance(), 100.0);

    std::string out = capture.buffer.str();
    BOOST_CHECK(out.find("greater than balance") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(Withdrawal_NonPositive_FailsAndPrints) {
    CheckingAccount acc("Raffi", "Hovhannisyan", 100.0);
    BankAccount& base = acc;
    CoutRedirect capture;

    bool result = base.withdrawal(0.0);

    BOOST_CHECK_EQUAL(result, false);
    BOOST_CHECK_EQUAL(base.getBalance(), 100.0);

    std::string out = capture.buffer.str();
    BOOST_CHECK(out.find("Invalid amount to withdrawal") != std::string::npos);
}


BOOST_AUTO_TEST_SUITE_END()