#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account
{
    public:
        Account(string, int, double);
        virtual ~Account();

        bool comparePin(int e);
        double viewBalance();
        bool deposit(double e);
        bool withdraw(double e);
        string getName();
        string toString();

    protected:

    private:
        int pin;
        string name;
        double balance;
};

#endif // ACCOUNT_H
