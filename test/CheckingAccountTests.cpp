#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "../include/accounts/CheckingAccount.hpp"
#include "../include/accounts/SavingsAccount.hpp"

BOOST_AUTO_TEST_SUITE(checking_account_suite, * boost::unit_test::timeout(10))

/**
 * Lines Covered: 9, 10 (hpp)
 * Branches Covered: N/A
 */
BOOST_AUTO_TEST_CASE(constructor_test1) {
    CheckingAccount* acc = new CheckingAccount("omar", "segura", 50.0);
    CheckingAccount* acc2 = new CheckingAccount("omar", "segura");

    BOOST_CHECK_EQUAL(acc->getFirstName(), "omar");
    BOOST_CHECK_EQUAL(acc->getLastName(), "segura");
    BOOST_CHECK_EQUAL(acc->getBalance(), 50.0);

    BOOST_CHECK_EQUAL(acc2->getFirstName(), "omar");
    BOOST_CHECK_EQUAL(acc2->getLastName(), "segura");
    BOOST_CHECK_EQUAL(acc2->getBalance(), 0.0);

    delete acc; 

}

/**
 * Lines Covered: 
 * Branches Covered:
 */
BOOST_AUTO_TEST_CASE(deposit_positive_test) {
    CheckingAccount* acc = new CheckingAccount("omar", "segura", 20.0);

    acc->deposit(30.0);

    BOOST_CHECK_EQUAL(acc->getBalance(), 50.0);

    delete acc; 
}

/**
 * Lines Covered:
 * Branches Covered:
 */
BOOST_AUTO_TEST_CASE(deposit_zero_test) {
    CheckingAccount* acc = new CheckingAccount("omar", "segura", 10.0);
    acc->deposit(0.0);


    BOOST_CHECK_EQUAL(acc->getBalance(), 10.0);

    delete acc; 
}

/**
 * Lines Covered:
 * Branches Covered:
 */
BOOST_AUTO_TEST_CASE(withdrawal_success_test) {
    CheckingAccount* acc = new CheckingAccount("omar", "segura", 100.0);
    acc->withdrawal(50.0);

    BOOST_CHECK_EQUAL(acc->getBalance(), 50.0);
    delete acc;
}

/**
 * Lines Covered:
 * Branches Covered:
 */
BOOST_AUTO_TEST_CASE(withdrawal_insufficient_test) {
    CheckingAccount* acc = new CheckingAccount("omar", "segura", 30.0);
    acc->withdrawal(50.0);

    BOOST_CHECK_EQUAL(acc->getBalance(), 30.0);
    delete acc;
}

/**
 * Lines Covered:
 * Branches Covered:
 */
BOOST_AUTO_TEST_CASE(withdrawal_zero_test) {
    CheckingAccount* acc = new CheckingAccount("omar", "segura", 30.0);
    acc->withdrawal(0.0);

    BOOST_CHECK_EQUAL(acc->getBalance(), 30.0);
    delete acc;
}

/**
 * Lines Covered: 9, 10 (hpp); 4, 6, 7, 8, 11 (cpp)
 * Branches Covered: 6T
 */
BOOST_AUTO_TEST_CASE(write_check_test){
    CheckingAccount* acc1 = new CheckingAccount("omar", "segura", 100.0);
    CheckingAccount* acc2 = new CheckingAccount("john", "Marston", 50.0);

    bool result = acc1->writeCheck(*acc2, 70.0);

    BOOST_CHECK_EQUAL(result, true);
    BOOST_CHECK_EQUAL(acc1->getBalance(), 30.0);
    BOOST_CHECK_EQUAL(acc2->getBalance(), 120.0);

    delete acc1;
    delete acc2;
}

/**
 * Lines Covered: 9, 10 (hpp); 4, 6, 11
 * Branches Covered: 6F
 */
BOOST_AUTO_TEST_CASE(write_check_insufficient_funds_test){
    CheckingAccount* acc1 = new CheckingAccount("omar", "segura", 40.0);
    CheckingAccount* acc2 = new CheckingAccount("john", "Marston", 50.0);

    bool result = acc1->writeCheck(*acc2, 70.0);

    BOOST_CHECK_EQUAL(result, false);
    BOOST_CHECK_EQUAL(acc1->getBalance(), 40.0);
    BOOST_CHECK_EQUAL(acc2->getBalance(), 50.0);

    delete acc1;
    delete acc2;
}

/**
 * Lines Covered: 9, 10 (hpp); 4, 6, 7, 8, 11, 29
 * Branches Covered: 6T, 6F
 */
BOOST_AUTO_TEST_CASE(check_log_test){
    CheckingAccount* acc = new CheckingAccount("omar", "segura", 200.0);
    CheckingAccount* acc2 = new CheckingAccount("john", "Marston", 50.0);

    acc->writeCheck(*acc2, 80.0);
    acc->writeCheck(*acc2, 50.0);
    acc->writeCheck(*acc2, 100.0); // this one should fail due to insufficient funds

    std::list<double> checkLog = acc->getCheckLog();
    std::list<double> expectedLog = {80.0, 50.0};

    BOOST_CHECK_EQUAL_COLLECTIONS(checkLog.begin(), checkLog.end(), expectedLog.begin(), expectedLog.end());

    delete acc;
    delete acc2;
}

/**
 * Lines Covered: 9, 10 (hpp); 4, 6, 11, 19, 20, 22, 23, 25(cpp)
 * Branches Covered: 6T, 22T, 22F
 */

 BOOST_AUTO_TEST_CASE(serialize_test) {
    CheckingAccount* acc = new CheckingAccount("omar", "segura", 10.00);
    CheckingAccount* acc2 = new CheckingAccount("john", "Marston", 50.0);
    acc->writeCheck(*acc2, 10.0);
    std::string expected_string =  "omar1,checking," + acc->getFirstName() + "," + acc->getLastName() + "," 
    + std::to_string(acc->getBalance()) + ",10.000000";

    std::string result = acc->serialize("omar1");

    BOOST_CHECK_EQUAL(result, expected_string);
 }

BOOST_AUTO_TEST_SUITE_END()