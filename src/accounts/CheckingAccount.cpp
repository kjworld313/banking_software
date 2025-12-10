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
    std::string result = username + ",checking," + getFirstName() + "," + getLastName() + "," 
    + std::to_string(getBalance());

    for(std::list<double>::const_iterator it = checkLog.begin(); it != checkLog.end(); it++){
        result += "," + std::to_string(*it);
    }
    return result;
}

std::list<double> CheckingAccount::getCheckLog(){
    return checkLog;
}