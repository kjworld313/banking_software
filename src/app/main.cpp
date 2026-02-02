#include "BankAccount.hpp"
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"
#include "AccountManager.hpp"
#include "Utils.hpp"

#include <iostream>
#include <map>

int main(){
    // welcome user to banking software
    statusMessage("Welcome to the banking software!");

    bool finished = false;
    AccountManager accounts; 

    // deserialize if file exists
    try {
        accounts.deserialize("../src/accounts.csv");
    }
    catch (const std::exception &e) {
        errorMessage(e.what());
    }

    while(!finished){
        //using getOption instead of print statements in starter code
        std::string input_string = getOption();
        
        if(input_string == "0"){ // exit program
            statusMessage("Exiting. Thank you for using the software.");
            finished = true;
        }
        else if(input_string == "1"){ // add account
            std::string user = getString("Enter your username: ");

            // add the account
            try {
                accounts.addAccount(user);
            } 
            catch (const std::exception &e) {
                errorMessage(e.what());
            }
        }  
        else if(input_string == "2"){ // deposit
            // ask user for username
            std::string user = getString("Enter your username: ");

            // ask user for amount
            try {
                double deposit_amount = getDouble("Enter amount to be deposited: ");

                // make deposit of amount to account user
                try {
                    accounts.makeDeposit(user, deposit_amount);
                }
                catch (const std::exception &e) {
                    errorMessage(e.what());
                }
            }
            catch (const std::exception &e) {
                errorMessage(e.what());
            }
        }
        else if(input_string == "3"){ // withdrawal
            // ask user for username
            std::string user = getString("Enter your username: ");   

            // ask user for amount
            try {
                double withdrawal_amount = getDouble("Enter amount to be withdrawn: ");

                // make the withdrawal
                try {
                    accounts.makeWithdrawal(user, withdrawal_amount);
                }
                catch (const std::exception &e) {
                    errorMessage(e.what());
                }
            }
            catch (const std::exception &e) {
                errorMessage(e.what());
            }
        }
        else if(input_string == "4"){ // display account
            // ask user for username
            std::string user = getString("Enter your username: ");

            // display the account
            try {
                statusMessage("\n" + accounts.displayAccount(user)); // display account
            }
            catch (const std::exception &e) {
                errorMessage(e.what());
            }
        }
        else if(input_string == "5"){ // add interest on accounts
            // add interest to all accounts
            try {
                accounts.addInterest();
            }
            catch (const std::exception &e) {
                errorMessage(e.what());
            }
        }
        else if(input_string == "6"){ // write check
            // ask user for check writer and check receiver usernames
            std::string checkWriter = getString("Enter the username of the account writing check: ");
            std::string checkReceiver = getString("Enter the username of the account cashing the check: ");

            // ask user for the check amount
            try {
                double check_amount = getDouble("Enter the amount of the check: ");

                // write the check
                try {
                    accounts.writeCheck(checkWriter, checkReceiver, check_amount);   // write the check
                }
                catch (const std::exception &e) {
                    errorMessage(e.what());
                }
            }
            catch (const std::exception &e) {
                errorMessage(e.what());
            }
        }
        else if (input_string == "7") { // delete account
            // ask user for username then delete account
            std::string user = getString("Enter the username to delete: "); // added to delete

            try {
                accounts.deleteAccount(user);
            }
            catch (const std::exception &e) {
                errorMessage(e.what());
            }
        }
        else{ // invalid input
            errorMessage("I'm sorry, that is not a valid choice.");
        }
    }

    // serialize accounts
    try {
        accounts.serialize("../src/accounts.csv");
    }
    catch (const std::exception &e) {
        errorMessage(e.what());
    }

    return 0;
}
