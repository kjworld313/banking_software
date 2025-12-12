#include "Utils.hpp"
#include <iostream>
#include <stdexcept>

// function that prints a status message
void statusMessage(const std::string &status) {
    std::cout << "[STATUS]: " + status << std::endl;
}

// function that prints an error message
void errorMessage(const std::string &error) {
    std::cout << "[ERROR]: " + error << std::endl;
}

// prints option prompt to user, returns option value
std::string getOption(){
    // menu of options
    std::cout<<"Options"<<std::endl;
    std::cout<<"0) Exit"<<std::endl;
    std::cout<<"1) Make account"<<std::endl;
    std::cout<<"2) Deposit to existing account"<<std::endl;
    std::cout<<"3) Withdraw from existing account"<<std::endl;
    std::cout<<"4) Display existing account"<<std::endl;
    std::cout<<"5) Accrue Interest"<<std::endl;
    std::cout<<"6) Write a check"<<std::endl;
    std::cout<<"What would you like to do (Input single number):"<<std::endl;

    // get user input
    std::string input_string;
    std::cin >> input_string;

    return input_string;
}

// function that takes a prompt and returns user input
std::string getString(const std::string &prompt){
    // print prompt
    std::cout << prompt;

    // get user input
    std::string input;
    std::cin >> input;

    return input;
}

// function that makes a BankAccount pointer
BankAccount* make_account() {
    BankAccount *acct = nullptr;

    // get name information
    std::string first = getString("Enter the first name: ");
    std::string last = getString("Enter the last name: ");

    // get account type from user
    std::string choice = getString("Would you like to make a savings (1) or checking (2) account: ");

    if(choice == "1"){ // savings account
        std::string interest_rate_string = getString("Enter the interest rate: ");

        // convert interest rate to double
        char *end;
        double interest_rate = strtod(interest_rate_string.c_str(), &end);
        if(*end == '\0'){
            if(interest_rate > 0 && interest_rate < 1){
                acct = new SavingsAccount(first, last, interest_rate); // make a savings account
            }
        }
        else{ // invalid input
            errorMessage("I'm sorry, that is not a valid interest rate.");
        }
    }
    else if(choice == "2"){ // checking account
        acct = new CheckingAccount(first, last); // make a checking account
    }
    else{ // invalid choice
        errorMessage("I'm sorry, that is not a valid choice.");
    }

    return acct;
}

// function to get a double input from the user
double getDouble(const std::string &prompt) {
    std::cout << prompt;
    double value;
    if (std::cin >> value) { // make sure input is valid
        return value;
    } else {
        std::cin.clear(); 
        std::cin.ignore(10000, '\n'); // remove bad input from buffer
        throw std::invalid_argument("Input is not a valid number");
    }
}