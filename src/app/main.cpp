#include "BankAccount.hpp"
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"
#include "AccountManager.hpp"
#include "Utils.hpp"

#include <iostream>
#include <map>

int main(){
    std::cout<<"Welcome to the banking software!"<<std::endl;

    bool finished = false;
    AccountManager accounts; 
    std::map<std::string, BankAccount*> accts;

    while(!finished){

        //using getOption instead of print statements in starter code
        std::string input_string = getOption();
        
        if(input_string == "0"){
            std::cout << "Thank you for using the software" << std::endl;
            finished = true;
        }
        else if(input_string == "1"){
            std::string user = getString("Enter your username: ");

            account.addAccount(user);
        }  
        else if(input_string == "2"){
            // ask user for username
            std::string user = getString("Enter your username: ");

            // ask user for amount
            double deposit_amount = getDouble("Enter amount to be deposited: ");

            // make deposit of amount to account user
            accounts.makeDeposit(user, deposit_amount);
        }
        else if(input_string == "3"){
            // ask user for username2
            std::string user = getString("Enter your username: ");   

            // ask user for amount
            double withdrawal_amount = getDouble("Enter amount to be withdrawn");
            
            accounts.makeWithdrawal(user, withdrawal_amount);
        }
        else if(input_string == "4"){
            std::string user = getString("Enter your username: ");

            accounts.displayAccount(user);
        }
        else if(input_string == "5"){
            accounts.addInterest();
        }
        else if(input_string == "6"){
            std::string checkWriter = getString("Enter the username of the account writing check: ");
            std::string checkReceiver = getString("Enter the username of the account cashing the check: ");

            accounts.writeCheck(checkWriter, checkReceiver);  
        }
        else{
            std::cout << "I'm sorry, that is not a valid choice." << std::endl;
        }
    }

    std::map<std::string, BankAccount*>::iterator it;

    for (it = accts.begin(); it != accts.end(); it++){
        BankAccount *acct = it->second;
        delete acct;
    }

    return 0;
}