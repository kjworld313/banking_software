#include "Utils.hpp"
#include <iostream>
#include <stdexcept>

// function that prints a status message
void statusMessage(const std::string status) {
    std::cout << "[STATUS]: " + status << std::endl;
}

// function that prints an error message
void errorMessage(const std::string error) {
    std::cout << "[ERROR]: " + error << std::endl;
}

// prints option prompt to user, returns option value
std::string getOption(){
    std::cout<<"Options"<<std::endl;
    std::cout<<"0) Exit"<<std::endl;
    std::cout<<"1) Make account"<<std::endl;
    std::cout<<"2) Deposit to existing account"<<std::endl;
    std::cout<<"3) Withdraw from existing account"<<std::endl;
    std::cout<<"4) Display existing account"<<std::endl;
    std::cout<<"5) Accrue Interest"<<std::endl;
    std::cout<<"6) Write a check"<<std::endl;
    std::cout<<"What would you like to do (Input single number):"<<std::endl;

    std::string input_string;
    std::cin >> input_string;

    return input_string;
}
std::string getString(const std::string &prompt){
    std::cout << prompt;
    std::string input;
    std::cin >> input;
    return input;
}

BankAccount* make_account() {
    BankAccount *acct = nullptr;

    std::string first = getString("Enter the first name ");
    std::string last = getString("Enter the last name ");

    std::string choice = getString("Would you like to make a savings (1) or checking (2) account: ");

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

double getDouble(const std::string &prompt) {
    std::cout << prompt;
    double value;
    if (std::cin >> value) {
        return value;
    } else {
        std::cin.clear(); 
        std::cin.ignore(10000, '\n'); // remove bad input from buffer
        throw std::invalid_argument("Input is not a valid number");
    }
}