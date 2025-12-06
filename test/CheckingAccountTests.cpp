#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "../include/accounts/CheckingAccount.hpp"
#include "../include/accounts/SavingsAccount.hpp"

BOOST_AUTO_TEST_SUITE(checking_account_suite, * boost::unit_test::timeout(10))

BOOST_AUTO_TEST_CASE(constructor_test) {
    CheckingAccount* acc = new CheckingAccount("omar", "segura", 50.0);

    BOOST_CHECK_EQUAL(acc->getFirstName(), "omar");
    BOOST_CHECK_EQUAL(acc->getLastName(), "segura");
    BOOST_CHECK_EQUAL(acc->getBalance(), 50.0);

    delete acc; 

}

BOOST_AUTO_TEST_CASE(Deposit_Positive_Test) {
    CheckingAccount* acc = new CheckingAccount("omar", "segura", 20.0);

    acc->deposit(30.0);

    BOOST_CHECK_EQUAL(acc->getBalance(), 50.0);

    delete acc; 
}

BOOST_AUTO_TEST_CASE(Deposit_Zero_Test) {
    CheckingAccount* acc = new CheckingAccount("omar", "segura", 10.0);
    acc->deposit(0.0);


    BOOST_CHECK_EQUAL(acc->getBalance(), 10.0);

    delete acc; 
}
BOOST_AUTO_TEST_CASE(Withdrawl_success_test) {
    CheckingAccount* acc = new CheckingAccount("omar", "segura", 100.0);
    acc->withdrawal(50.0);

    BOOST_CHECK_EQUAL(acc->getBalance(), 50.0);
    delete acc;
}

BOOST_AUTO_TEST_CASE(Withdrawl_insuffiecient_test) {
    CheckingAccount* acc = new CheckingAccount("omar", "segura", 30.0);
    acc->withdrawal(50.0);

    BOOST_CHECK_EQUAL(acc->getBalance(), 30.0);
    delete acc;
}

BOOST_AUTO_TEST_CASE(Withdrawl_zero_test) {
    CheckingAccount* acc = new CheckingAccount("omar", "segura", 30.0);
    acc->withdrawal(0.0);

    BOOST_CHECK_EQUAL(acc->getBalance(), 30.0);
    delete acc;
}

    BOOST_AUTO_TEST_CASE(Write_check_test){
        CheckingAccount* acc1 = new CheckingAccount("omar", "segura", 100.0);
        CheckingAccount* acc2 = new CheckingAccount("john", "Marston", 50.0);

        bool result = acc1->writeCheck(*acc2, 70.0);

        BOOST_CHECK_EQUAL(result, true);
        BOOST_CHECK_EQUAL(acc1->getBalance(), 30.0);
        BOOST_CHECK_EQUAL(acc2->getBalance(), 120.0);

        delete acc1;
        delete acc2;
    }

    BOOST_AUTO_TEST_CASE(Write_check_insufficient_funds_test){
        CheckingAccount* acc1 = new CheckingAccount("omar", "segura", 40.0);
        CheckingAccount* acc2 = new CheckingAccount("john", "Marston", 50.0);

        bool result = acc1->writeCheck(*acc2, 70.0);

        BOOST_CHECK_EQUAL(result, false);
        BOOST_CHECK_EQUAL(acc1->getBalance(), 40.0);
        BOOST_CHECK_EQUAL(acc2->getBalance(), 50.0);

        delete acc1;
        delete acc2;
    }

    BOOST_AUTO_TEST_CASE(Check_log_test){
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

BOOST_AUTO_TEST_SUITE_END()