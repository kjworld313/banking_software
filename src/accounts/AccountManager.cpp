#include "AccountManager.hpp"


void AccountManager::makeDeposit(std::string username, double amount){
    if(amount<0){
        //throw exception
    }
    else{
        BankAccount* account = map_name[username];
        account->deposit(amount);
    }
}