#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <string>
#include "AccountManager.hpp"

// note the space before the '.' indicating root directory. do not include space
// ./test/bank_account_tests <<< "Lucy Blaney 2 Lucy Blaney 2 Lucy Blaney 2 Lucy Blaney 2 Kj World 1 0.2 Riley Puppy 2 Kj World 2 Riley Puppy 2 Kj World 1 0.2 Riley Puppy 2 Kj World 2 User One 2 User Two 2 User Three 2 User Four 2 John Doe 2 User One 2 User Two 2 User Three 1 0.01 User One 2 User Two 2 User Three 1 0.01 Lucy Blaney 2"

BOOST_AUTO_TEST_SUITE(account_manager_suite, * boost::unit_test::timeout(10))

/*
 * Lines Covered: 22, 27, 29, 34, 35, 37, 42, 45, 46, 86, 90, 93, 94
 * Branches Covered: 22F, 29F, 45T, 86F
*/
BOOST_AUTO_TEST_CASE(make_deposit_test1){
    AccountManager accs;
    
    accs.addAccount("lblaney");
    accs.makeDeposit("lblaney", 100.0);

    std::string display_string = accs.displayAccount("lblaney");
    std::string expected_string = "First Name: Lucy\nLast Name: Blaney\nBalance: $100.000000\n";
    BOOST_CHECK_EQUAL(display_string, expected_string);
}

/*
 * Lines Covered: 22, 27, 29, 34, 35, 37, 42, 45, 49
 * Branches Covered: 22F, 29F, 45F
*/
BOOST_AUTO_TEST_CASE(make_deposit_test2){
    AccountManager accs;

    accs.addAccount("lblaney");
    BOOST_CHECK_THROW(accs.makeDeposit("bblaney", 100.0), std::invalid_argument);
}

/*
 * Lines Covered: 22, 27, 29, 34, 35, 37, 42, 45, 46, 55, 58, 59, 86, 90, 93, 94
 * Branches Covered: 22F, 29F, 45T, 58T, 86F
*/
BOOST_AUTO_TEST_CASE(make_withdrawal_test1){
    AccountManager accs;

    accs.addAccount("lblaney");
    accs.makeDeposit("lblaney", 100.0);
    accs.makeWithdrawal("lblaney", 50.0);

    std::string display_string = accs.displayAccount("lblaney");
    std::string expected_string = "First Name: Lucy\nLast Name: Blaney\nBalance: $50.000000\n";

    BOOST_CHECK_EQUAL(display_string, expected_string);
}

/*
 * Lines Covered: 22, 27, 29, 34, 35, 37, 55, 58, 62
 * Branches Covered: 22F, 29F, 58F
*/
BOOST_AUTO_TEST_CASE(make_withdrawal_test2){
    AccountManager accs;

    accs.addAccount("lblaney");
    BOOST_CHECK_THROW(accs.makeWithdrawal("bblaney", 100.0), std::invalid_argument);
}

/**
 * Lines Covered: 22, 27, 29, 34, 35, 37, 42, 45, 46, 86, 90, 93, 94, 105, 107, 110, 111
 * Branches Covered: 22F, 29F, 45T, 86F, 105T, 105F, 110T
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
 * Lines Covered: 22, 27, 29, 34, 35, 37, 42, 45, 46, 86, 90, 93, 94, 119, 121, 124, 126, 127
 * Branches Covered: 22F, 29F, 45T, 86F, 119T, 124T
 */ 
// test on writeCheck() where writeCheck() should be successful 
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
 * Lines Covered: 119, 137
 * Branches Covered: 119F
 */ 
// test on writeCheck() with an invalid check writer username
BOOST_AUTO_TEST_CASE(write_check_test2) {
    // arrange
    AccountManager accounts;

    // act and assert
    BOOST_CHECK_THROW(accounts.writeCheck("kjworld313", "riley414", 10.00), std::invalid_argument);
}

/**
 * Lines Covered: 22, 27, 29, 34, 35, 37, 42, 45, 46, 86, 90, 93, 94, 119, 121, 124, 129, 130
 * Branches Covered: 22F, 29F, 45T, 86F, 119T, 124F, 129T
 */ 
// test on writeCheck() with a non-checking account as checkWriter
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
 * Lines Covered: 22, 27, 29, 34, 35, 37, 42, 45, 46, 86, 90, 93, 94, 119, 121, 124, 129, 133
 * Branches Covered: 22F, 29F, 45T, 86F, 119T, 124F, 129F
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
 * Lines Covered: 22, 27, 29, 34, 35, 37, 68, 69, 73, 76, 79, 81, 99
 * Branches Covered: 22F, 29F, 68T, 68F
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
 * Lines Covered: 22, 27, 29, 34, 35, 37, 86, 87, 90, 93, 94
 * Branches Covered: 22F, 29F, 86T, 86F
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
 * Lines Covered:  22, 27, 29, 34, 35, 37, 99
 * Branches Covered: 22F, 29F
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
 * Lines Covered: 144, 145
 * Branches Covered: 144T
 */
// test serialize function with no accounts
BOOST_AUTO_TEST_CASE(throw_serialize_test) {
    // arrange
    AccountManager accounts;

    // act and assert
    BOOST_CHECK_THROW(accounts.serialize("test_file.txt"), std::out_of_range);
}

