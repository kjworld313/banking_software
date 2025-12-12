# Group2

***

## Project Title
Banking Software Application

## Description
Our project is a banking software that tracks accounts and their account details, including name, username, account type, balance, and interest rate or check log. The software accrues interest on savings accounts and allows users to create accounts, deposit to or withdraw from accounts, display accounts in the system, write checks, and delete an account from the system. The software utilizes account classes and utility functions for its functionality, as well as the C++ Boost Testing Framework for unit testing.

## Program Instructions
In order to run the program,  make a 'build' directory in the root of the project and run 'cmake ..' in the terminal. Once the build file generator has finished processing, run 'make' and use the following command line to run the program:
./src/bank_app. The main program prompts a menu of options for the user to select from - program will inform user of invalid input.
When depositing, withdrawing, or writing a check only enter valid amounts (integers or decimals, no strings or other non-number characters) to ensure success of operations. Program serializes account system data at end of process and deserializes at the beginning of each software run to extract pre-existing system data.

## Testing
To test this program, make a 'build' directory in the root of the project and run 'cmake ..' in the terminal. Once the build file generator has finished processing, run 'make' and use the following command line to test the program:
./test/bank_account_tests <<< "Lucy Blaney 2 Lucy Blaney 2 Lucy Blaney 2 Lucy Blaney 2 Kj World 1 0.2 Riley Puppy 2 Kj World 2 Riley Puppy 2 Kj World 1 0.2 Riley Puppy 2 Kj World 2 User One 2 User Two 2 User Three 2 User Four 2 John Doe 2 User One 2 User One 2 User Two 2 User Two 2 User Three 1 0.01 User Three 1 0.01 Lucy Blaney 2"

## Authors and acknowledgment
Contributors: Nima Dahir, Katelynn Olson, Omar Segura, Lucy Blaney

Thanks to [makeareadme.com](https://www.makeareadme.com/) for this template.