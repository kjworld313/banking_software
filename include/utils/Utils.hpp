#include "BankAccount.hpp"
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"

// function that prints a status message
void statusMessage(const std::string status);

// function that prints an error message
void errorMessage(const std::string error);

// function that gets the option
std::string getOption();

BankAccount* make_account();

std::string getString(const std::string &prompt);

// function to get a double input from the user
double getDouble(const std::string &prompt);

