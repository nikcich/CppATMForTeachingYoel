#ifndef ATM_H
#define ATM_H
#include <string>
#include <vector>
#include "Account.h"

using namespace std;

class ATM
{
    public:
        ATM(string file);
        virtual ~ATM();
        void start();
        void handleLogin();
        void viewBalance();
        bool checkLoggedIn();
        void deposit();
        void withdraw();

    protected:

    private:
        string file;
        vector<Account *> accountList;
        int loginAttempts;
        Account *currentAccount;
};

#endif // ATM_H
