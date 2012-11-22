#pragma once
#include<uC++.h>
_Monitor Bank {
    unsigned int *accounts;
    uCondition *conditions;
  public:
    Bank( unsigned int numStudents );
    ~Bank();
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};


