#define BOOST_TEST_DYN_LINK


#include <boost/test/unit_test.hpp>
#include "BankAccount.hpp"
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"


#include <string>
#include <list>

BOOST_AUTO_TEST_SUITE(checking_account_suite, * boost::unit_test::timeout(10))

// Constructors
BOOST_AUTO_TEST_CASE(ConstructorWithBalance_SetsFields) {
    CheckingAccount acc("Raffi", "Hovhannisyan", 150.0);    
}
BOOST_AUTO_TEST_CASE(ConstructorWithoutBalance_DefaultsToZero) {
    CheckingAccount acc("Kevork", "Hanounik");    
}   

// write_check()
BOOST_AUTO_TEST_CASE(WriteCheck_Success_TransfersMoneyAndLogs) {
    CheckingAccount writer("Raffi", "Hovhannisyan", 200.0);
    SavingsAccount receiver("Kevork", "Hanounik", 50.0, 0.05);

    bool result = writer.writeCheck(receiver, 40.0);

    BOOST_CHECK_EQUAL(result, true);
    BOOST_CHECK_EQUAL(writer.getBalance(), 160.0);
    BOOST_CHECK_EQUAL(receiver.getBalance(), 90.0);

    std::list<double> log = writer.getCheckLog();
    BOOST_CHECK_EQUAL(log.size(), 1);
    BOOST_CHECK_EQUAL(log.front(), 40.0);
}

BOOST_AUTO_TEST_CASE(WriteCheck_InsufficientFunds_Fails) {
    CheckingAccount writer("Raffi", "Hovhannisyan", 20.0);
    SavingsAccount receiver("Kevork", "Hanounik", 50.0, 0.05);

    bool result = writer.writeCheck(receiver, 100.0);

    BOOST_CHECK_EQUAL(result, false);
    BOOST_CHECK_EQUAL(writer.getBalance(), 20.0);
    BOOST_CHECK_EQUAL(receiver.getBalance(), 50.0);

    BOOST_CHECK(writer.getCheckLog().empty());
}

// get_check_log()
BOOST_AUTO_TEST_CASE(GetCheckLog_ReturnsCopyOfLog) {
    CheckingAccount writer("Raffi", "Hovhannisyan", 100.0);
    SavingsAccount receiver("Kevork", "Hanounik", 10.0, 0.05);

    writer.writeCheck(receiver, 25.0);
    writer.writeCheck(receiver, 15.0);

    std::list<double> log = writer.getCheckLog();

    BOOST_CHECK_EQUAL(log.size(), 2);

    auto it = log.begin();
    BOOST_CHECK_EQUAL(*it++, 25.0);
    BOOST_CHECK_EQUAL(*it, 15.0);
}

// to_string()
BOOST_AUTO_TEST_CASE(ToString_IncludesBalance) {
    CheckingAccount acc("Raffi", "Hovhannisyan", 123.45);

    std::string output = acc.toString();

    BOOST_CHECK(output.find("Checking Account Balance") != std::string::npos);
    BOOST_CHECK(output.find("123.45") != std::string::npos);
}

//serialize()
BOOST_AUTO_TEST_CASE(Serialize_WithoutChecks) {
    CheckingAccount acc("Raffi", "Hovhannisyan", 100.0);

    std::string data = acc.serialize();

    BOOST_CHECK(data.find("checkings,Raffi,Hovhannisyan,100") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(Serialize_WithChecks) {
    CheckingAccount writer("Raffi", "Hovhannisyan", 200.0);
    SavingsAccount receiver("Kevork", "Hanounik", 50.0, 0.05);

    writer.writeCheck(receiver, 30.0);
    writer.writeCheck(receiver, 20.0);

    std::string data = writer.serialize();

    BOOST_CHECK(data.find("checkings,Raffi,Hovhannisyan,150") != std::string::npos);
    BOOST_CHECK(data.find("30") != std::string::npos);
    BOOST_CHECK(data.find("20") != std::string::npos);
}

BOOST_AUTO_TEST_SUITE_END()