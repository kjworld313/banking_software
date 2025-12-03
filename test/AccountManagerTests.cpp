#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <string>

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
    std::string intendedstring
    BOOST_CHECK_EQUAL(displaystring, );
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

    BOOST_CHECK_EQUAL(acc.getBalance(), 50.0);
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

BOOST_AUTO_TEST_SUITE_END()