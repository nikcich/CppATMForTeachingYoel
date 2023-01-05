#include "ATM.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

ATM::ATM(string file){
    this->file = file;
    ifstream db(file);

    string name;
    string pin;
    string balance;

    while(getline(db, name, ' ') && getline(db, pin, ' ') && getline(db, balance, '\n')){
        cout << name << '\t' << pin << '\t' << balance << endl;
        Account *newUser = new Account(name, stoi(pin), stod(balance));
        this->accountList.push_back(newUser);
    }

    db.close();

    this->currentAccount = nullptr;
}

void ATM::start(){
    int input = -1;

    do{
        if(this->loginAttempts > 3) {
            cout << "---------- Bank of Yoel ----------" << endl
                 << "You suck get the fuck out" << endl;
            return;
        }
        cout << "---------- Bank of Yoel ----------" << endl
            << "Please Select An Option:" << endl
            << "1. Login" << endl
            << "2. Withdraw" << endl
            << "3. Deposit" << endl
            << "4. View Balance" << endl
            << "5. Exit" << endl;

        cin >> input;

        switch(input){
            case 1: // Login
                this->handleLogin();
                break;
            case 2: // Withdraw
                this->withdraw();
                break;
            case 3: // Deposit
                this->deposit();
                break;
            case 4: // View Balance
                this->viewBalance();
                break;
            case 5: // Exit
                return;
                break;
            default:
                cout << "Invalid Option, please try again." << endl << endl;
                break;
        }

        // Save Updated Data To File

        ofstream db(this->file);

        for(int i = 0; i < this->accountList.size(); i++){
            Account *curr = this->accountList[i];

            db << curr->toString();
        }

        db.close();
    }while(input != 5);

}

bool ATM::checkLoggedIn(){
    if(this->currentAccount == nullptr) return false;

    return true;
}

void ATM::withdraw(){
    cout << "---------- Bank of Yoel ----------" << endl;
    if(!checkLoggedIn()){
        cout << "Log In To Deposit." << endl << endl;
        return;
    }

    cout << "Enter The Amount To Withdraw: " << endl;

    string input;

    cin >> input;
    double withdrawAmount;

    try{
        withdrawAmount = stod(input);
    }catch(const std::invalid_argument& ia){
        withdrawAmount = -1;
    }

    if(withdrawAmount > 0.0 && withdrawAmount <= this->currentAccount->viewBalance()){
        bool success = this->currentAccount->withdraw(withdrawAmount);

        if(success){
            cout << "Withdraw Successful, Thank You." << endl << endl;
        }else{
            cout << "Withdraw Unsuccessful, Try Again." << endl << endl;
        }
    }else{
        cout << "Withdraw Unsuccessful, Try Again." << endl << endl;
    }
}

void ATM::deposit(){
    cout << "---------- Bank of Yoel ----------" << endl;
    if(!checkLoggedIn()){
        cout << "Log In To Deposit." << endl << endl;
        return;
    }

    cout << "Enter The Amount To Deposit: " << endl;

    string input;

    cin >> input;
    double depositAmount;

    try{
        depositAmount = stod(input);
    }catch(const std::invalid_argument& ia){
        depositAmount = -1;
    }

    if(depositAmount > 0.0){
        bool success = this->currentAccount->deposit(depositAmount);

        if(success){
            cout << "Deposit Successful, Thank You." << endl << endl;
        }else{
            cout << "Deposit Unsuccessful, Try Again." << endl << endl;
        }
    }else{
        cout << "Deposit Unsuccessful, Try Again." << endl << endl;
    }
}

void ATM::viewBalance(){
    cout << "---------- Bank of Yoel ----------" << endl;
    if(!checkLoggedIn()){
        cout << "Log In To View Your Balance." << endl << endl;
        return;
    }


    cout << this->currentAccount->getName() << ", your current balance is: $"
         << this->currentAccount->viewBalance() << endl << endl;
}

void ATM::handleLogin(){
    cout << "---------- Bank of Yoel ----------" << endl
         << "Please Enter Your Pin: " << endl;

    string input;
    cin >> input;
    int pin;
    try{
        pin = stoi(input);
    }catch(const std::invalid_argument& ia){
        pin = -1;
    }catch(const std::out_of_range& ia){
        pin = -1;
    }

    if(input.length() == 4 && pin <= 9999 && pin >= 0){
            for(int i = 0; i < this->accountList.size(); i++){
                Account *curr = this->accountList[i];

                bool isCorrectPin = curr->comparePin(pin);

                if(isCorrectPin){
                    this->currentAccount = curr;
                    cout << endl << "Successfully logged in. Welcome, " << curr->getName() << endl << endl;
                    return;
                }
            }

    }else{
        cout << "Invalid Pin." << endl << endl;
        this->loginAttempts++;
        return;
    }
}

ATM::~ATM(){
    //dtor
}
