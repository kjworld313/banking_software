#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <string>
#include "AccountManager.hpp"

BOOST_AUTO_TEST_SUITE(account_manager_suite, * boost::unit_test::timeout(10))

// /*
//  * Lines Covered: 6, 7, 10, 11
//  * Branches Covered: 10T
// */
// BOOST_AUTO_TEST_CASE(makeDepositTest1){
//     AccountManager accs;
    
//     accs.addAccount("lblaney");
//     accs.makeDeposit("lblaney", 100.0);

//     std::string displaystring = accs.displayAccount("lblaney");
//     std::string intendedstring;
//     //BOOST_CHECK_EQUAL(displaystring, );
// }

// /*
//  * Lines Covered: 6,7,10,15
//  * Branches Covered: 15F
// */
// BOOST_AUTO_TEST_CASE(makeDepositTest2){
//     AccountManager accs;

//     accs.addAccount("lblaney");
//     BOOST_CHECK_THROW(accs.makeDeposit("bblaney", 100.0), std::out_of_range);
// }

// /*
//  * Lines Covered: 
//  * Branches Covered: 
// */
// BOOST_AUTO_TEST_CASE(makeWithdrawalTest1){
//     AccountManager accs;

//     accs.addAccount("lblaney");
//     accs.makeDeposit("lblaney", 100.0);
//     accs.makeWithdrawal("lblaney", 50.0);

//     //BOOST_CHECK_EQUAL(acc.getBalance(), 50.0);
// }

// /*
//  * Lines Covered: 
//  * Branches Covered: 
// */
// BOOST_AUTO_TEST_CASE(makeWithdrawalTest2){
//     AccountManager accs;

//     accs.addAccount("lblaney");
//     BOOST_CHECK_THROW(accs.makeWithdrawal("bblaney", 100.0), std::out_of_range);
// }

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

BOOST_AUTO_TEST_SUITE_END()