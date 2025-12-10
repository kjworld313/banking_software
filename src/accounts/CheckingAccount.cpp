#include "CheckingAccount.hpp"

bool CheckingAccount::writeCheck(BankAccount &a, double amount){
    bool success = withdrawal(amount);

    if(success){
        a.deposit(amount);
        checkLog.push_back(amount);
    }

    return success;
}

std::string CheckingAccount::toString(){
    return "Checking Account Balance: $" + std::to_string(getBalance());
}

std::string CheckingAccount::serialize(std::string username){
    return "Checking, "  + username + "," + getFirstName() + "," + getLastName() + "," 
    + std::to_string(getBalance());
}

std::list<double> CheckingAccount::getCheckLog(){
    return checkLog;
}