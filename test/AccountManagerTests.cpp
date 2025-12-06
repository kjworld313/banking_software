#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <string>
#include "AccountManager.hpp"

BOOST_AUTO_TEST_SUITE(account_manager_suite, * boost::unit_test::timeout(10))

/*
 * Lines Covered: 6, 7, 10, 11
 * Branches Covered: 10T
*/
BOOST_AUTO_TEST_CASE(makeDepositTest1){
    AccountManager accs;
    
    accs.addAccount("lblaney");
    accs.makeDeposit("lblaney", 100.0);

    std::string displaystring = accs.displayAccount("lblaney");
    std::string intendedstring = "First Name: Lucy\nLast Name: Blaney\nBalance: $100.000000\n";
    BOOST_CHECK_EQUAL(displaystring, intendedstring);
}

/*
 * Lines Covered: 6,7,10,15
 * Branches Covered: 15F
*/
BOOST_AUTO_TEST_CASE(makeDepositTest2){
    AccountManager accs;

    accs.addAccount("lblaney");
    BOOST_CHECK_THROW(accs.makeDeposit("bblaney", 100.0), std::out_of_range);
}

/*
 * Lines Covered: 
 * Branches Covered: 
*/
BOOST_AUTO_TEST_CASE(makeWithdrawalTest1){
    AccountManager accs;

    accs.addAccount("lblaney");
    accs.makeDeposit("lblaney", 100.0);
    accs.makeWithdrawal("lblaney", 50.0);

    std::string displaystring = accs.displayAccount("lblaney");
    std::string intendedstring = "First Name: Lucy\nLast Name: Blaney\nBalance: $50.000000\n";

    BOOST_CHECK_EQUAL(displaystring, intendedstring);
}

/*
 * Lines Covered: 
 * Branches Covered: 
*/
BOOST_AUTO_TEST_CASE(makeWithdrawalTest2){
    AccountManager accs;

    accs.addAccount("lblaney");
    BOOST_CHECK_THROW(accs.makeWithdrawal("bblaney", 100.0), std::out_of_range);
}

/**
 * Lines Covered: 90, 102, 105, 106
 * Branches Covered: 90T, 105T
 */ 
// test on addInterest() that should have successful output
BOOST_AUTO_TEST_CASE(add_interest_test1) {
    // arrange
    AccountManager accounts;
    accounts.addAccount("kjworld313"); // must be savings account
    accounts.makeDeposit("kjworld313", 10.00);
    std::string expected_output = "First Name: Kj\nLast Name: World\nBalance: $12.000000\n";

    // act
    accounts.addInterest();

    // assert
    BOOST_CHECK_EQUAL(accounts.displayAccount("kjworld313"), expected_output);
}

/**
 * Lines Covered: 90, 102, 105
 * Branches Covered: 90T, 105F
 */ 
// test on addInterest() that should not accrue interest on a non-savings account
BOOST_AUTO_TEST_CASE(add_interest_test2) {
    // arrange
    AccountManager accounts;
    accounts.addAccount("kjworld313"); // must be checking account (not a savings)
    accounts.makeDeposit("kjworld313", 10.00);
    std::string expected_output = "First Name: Kj\nLast Name: World\nBalance: $10.000000\n";

    // act
    accounts.addInterest();

    // assert
    BOOST_CHECK_EQUAL(accounts.displayAccount("kjworld313"), expected_output);
}

/**
 * Lines Covered: 116, 118, 121, 123, 124, 126, 129, 133
 * Branches Covered: 116T, 121T, 126F, 129F, 133F
 */ 
// test on writeCheck() that should be successful 
BOOST_AUTO_TEST_CASE(write_check_test1) {
    // arrange
    AccountManager accounts;
    accounts.addAccount("kjworld313"); // must be checking account
    accounts.addAccount("riley414"); // can be any type of account
    accounts.makeDeposit("kjworld313", 10.00);
    std::string expected_output1 = "First Name: Kj\nLast Name: World\nBalance: $0.000000\n";
    std::string expected_output2 = "First Name: Riley\nLast Name: Puppy\nBalance: $10.000000\n";

    // act
    accounts.writeCheck("kjworld313", "riley414", 10.00);

    // assert
    BOOST_CHECK_EQUAL(accounts.displayAccount("kjworld313"), expected_output1);
    BOOST_CHECK_EQUAL(accounts.displayAccount("riley414"), expected_output2);
}

/**
 * Lines Covered: 116, 133, 134
 * Branches Covered: 116F, 133T
 */ 
// test on writeCheck() that should not be successful for an invalid check writer username
BOOST_AUTO_TEST_CASE(write_check_test2) {
    // arrange
    AccountManager accounts;
    accounts.addAccount("riley414"); // can be any type of account
    std::string expected_output = "First Name: Riley\nLast Name: Puppy\nBalance: $0.000000\n";

    // act and assert
    BOOST_CHECK_THROW(accounts.writeCheck("kjworld313", "riley414", 10.00), std::invalid_argument);
    BOOST_CHECK_EQUAL(accounts.displayAccount("riley414"), expected_output);
}

/**
 * Lines Covered: 116, 118, 121, 126, 127
 * Branches Covered: 116T, 121F, 126T
 */ 
// test on writeCheck() that should not be successful for an invalid checking account
BOOST_AUTO_TEST_CASE(write_check_test3) {
    // arrange
    AccountManager accounts;
    accounts.addAccount("kjworld313"); // must not be checking account
    accounts.addAccount("riley414"); // can be any type of account
    accounts.makeDeposit("kjworld313", 10.00);
    std::string expected_output1 = "First Name: Kj\nLast Name: World\nBalance: $10.000000\n";
    std::string expected_output2 = "First Name: Riley\nLast Name: Puppy\nBalance: $0.000000\n";

    // act and assert
    BOOST_CHECK_THROW(accounts.writeCheck("kjworld313", "riley414", 10.00), std::invalid_argument);
    BOOST_CHECK_EQUAL(accounts.displayAccount("kjworld313"), expected_output1);
    BOOST_CHECK_EQUAL(accounts.displayAccount("riley414"), expected_output2);
}

/**
 * Lines Covered: 116,118, 121, 126, 129, 130
 * Branches Covered: 116T, 121F, 126F, 129T
 */ 
// test on writeCheck() that should not be successful for an invalid check receiver username
BOOST_AUTO_TEST_CASE(write_check_test4) {
    // arrange
    AccountManager accounts;
    accounts.addAccount("kjworld313"); // must be checking account
    accounts.makeDeposit("kjworld313", 10.00);
    std::string expected_output = "First Name: Kj\nLast Name: World\nBalance: $10.000000\n";

    // act and assert
    BOOST_CHECK_THROW(accounts.writeCheck("kjworld313", "riley414", 10.00), std::invalid_argument);
    BOOST_CHECK_EQUAL(accounts.displayAccount("kjworld313"), expected_output);
}

BOOST_AUTO_TEST_SUITE_END()