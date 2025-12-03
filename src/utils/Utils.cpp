#include "Utils.hpp"
#include <iostream>

std::string getString(const std::string &prompt){
    std::cout << prompt;
    std::string input;
    std::cin >> input;
    return input;
}

BankAccount* make_account(){
    BankAccount *acct = nullptr;

    std::string first = getString("Enter the first name ");
    std::string last = getString("Enter the last name ");

    std::string choice = getString("Would you like tomake a savings (1) or checking (2) account: ");

    if(choice == "1"){
        std::string interest_rate_string = getString("Enter the interest rate: ");

        char *end;
        double interest_rate = strtod(interest_rate_string.c_str(), &end);
        if(*end == '\0'){
            if(interest_rate > 0 && interest_rate < 1){
                acct = new SavingsAccount(first, last, interest_rate);
            }
        }
        else{
            std::cout << "I'm sorry, that is not a valid interest rate." << std::endl;
        }
    }
    else if(choice == "2"){
        acct = new CheckingAccount(first, last);
    }
    else{
        std::cout << "I'm sorry, that is not a valid choice." << std::endl;
    }

    return acct;
}

