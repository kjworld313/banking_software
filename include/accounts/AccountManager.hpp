#ifndef ACCOUNTMANAGER_HPP
#define ACCOUNTMANAGER_HPP

#include <string>
#include <map>

class AccountManager{
    private: 
    int numAccounts;
    std::map<std::string, BankAccount*> accounts;

    public:
      AccountManager();

     ~AccountManager();

     void addAccount(std::string username);

     void makeDeposit(std::string username, double amount);
     void makeWithdrawal(std::string username, double amount);

    void addInterest();
    void writeCheck(std::string checkWriter, std::string checkReceiver, double amount);

};

#endif