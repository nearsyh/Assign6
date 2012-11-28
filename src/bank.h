#pragma once
#include<uC++.h>
_Monitor Bank {
    unsigned int *accounts;
    uCondition *conditions;         // every account should be independent from others, every one has its own lock
  public:
    Bank( unsigned int numStudents );
    ~Bank();
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};


