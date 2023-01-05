#include "Account.h"

Account::Account(string name, int pin, double balance){
    this->pin = pin;
    this->name = name;
    this->balance = balance;
}

bool Account::comparePin(int enteredPin){
    return this->pin == enteredPin;
}

double Account::viewBalance(){
    return this->balance;
}

bool Account::deposit(double d){
    if(d > 0.0){
        this->balance = this->balance + d;
        return true;
    }

    return false;
}

bool Account::withdraw(double w){
    if(w > 0.0 && w <= this->balance){
        this->balance = this->balance - w;
        return true;
    }

    return false;
}

string Account::getName(){
    return this->name;
}

string Account::toString(){
    string output = "";

    output += this->name;
    output += " ";
    output += to_string(this->pin);
    output += " ";
    output += to_string(this->balance);
    output += "\n";

    return output;
}

Account::~Account()
{
    //dtor
}
