#ifndef ACCOUNTMANAGER_HPP
#define ACCOUNTMANAGER_HPP
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"

class AccountManager{

    public:

    void makeDeposit(std::string username, double amount);
    void makeWithdrawal(std::string username, double amount);
};

#endif