/**
 * Lines Covered: 22, 27, 29, 34, 35, 37, 144, 149, 150, 153, 166
 * Branches Covered: 22F, 29F, 144F, 153F
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
  * Lines Covered: 22, 27, 29, 34, 35, 37, 86, 87, 90, 93, 94, 144, 149, 150, 153, 155, 156, 157, 
  * cont: 158, 159, 163, 172, 173, 178, 178, 179, 181, 182, 184, 185, 191, 192, 194, 199, 200, 201, 202, 203
  * cont: 206, 207, 210, 211, 214, 216, 217, 219, 221, 222, 223, 224, 227, 234, 235, 236, 239, 241
  * Branches Covered: 22F, 29F, 86F, 142F, 151T, 153T, 155T, 155F, 172F, 178T, 178F, 185T, 185F, 185F, 186T,
  * cont: 194F, 210T, 210F, 221T, 221F, 223T
  */
 // test serialize function, should be successful
 BOOST_AUTO_TEST_CASE(serialize_test) {
    // arrange
    AccountManager accounts;
    accounts.addAccount("username1");
    accounts.addAccount("username2");
    accounts.addAccount("username3");
    AccountManager expected_accounts;
    expected_accounts.addAccount("username1");
    expected_accounts.addAccount("username2");
    expected_accounts.addAccount("username3");

    // act
    accounts.serialize("test_file.txt");
    accounts.deserialize("test_file.txt"); // get information back
    
    // assert
    for (int i = 1; i < accounts.getNumAccounts(); i++) {
        std::string num = std::to_string(i);
        BOOST_CHECK_EQUAL(accounts.displayAccount("username" + num), expected_accounts.displayAccount("username" + num));
    }
 }

 /**
 * Lines Covered: 86, 90, 93, 94, 172, 173, 178, 178, 179, 181, 182, 184, 185, 191, 192, 194, 199, 200, 201, 202, 203
 * cont: 206, 207, 210, 211, 214, 216, 217, 219, 221, 222, 223, 224, 227, 234, 235, 236, 239, 241
 * Branches Covered: 86F, 173F, 185F, 185T, 186F, 194F, 210T, 210F, 214T, 214F, 221T, 221F, 223T, 218F
 */
// test deserialize function
BOOST_AUTO_TEST_CASE(deserialize_test) {
    // arrange, create a temporary file with a savings and a checking account
    std::string filename = "test_deserialize.txt";
    {
        std::ofstream out(filename);
        out << "username1,savings,Nima,Dahir,1000.50,0.05\n";
        out << "username2,checking,Lucy,Blaney,500.00,40.0,20.0,5.0\n";
    }

    // act, reate a new AccountManager and deserialize from file
    AccountManager mgr;
    mgr.deserialize(filename);

    // assert, check number of accounts
    BOOST_CHECK_EQUAL(mgr.getNumAccounts(), 2);

    // assert, check deserialized SavingsAccount 
    std::string expected1 = "First Name: Nima\nLast Name: Dahir\nBalance: $1000.500000\n";
    BOOST_CHECK_EQUAL(mgr.displayAccount("username1"), expected1);

    // assert, check deserialized CheckingAccount 
    std::string expected2 = "First Name: Lucy\nLast Name: Blaney\nBalance: $500.000000\n";
    BOOST_CHECK_EQUAL(mgr.displayAccount("username2"), expected2);

    // clean up the temporary file
    std::remove(filename.c_str());
}

/**
 * Lines Covered: 172, 173, 174
 * Branches Covered: 173F
 */

// test for file not found
BOOST_AUTO_TEST_CASE(deserialize_file_not_found) {
    AccountManager mgr;
    BOOST_CHECK_THROW(mgr.deserialize("nonexistent_file.txt"), std::runtime_error);
}

/**
 * Lines Covered: 22, 27, 29, 34, 35, 37, 86, 90, 93, 94, 172, 173, 178, 178, 179, 181, 182, 184, 185, 191, 192, 194, 199, 200, 201, 202, 203
 * cont: 206, 207, 210, 211, 214, 216, 217, 219, 221, 222, 223, 224, 227, 234, 235, 236, 239, 241
 * Branches Covered: 86F, 173F, 185F, 185T, 186F, 194F, 210T, 210F, 214T, 214F, 221T, 221F, 223T, 218F
 */
BOOST_AUTO_TEST_CASE(deserialize_overwrite_accounts) {
    AccountManager mgr;

    // add old account (will prompt for input;)
    mgr.addAccount("username2");  

    // check that there is 1 account (olduser)
    BOOST_CHECK_EQUAL(mgr.getNumAccounts(), 1);

    // create temporary file to overwrite accounts
    std::string filename = "overwrite.txt";
    {
        std::ofstream out(filename);
        out << "username2,checking,Lucy,Blaney,500.00\n";
    }

    // deserialize from file (should remove old account)
    mgr.deserialize(filename);

    // after deserialization, old account should be removed
    BOOST_CHECK_EQUAL(mgr.getNumAccounts(), 1); 
    std::string expected = "First Name: Lucy\nLast Name: Blaney\nBalance: $500.000000\n";
    BOOST_CHECK_EQUAL(mgr.displayAccount("username2"), expected);

    // clean up temporary file
    std::remove(filename.c_str());
}

BOOST_AUTO_TEST_SUITE_END()