#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(account_manager_suite, * boost::unit_test::timeout(10))

/*
 * Lines Covered: 
 * Branches Covered: 
*/
BOOST_AUTO_TEST_CASE(makeDepositTest1){
    AccountManager accs;
    
    accs.addAccount("lblaney");
    accs.makeDeposit("lblaney", 100.0);

    BOOST_CHECK_EQUAL(acc1.getBalance(), 200.0);
}

/*
 * Lines Covered: 
 * Branches Covered: 
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
    accs.makeWithdrawal("lblaney", 50.0);

    BOOST_CHECK_EQUAL(acc1.getBalance(), 50.0);
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