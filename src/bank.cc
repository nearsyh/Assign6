#include "bank.h"
Bank::Bank( unsigned int numStudents ) {
    accounts = new unsigned int[numStudents];
    conditions = new uCondition[numStudents];
    memset(accounts, 0, sizeof(unsigned int) * numStudents);
}
Bank::~Bank() {
    delete []accounts;
    delete []conditions;
}
void Bank::deposit( unsigned int id, unsigned int amount ) {
    accounts[id] += amount;
    conditions[id].signal();
}
void Bank::withdraw( unsigned int id, unsigned int amount ) {
    while(accounts[id] < amount) {
        conditions[id].wait();
    }
}
