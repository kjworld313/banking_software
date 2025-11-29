#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include "BankAccount.hpp"
#include "CheckingAccount.hpp"

BOOST_AUTO_TEST_SUITE(bank_account_suite, * boost::unit_test::timeout(10))

/**
 * Lines covered : 5, 6, 7
 * Branches covered : N/A
 */
// test on parametrized constructor that sets all private data members
BOOST_AUTO_TEST_CASE(constructor1_test) {
    // arrange
    BankAccount* bank_account = nullptr;
    
    // act
    bank_account = new CheckingAccount("John", "Doe", 0.00);

    // assert
    BOOST_CHECK_EQUAL(bank_account->getFirstName(), "John");
    BOOST_CHECK_EQUAL(bank_account->getLastName(), "Doe");
    BOOST_CHECK_EQUAL(bank_account->getBalance(), 0.00);
}

/**
 * Lines covered : 17
 * Branches covered : N/A
 */
// test on balance getter
BOOST_AUTO_TEST_CASE(balance_test) {
    // arrange
    CheckingAccount* account = new CheckingAccount("John", "Doe");

    // act and assert
    BOOST_CHECK_EQUAL(account->getBalance(), 0.00);
}

/**
 * Lines covered : 29
 * Branches covered : N/A
 */
// test on first name setter
BOOST_AUTO_TEST_CASE(set_first_test) {
    // arrange 
    CheckingAccount* account = new CheckingAccount("Jane", "Doe");

    // act and assert
    BOOST_CHECK_EQUAL(account->getFirstName(), "Jane");
}
BOOST_AUTO_TEST_SUITE_END()