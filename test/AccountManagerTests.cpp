#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <string>
#include "AccountManager.hpp"

// note the space before the '.' indicating root directory. do not include space
// ./test/bank_account_tests <<< "Lucy Blaney 2 Lucy Blaney 2 Lucy Blaney 2 Lucy Blaney 2 Kj World 1 0.2 Riley Puppy 2 Kj World 2 Riley Puppy 2 Riley Puppy 2 Kj World 1 0.2 Riley Puppy 2 Kj World 2 User One 2 User Two 2 User Three 2 User Four 2 John Doe 2"

BOOST_AUTO_TEST_SUITE(account_manager_suite, * boost::unit_test::timeout(10))

/*
 * Lines Covered: 6, 7, 10, 11
 * Branches Covered: 10T
*/
BOOST_AUTO_TEST_CASE(makeDepositTest1){
    AccountManager accs;
    
    accs.addAccount("lblaney");
    accs.makeDeposit("lblaney", 100.0);

    std::string display_string = accs.displayAccount("lblaney");
    std::string expected_string = "First Name: Lucy\nLast Name: Blaney\nBalance: $100.000000\n";
    BOOST_CHECK_EQUAL(display_string, expected_string);
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

    std::string display_string = accs.displayAccount("lblaney");
    std::string expected_string = "First Name: Lucy\nLast Name: Blaney\nBalance: $50.000000\n";

    BOOST_CHECK_EQUAL(display_string, expected_string);
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
 * Lines Covered: 103, 105, 108, 109
 * Branches Covered: 103T, 108T
 */ 
// test on addInterest() that makes sure only savings accounts accrue interest
BOOST_AUTO_TEST_CASE(add_interest_test1) {
    // arrange
    AccountManager accounts;
    accounts.addAccount("kjworld313"); // must be savings account
    accounts.addAccount("riley414"); // must be non-savings account
    accounts.makeDeposit("kjworld313", 10.00);
    accounts.makeDeposit("riley414", 10.00);
    std::string expected_string1 = "First Name: Kj\nLast Name: World\nBalance: $12.000000\n";
    std::string expected_string2 = "First Name: Riley\nLast Name: Puppy\nBalance: $10.000000\n";

    // act
    accounts.addInterest();

    // assert
    BOOST_CHECK_EQUAL(accounts.displayAccount("kjworld313"), expected_string1);
    BOOST_CHECK_EQUAL(accounts.displayAccount("riley414"), expected_string2);
}

/**
 * Lines Covered: 117, 119, 122, 124, 125
 * Branches Covered: 117T, 122T
 */ 
// test on writeCheck() that should be successful 
BOOST_AUTO_TEST_CASE(write_check_test1) {
    // arrange
    AccountManager accounts;
    accounts.addAccount("kjworld313"); // must be checking account
    accounts.addAccount("riley414"); // can be any type of account
    accounts.makeDeposit("kjworld313", 10.00);
    std::string expected_string1 = "First Name: Kj\nLast Name: World\nBalance: $0.000000\n";
    std::string expected_string2 = "First Name: Riley\nLast Name: Puppy\nBalance: $10.000000\n";

    // act
    accounts.writeCheck("kjworld313", "riley414", 10.00);

    // assert
    BOOST_CHECK_EQUAL(accounts.displayAccount("kjworld313"), expected_string1);
    BOOST_CHECK_EQUAL(accounts.displayAccount("riley414"), expected_string2);
}

/**
 * Lines Covered: 117, 134, 135
 * Branches Covered: 117F, 134T
 */ 
// test on writeCheck() that should not be successful for an invalid check writer username
BOOST_AUTO_TEST_CASE(write_check_test2) {
    // arrange
    AccountManager accounts;
    accounts.addAccount("riley414"); // can be any type of account
    std::string expected_string = "First Name: Riley\nLast Name: Puppy\nBalance: $0.000000\n";

    // act and assert
    BOOST_CHECK_THROW(accounts.writeCheck("kjworld313", "riley414", 10.00), std::invalid_argument);
    BOOST_CHECK_EQUAL(accounts.displayAccount("riley414"), expected_string);
}

/**
 * Lines Covered: 117, 119, 122, 127, 128
 * Branches Covered: 117T, 122F, 127T
 */ 
// test on writeCheck() that should not be successful for an invalid checking account
BOOST_AUTO_TEST_CASE(write_check_test3) {
    // arrange
    AccountManager accounts;
    accounts.addAccount("kjworld313"); // must not be checking account
    accounts.addAccount("riley414"); // can be any type of account
    accounts.makeDeposit("kjworld313", 10.00);
    std::string expected_string1 = "First Name: Kj\nLast Name: World\nBalance: $10.000000\n";
    std::string expected_string2 = "First Name: Riley\nLast Name: Puppy\nBalance: $0.000000\n";

    // act and assert
    BOOST_CHECK_THROW(accounts.writeCheck("kjworld313", "riley414", 10.00), std::invalid_argument);
    BOOST_CHECK_EQUAL(accounts.displayAccount("kjworld313"), expected_string1);
    BOOST_CHECK_EQUAL(accounts.displayAccount("riley414"), expected_string2);
}

/**
 * Lines Covered: 117, 119, 122, 127, 130, 131
 * Branches Covered: 117T, 122F, 127F, 130T
 */ 
// test on writeCheck() that should not be successful for an invalid check receiver username
BOOST_AUTO_TEST_CASE(write_check_test4) {
    // arrange
    AccountManager accounts;
    accounts.addAccount("kjworld313"); // must be checking account
    accounts.makeDeposit("kjworld313", 10.00);
    std::string expected_string = "First Name: Kj\nLast Name: World\nBalance: $10.000000\n";

    // act and assert
    BOOST_CHECK_THROW(accounts.writeCheck("kjworld313", "riley414", 10.00), std::invalid_argument);
    BOOST_CHECK_EQUAL(accounts.displayAccount("kjworld313"), expected_string);
}

/**
 * Lines Covered: 66, 67, 71, 74, 77, 79
 * Branches Covered: 66T
 */
// test deleteaccount function
BOOST_AUTO_TEST_CASE(delete_account_test) {
    AccountManager accounts;
    accounts.addAccount("user1"); // assume make_account creates a valid checkingaccount

    // successful delete
    BOOST_CHECK_NO_THROW(accounts.deleteAccount("user1"));
    BOOST_CHECK_EQUAL(accounts.getNumAccounts(), 0);

    // delete non-existent account
    BOOST_CHECK_THROW(accounts.deleteAccount("user1"), std::invalid_argument);
}

/**
 * Lines Covered: 84, 85
 * Branches Covered: 84T
 */
// test displayaccount function
BOOST_AUTO_TEST_CASE(display_account_test) {
    AccountManager accounts;
    accounts.addAccount("user2"); 
    // expected output based on default values for the account
    std::string expected_string = 
        "First Name: User\n"
        "Last Name: Two\n"
        "Balance: $0.000000\n";

    // check that displayAccount returns the expected string
    BOOST_CHECK_EQUAL(accounts.displayAccount("user2"), expected_string);

    // check that displaying a non-existent account throws an exception
    BOOST_CHECK_THROW(accounts.displayAccount("no_user"), std::invalid_argument);
}

/**
 * Lines Covered: 97
 * Branches Covered: None
 */
// test getter for number of accounts
BOOST_AUTO_TEST_CASE(get_num_accounts_test) {
    AccountManager accounts;
    BOOST_CHECK_EQUAL(accounts.getNumAccounts(), 0);

    accounts.addAccount("user3");
    BOOST_CHECK_EQUAL(accounts.getNumAccounts(), 1);

    accounts.addAccount("user4");
    BOOST_CHECK_EQUAL(accounts.getNumAccounts(), 2);
}

/** 
 * Lines Covered: 142, 143
 * Branches Covered: 142T
 */
// test serialize function with no accounts
BOOST_AUTO_TEST_CASE(throw_serialize_test) {
    // arrange
    AccountManager accounts;

    // act and assert
    BOOST_CHECK_THROW(accounts.serialize("test_file"), std::out_of_range);
}

/**
 * Lines Covered: 142, 147, 148, 151, 152
 * Branches Covered: 142F 151T
 */

 // test serialize function with file open failure (attempting to write to a directory)
 BOOST_AUTO_TEST_CASE(file_failure_serialize_test) {
    // arrange
    AccountManager accounts;
    accounts.addAccount("johndoe");

    // act and assert
    BOOST_CHECK_THROW(accounts.serialize("./test/"), std::runtime_error);
 }

 /**
  * Lines Covered: 142, 147, 148, 151, 156, 
  */

BOOST_AUTO_TEST_SUITE_END()