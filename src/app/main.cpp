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
    std::map<std::string, BankAccount*> accts;

    while(!finished){

        //using getOption instead of print statements in starter code
        std::string input_string = getOption();
        
        if(input_string == "0"){ // exit program
            statusMessage("Exiting. Thank you for using the software.");
            finished = true;
        }
        else if(input_string == "1"){ // add account
            std::string user = getString("Enter your username: ");

            accounts.addAccount(user);
        }  
        else if(input_string == "2"){ // deposit
            // ask user for username
            std::string user = getString("Enter your username: ");

            // ask user for amount
            double deposit_amount = getDouble("Enter amount to be deposited: ");

            // make deposit of amount to account user
            accounts.makeDeposit(user, deposit_amount);
        }
        else if(input_string == "3"){ // withdrawal
            // ask user for username
            std::string user = getString("Enter your username: ");   

            // ask user for amount
            double withdrawal_amount = getDouble("Enter amount to be withdrawn: ");
            
            accounts.makeWithdrawal(user, withdrawal_amount);
        }
        else if(input_string == "4"){ // display account
            // ask user for username
            std::string user = getString("Enter your username: ");

            statusMessage("/n" + accounts.displayAccount(user)); // display account
        }
        else if(input_string == "5"){ // add interest on accounts
            // add interest to all accounts
            accounts.addInterest();
        }
        else if(input_string == "6"){ // write check
            // ask user for check writer and check receiver usernames
            std::string checkWriter = getString("Enter the username of the account writing check: ");
            std::string checkReceiver = getString("Enter the username of the account cashing the check: ");

            accounts.writeCheck(checkWriter, checkReceiver);   // write the check
        }
        else if (input_string == "7") { // delete account
            // ask user for username then delete account
            std::string user = getString("Enter the username to delete: "); // added to delete
            accounts.deleteAccount(user);
        }
        else{ // invalid input
            errorMessage("I'm sorry, that is not a valid choice.");
        }
    }

    // loop through map and delete all accounts
    std::map<std::string, BankAccount*>::iterator it;

    for (it = accts.begin(); it != accts.end(); it++){
        BankAccount *acct = it->second;
        delete acct;
    }

    return 0;
}