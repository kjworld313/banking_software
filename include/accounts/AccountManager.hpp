#ifndef ACCOUNTMANAGER_HPP
#define ACCOUNTMANAGER_HPP

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>

#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"

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

      void deleteAccount(std::string username);
      std::string displayAccount(std::string username);
      int getNumAccounts() const;

      void addInterest();
      void writeCheck(std::string checkWriter, std::string checkReceiver, double amount);

      void serialize(std::string filename);
      void deserialize(std::string filename);

};

#endif