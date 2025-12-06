#include "AccountManager.hpp"
#include <iostream>
#include <stdexcept>
#include "../utils/Utils.hpp"

    AccountManager::AccountManager(){
        numAccounts = (0);
    }

    AccountManager::~AccountManager(){
        for (auto it = accounts.begin(); it != accounts.end(); ++it){
            delete it->second;
        }
        accounts.clear();
    }
    //check if username already exists
    void AccountManager::addAccount(std::string username){
        if (accounts.find(username) != accounts.end()){
            throw std::invalid_argument("Username already exists.");
        }

        BankAccount* accs = make_account();

        if(accs == nullptr){
            throw std::runtime_error("Account creation failed.");
        }
        accounts[username] = accs;
        numAccounts++;

        std::cout<<"Account successfully created for user: " << username << std::endl;
    }

    //function deposits amount into account with username
    void AccountManager::makeDeposit(std::string username, double amount){
        auto it = accounts.find(username);

        //check if account exists, if it does make deposit, if it doesn't print error
        if (it != accounts.end()){
            (it->second)->deposit(amount);
        }
    
        else{
            throw std::out_of_range("Username does not exist.");
        }
    }

    void AccountManager::makeWithdrawal(std::string username, double amount){
        auto it = accounts.find(username);

        //check if account exists, if it does make deposit, if it doesn't print error
        if (it != accounts.end()){
            (it->second)->withdrawal(amount);
        }
    
        else{
            throw std::out_of_range("Username does not exist.");
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
    
    std::string AccountManager::displayAccount(std::string username) {
        // check if the username exists
        if (accounts.count(username) == 0) {
            throw std::invalid_argument("The account does not exist.");
        }
    
        BankAccount* acc = accounts[username];

        // return account as string
        return "First Name: " + acc->getFirstName() + "\nLast Name: " + acc->getLastName() + 
        "\nBalance: $" + std::to_string(acc->getBalance()) + "\n";
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
        if(accounts.count(checkWriter) != 0) {
            // dynamically cast account to check if checkWriter is a checking account
            CheckingAccount* account = dynamic_cast<CheckingAccount*>(accounts[checkWriter]); // second is the bank account 

            // check if checkWriter is a checking account and checkReceiver account exists in system
            if (account && accounts.count(checkReceiver) != 0) {
                // get check receiver account from map and write check
                BankAccount* recipient = accounts[checkReceiver];
                account->writeCheck(*recipient, amount);
            } 
            else if (!account) { // account is not a checking account
                throw std::invalid_argument("Bank Account " + checkWriter + " is not a Checking Account.");
            }
            else { // checkReceiver account does not exist in system, throw exception
                throw std::invalid_argument("Receiving Account " + checkReceiver + " does not exist in system.");
            }
        } 
        else { // checkWriter account does not exist in system, throw exception
            throw std::invalid_argument("Checking Account " + checkWriter + " does not exist in system.");
        }
    }


