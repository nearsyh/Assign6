#pragma once
#include <uC++.h>
_Monitor Printer;
_Monitor Bank;

_Task Parent {
    Printer &prt;
    Bank &bank;
    unsigned int numStudents, parentalDelay;
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};
