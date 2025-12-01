#ifndef ACCOUNTMANAGER_HPP
#define ACCOUNTMANAGER_HPP

class AccountManager{

    public:

    void makeDeposit(std::string username, double amount);
    void makeWithdrawal(std::string username, double amount);
};

#endif