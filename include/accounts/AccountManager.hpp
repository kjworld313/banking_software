#ifndef ACCOUNTMANAGER_HPP
#define ACCOUNTMANAGER_HPP

#include <string>
#include <map>

class AccountManager{
<<<<<<< HEAD
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

=======
    public:
        void makeDeposit(std::string username, double amount);
        
        void makeWithdrawal(std::string username, double amount);

        // function that adds interest to all savings accounts and returns success of operation
        bool addInterest();

        // function that attempts to write a check from writer to receiver and returns success of operation
        bool writeCheck(std::string checkWriter, std::string checkReceiver, double amount);
>>>>>>> 67b96c8 (Wrote addInterest and writeCheck functions)
};

#endif