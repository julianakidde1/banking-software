#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "SavingsAccount.hpp"

#include <string>

BOOST_AUTO_TEST_SUITE(savings_account_suite, * boost::unit_test::timeout(10))


// Constructors
BOOST_AUTO_TEST_CASE(Constructor_WithBalanceAndInterest) {
    SavingsAccount acc("Raffi", "Hovhannisyan", 100.0, 0.05);

    BOOST_CHECK_EQUAL(acc.getFirstName(), "Raffi");
    BOOST_CHECK_EQUAL(acc.getLastName(), "Hovhannisyan");
    BOOST_CHECK_EQUAL(acc.getBalance(), 100.0);
    BOOST_CHECK_EQUAL(acc.getInterestRate(), 0.05);
}

BOOST_AUTO_TEST_CASE(Constructor_WithoutInitialBalance) {
    SavingsAccount acc("Raffi", "Hovhannisyan", 0.03);

    BOOST_CHECK_EQUAL(acc.getFirstName(), "Raffi");
    BOOST_CHECK_EQUAL(acc.getLastName(), "Hovhannisyan");
    BOOST_CHECK_EQUAL(acc.getBalance(), 0.0);
    BOOST_CHECK_EQUAL(acc.getInterestRate(), 0.03);
}

// getInterestRate() and setInterestRate()
BOOST_AUTO_TEST_CASE(SetAndGetInterestRate) {
    SavingsAccount acc("Raffi", "Hovhannisyan", 100.0, 0.05);

    acc.setInterestRate(0.1);

    BOOST_CHECK_EQUAL(acc.getInterestRate(), 0.1);
}

// accrueInterest()
BOOST_AUTO_TEST_CASE(AccrueInterest_IncreasesBalance) {
    SavingsAccount acc("Raffi", "Hovhannisyan", 200.0, 0.10);

    acc.accrueInterest();  // 10% of 200 = 20

    BOOST_CHECK_EQUAL(acc.getBalance(), 220.0);
}

BOOST_AUTO_TEST_CASE(AccrueInterest_ZeroBalanceDoesNothing) {
    SavingsAccount acc("Raffi", "Hovhannisyan", 0.0, 0.10);

    acc.accrueInterest();

    BOOST_CHECK_EQUAL(acc.getBalance(), 0.0);
}

// toString()
BOOST_AUTO_TEST_CASE(ToString_IncludesBalanceAndInterest) {
    SavingsAccount acc("Raffi", "Hovhannisyan", 150.0, 0.05);

    std::string output = acc.toString();

    BOOST_CHECK(output.find("Savings Account Balance") != std::string::npos);
    BOOST_CHECK(output.find("150") != std::string::npos);
    BOOST_CHECK(output.find("0.05") != std::string::npos);
}

// serialize()
BOOST_AUTO_TEST_CASE(Serialize_FormatsCorrectly) {
    SavingsAccount acc("Raffi", "Hovhannisyan", 100.0, 0.05);

    std::string data = acc.serialize();

    BOOST_CHECK(data.find("savings,Raffi,Hovhannisyan") != std::string::npos);
    BOOST_CHECK(data.find("100") != std::string::npos);
    BOOST_CHECK(data.find("0.05") != std::string::npos);
}

BOOST_AUTO_TEST_SUITE_END()