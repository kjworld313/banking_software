#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "SavingsAccount.hpp"

BOOST_AUTO_TEST_SUITE(savings_account_suite, * boost::unit_test::timeout(10))


/*

 * Lines covered: 3, 4
 * branches covered: N/A

*/
BOOST_AUTO_TEST_CASE(constructorTest1){
    SavingsAccount* acc = new SavingsAccount("Lucy","Blaney", 100.0, 0.5);

    BOOST_CHECK_EQUAL(acc->getFirstName(), "Lucy");
    BOOST_CHECK_EQUAL(acc->getLastName(),"Blaney");
    BOOST_CHECK_EQUAL(acc->getBalance(), 100.0);
    BOOST_CHECK_EQUAL(acc->getInterestRate(), 0.5);
}

/*
 * Lines Covered: 7, 8
 * Branches Covered: N/A
*/
BOOST_AUTO_TEST_CASE(constructorTest2){
    SavingsAccount* acc = new SavingsAccount("Lucy", "Blaney", 0.3);

    BOOST_CHECK_EQUAL(acc->getFirstName(), "Lucy");
    BOOST_CHECK_EQUAL(acc->getLastName(),"Blaney");
    BOOST_CHECK_EQUAL(acc->getInterestRate(), 0.3);
    BOOST_CHECK_EQUAL(acc->getBalance(), 0.0);
}

/*
 * Lines Tested: 11, 12, 13
 * Branches Tested: N/A
*/
BOOST_AUTO_TEST_CASE(accrueInterest_test){
    SavingsAccount* acc = new SavingsAccount("Lucy","Blaney", 100.0, 0.1);

    acc->accrueInterest();

    BOOST_CHECK_CLOSE(acc->getBalance(), 110.0, 0.01);
}



BOOST_AUTO_TEST_SUITE_END()