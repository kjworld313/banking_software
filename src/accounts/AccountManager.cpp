#include "AccountManager.hpp"
#include <iostream>
#include <stdexcept>


    void AccountManager::makeDeposit(std::string username, double amount){
        if(amount<0){
            //throw exception
        }
        else{
            BankAccount* account = accounts[username];
            account->deposit(amount);
        }
    }

    void AccountManager::makeWithdrawal(std::string username, double amount){
        if(amount<0){
            //throw exception
        }
        else{
            BankAccount* account = accounts[username];
            account->withdrawal(amount);
        }
    }
    void AccountManager::deleteAccount(std::string username) {
        // check if username exists
        if (accounts.count(username) == 0) {
            throw std::invalid_argument("The account does not exist.");
        }
    
        // delete the dynamic account object
        delete accounts[username];
    
        // remove from the map
        accounts.erase(username);
    
        // update the count
        numAccounts = numAccounts - 1;
    
        std::cout << "[STATUS]: The account was deleted.\n";
    }
    
    void AccountManager::displayAccount(std::string username) {
        // check if the username exists
        if (accounts.count(username) == 0) {
            throw std::invalid_argument("The account does not exist.");
        }
    
        BankAccount* acc = accounts[username];

        std::cout << "First Name: " << acc->getFirstName() << "\n";
        std::cout << "Last Name: "  << acc->getLastName() << "\n";
        std::cout << "Balance: $"   << acc->getBalance()  << "\n";
    }
        
    // numAccounts
    int AccountManager::getNumAccounts() const {
        return numAccounts;
    }
    
    // function that adds interest to all savings accounts and returns success of operation
    void AccountManager::addInterest() {
        // iterate through accounts map and accrue interest on all accounts
        for (auto iterator = accounts.begin(); iterator != accounts.end(); iterator++) {
            // dynamically cast each account in map to determine if current account is a savings account
            SavingsAccount* savingsAccount = dynamic_cast<SavingsAccount*>(iterator->second); // second is the bank account 

            // check if current account is a savings account and accrue interest
            if (savingsAccount != nullptr) {
                savingsAccount->accrueInterest(); // accrue interest on the current savings account
            }
        }
    }

    // function that attempts to write a check from writer to receiver
    void AccountManager::writeCheck(std::string checkWriter, std::string checkReceiver, double amount) {
        // check if the checkWriter account exists in the system
        if(accounts.find(checkWriter) != accounts.end()) {
            // get check writer account from map
            CheckingAccount* account = accounts[checkWriter];
            // check if checkReceiver account exists in the system
            if (accounts.find(checkReceiver) != accounts.end()) {
                // get check receiver account from map and write check
                BankAccount* recipient = accounts[checkReceiver];
                account->writeCheck(recipient, amount);
            } else { // checkReceiver account does not exist in system throw exception
                throw std::invalid_argument("Receiving Account does not exist in system.");
            }
        } else { // checkWriter account does not exist in system, throw exception
            throw std::invalid_argument("Checking Account does not exist in system.");
        }
    }
