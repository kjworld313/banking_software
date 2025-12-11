#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include "CheckingAccount.hpp"

BOOST_AUTO_TEST_SUITE(bank_account_suite, * boost::unit_test::timeout(10))

/**
 * Lines Covered: 6, 7, 8, 18, 22, 26
 * Branches Covered: N/A
 */
// test on parametrized constructor that sets all private data members
BOOST_AUTO_TEST_CASE(constructor1_test) {
    // arrange
    BankAccount* bank_account = nullptr;
    
    // act
    bank_account = new CheckingAccount("John", "Doe", 10.00);

    // assert
    BOOST_CHECK_EQUAL(bank_account->getFirstName(), "John");
    BOOST_CHECK_EQUAL(bank_account->getLastName(), "Doe");
    BOOST_CHECK_EQUAL(bank_account->getBalance(), 10.00);
}

/**
 * Lines Covered: 12, 13, 14, 18, 22, 26
 * Branches Covered: N/A
 */
BOOST_AUTO_TEST_CASE(constructor2_test) {
    // arrange
    BankAccount* bank_account = nullptr;

    // act
    bank_account = new CheckingAccount("John", "Doe");

    // assert
    BOOST_CHECK_EQUAL(bank_account->getFirstName(), "John");
    BOOST_CHECK_EQUAL(bank_account->getLastName(), "Doe");
    BOOST_CHECK_EQUAL(bank_account->getBalance(), 0.00); // default balance
}

/**
 * Lines Covered: 12, 13, 14, 17
 * Branches Covered: N/A
 */
// test on balance getter
BOOST_AUTO_TEST_CASE(balance_test) {
    // arrange
    CheckingAccount* account = new CheckingAccount("John", "Doe");

    // act and assert
    BOOST_CHECK_EQUAL(account->getBalance(), 0.00);
}

/**
 * Lines Covered: 12, 13, 14, 22, 30
 * Branches Covered: N/A
 */
BOOST_AUTO_TEST_CASE(set_first_test) {
    CheckingAccount* account = new CheckingAccount("Jane", "Doe");

    account->setFirstName("Nima");

    BOOST_CHECK_EQUAL(account->getFirstName(), "Nima");
}


/**
 * Lines Covered: 12, 13, 14, 26, 34,
 * Branches Covered: N/A
 */
BOOST_AUTO_TEST_CASE(set_last_name_test) {
    // arrange 
    CheckingAccount* account = new CheckingAccount("Jane", "Doe");

    // act 
    account->setLastName("Blaney");

    // assert
    BOOST_CHECK_EQUAL(account->getLastName(), "Blaney");
}

/**
 * Lines Covered: 12, 13, 14, 22
 * Branches Covered: N/A
 */
BOOST_AUTO_TEST_CASE(get_first_name_test) {
    // arrange 
    CheckingAccount* account = new CheckingAccount("John", "Doe");

    // act & assert
    BOOST_CHECK_EQUAL(account->getFirstName(), "John");
}

/**
 * Lines Covered: 12, 13, 14, 26
 * Branches Covered: N/A
 */
BOOST_AUTO_TEST_CASE(get_last_name_test) {
    // arrange 
    CheckingAccount* account = new CheckingAccount("John", "Doe");

    // act & assert
    BOOST_CHECK_EQUAL(account->getLastName(), "Doe");
}

/**
 * Lines Covered: 12, 13, 14, 18, 38, 39, 40, 41
 * Branches Covered: 38T
 */
// test on withdrawal function with balance equal to a nonzero amount
BOOST_AUTO_TEST_CASE(nonzero_true_withdrawal_test) { // true return case
    // arrange
    CheckingAccount* account = new CheckingAccount("Jane", "Doe", 10.00);

    // act 
    account->withdrawal(10.00);

    // assert
    BOOST_CHECK_EQUAL(account->getBalance(), 0.00); // balance should be 0 (successful)
}

/**
 * Lines Covered: 12, 13, 14, 18, 38, 39, 44, 45
 * Branches Covered: 38T, 39F
 */
// test on withdrawal function with empty balance and nonzero amount
BOOST_AUTO_TEST_CASE(nonzero_false_withdrawal_test) { // false return case
    // arrange
    CheckingAccount* account = new CheckingAccount("Jane", "Doe");

    // act 
    account->withdrawal(10.00);

    // assert
    BOOST_CHECK_EQUAL(account->getBalance(), 0.00); // balance should still be 0
}

/**
 * Lines Covered: 12, 13, 14, 18, 38, 49, 50
 * Branches Covered: 37F
 */
// test on withdrawal function with zero amount
BOOST_AUTO_TEST_CASE(zero_amount_withdrawal_test) { // false return case
    // arrange
    CheckingAccount* account = new CheckingAccount("Jane", "Doe", 10.00);

    // act 
    account->withdrawal(0.00);

    // assert
    BOOST_CHECK_EQUAL(account->getBalance(), 10.00); // balance should still be 10
}


/**
 * Lines Covered: 12, 13, 14, 18, 55, 56, 57
 * Branches Covered: 55T
 */
BOOST_AUTO_TEST_CASE(deposit_positive_test) {
    CheckingAccount* account = new CheckingAccount("Nima", "Dahir", 10.00);

    account->deposit(5.00); // deposit positive amount

    BOOST_CHECK_EQUAL(account->getBalance(), 15.00);
}

/**
 * Lines Covered: 12, 13, 14, 18, 55, 60, 61
 * Branches Covered: 55F
 */
BOOST_AUTO_TEST_CASE(deposit_zero_test) {
    CheckingAccount* account = new CheckingAccount("Nima", "Dahir", 10.00);

    account->deposit(0.00); // deposit zero (invalid)

    BOOST_CHECK_EQUAL(account->getBalance(), 10.00); // balance should not change
}

/**
 * Lines Covered: 12, 13, 14, 18, 55, 60, 61
 * Branches Covered: 55F
 */
BOOST_AUTO_TEST_CASE(deposit_negative_test) {
    CheckingAccount* account = new CheckingAccount("Nima", "Dahir", 10.00);

    account->deposit(-5.00); // deposit negative (invalid)

    BOOST_CHECK_EQUAL(account->getBalance(), 10.00); // balance should not change
}



BOOST_AUTO_TEST_SUITE_END()