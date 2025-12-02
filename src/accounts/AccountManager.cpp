#include "AccountManager.hpp"

    //function deposits amount into account with username
    void AccountManager::makeDeposit(std::string username, double amount){
        auto it = accounts.find(username);

        if (it != accounts.end()){
            it->second.deposit(amount);
        }
        else{
            std::cout<<"Username does not match any existing accounts."<<std::endl;
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
