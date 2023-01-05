#include <iostream>
#include "Account.h"
#include "ATM.h"
#include <string>

using namespace std;

int main()
{
    Account *firstAccount = new Account("Nik", 1111, 69.69);

    ATM *atm = new ATM("db.txt");
    atm->start();

    return 0;
}
