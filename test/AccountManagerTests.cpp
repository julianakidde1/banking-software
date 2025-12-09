#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "AccountManager.hpp"
#include "SavingsAccount.hpp"
#include "CheckingAccount.hpp"

#include <sstream>
#include <fstream>
#include <iostream>

BOOST_AUTO_TEST_SUITE(account_manager_suite, * boost::unit_test::timeout(10))

//deserialize()
BOOST_AUTO_TEST_CASE(DeserializeLoadsAccounts) {
    AccountManager acc;
    acc.deserialize("test_accounts.txt");

    BOOST_CHECK_EQUAL(acc.getNumAccounts(), 2); // does not find two accounts
}

//displayAccount()  errrrorrrrrrr in hereeeeeeeeeeeeeeeee
BOOST_AUTO_TEST_CASE(DisplayExistingAccount) {
    AccountManager acc;
    acc.deserialize("test_accounts.txt");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    acc.displayAccount("user1");

    std::cout.rdbuf(old);

    BOOST_CHECK(buffer.str().find("A") != std::string::npos); // A - first name
    BOOST_CHECK(buffer.str().find("B") != std::string::npos); // B - last name
}

BOOST_AUTO_TEST_CASE(DisplayNonexistentAccount) {
    AccountManager acc;
    acc.deserialize("test_accounts.txt");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    acc.displayAccount("ghost");

    std::cout.rdbuf(old);

    BOOST_CHECK(buffer.str().find("does not") != std::string::npos ||
                buffer.str().find("taken") != std::string::npos);
}

//makeDeposit()
BOOST_AUTO_TEST_CASE(DepositSuccess) {
    AccountManager acc;
    acc.deserialize("test_accounts.txt");

    acc.makeDeposit("user1", 50);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    acc.displayAccount("user1");

    std::cout.rdbuf(old);

    BOOST_CHECK(buffer.str().find("150") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(DepositAccountMissing) {
    AccountManager acc;
    acc.makeDeposit("ghost", 50);

    BOOST_CHECK_EQUAL(acc.getNumAccounts(), 0);
}

//makeWithdrawal()
BOOST_AUTO_TEST_CASE(WithdrawalSuccess) {
    AccountManager acc;
    acc.deserialize("test_accounts.txt");

    acc.makeWithdrawal("user1", 40);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    acc.displayAccount("user1");

    std::cout.rdbuf(old);

    BOOST_CHECK(buffer.str().find("60") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(WithdrawalAccountMissing) {
    AccountManager acc;
    acc.makeWithdrawal("ghost", 20);

    BOOST_CHECK_EQUAL(acc.getNumAccounts(), 0);
}

//addInterest()
BOOST_AUTO_TEST_CASE(AddInterestSavingsOnly) {
    AccountManager acc;
    acc.deserialize("test_accounts.txt");

    acc.addInterest();

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    acc.displayAccount("user1");

    std::cout.rdbuf(old);

    // interest applied → balance > 100
    BOOST_CHECK(buffer.str().find("100") == std::string::npos);
}

//writeCheck()
BOOST_AUTO_TEST_CASE(WriteCheckSuccess) {
    AccountManager acc;
    acc.deserialize("test_accounts.txt");

    acc.writeCheck("user2", "user1", 50);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    acc.displayAccount("user1");

    std::cout.rdbuf(old);

    BOOST_CHECK(buffer.str().find("150") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(WriteCheckWrongAccountType) {
    AccountManager acc;
    acc.deserialize("test_accounts.txt");

    acc.writeCheck("user1", "user2", 10); // user1 is savings
    BOOST_CHECK_EQUAL(acc.getNumAccounts(), 2);
}

BOOST_AUTO_TEST_CASE(WriteCheckMissingAccounts) {
    AccountManager acc;
    acc.deserialize("test_accounts.txt");

    acc.writeCheck("ghost", "user1", 10);
    BOOST_CHECK_EQUAL(acc.getNumAccounts(), 2);
}

//deleteAccount()
BOOST_AUTO_TEST_CASE(DeleteExistingAccount) {
    AccountManager acc;
    acc.deserialize("test_accounts.txt");

    acc.deleteAccount("user2");

    BOOST_CHECK_EQUAL(acc.getNumAccounts(), 1);
}

BOOST_AUTO_TEST_CASE(DeleteNonexistentAccount) {
    AccountManager acc;
    acc.deserialize("test_accounts.txt");

    acc.deleteAccount("ghost");

    BOOST_CHECK_EQUAL(acc.getNumAccounts(), 2);
}

//serialize()
BOOST_AUTO_TEST_CASE(SerializeCreatesFile) {
    AccountManager acc;
    acc.deserialize("test_accounts.txt");

    acc.serialize("out.txt");

    std::ifstream file("out.txt");
    BOOST_CHECK(file.is_open());

    file.close();
    std::remove("out.txt");
}

BOOST_AUTO_TEST_CASE(constructor_test)
{
    AccountManager am;

    BOOST_CHECK_EQUAL(am.getNumAccounts(), 0);
}   



BOOST_AUTO_TEST_SUITE_END()