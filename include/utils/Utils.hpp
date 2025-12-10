#include "BankAccount.hpp"
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"

// function that prints a status message
void statusMessage(const std::string status);

// function that prints an error message
void errorMessage(const std::string error);

// function that prints option prompt to user, returns option value
std::string getOption();

// function that takes a prompt and returns user input
std::string getString(const std::string &prompt);

// function that makes a BankAccount pointer
BankAccount* make_account();

// function to get a double input from the user
double getDouble(const std::string &prompt);

