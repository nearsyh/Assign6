#ifndef NAMESERVER_H
#define NAMESERVER_H
#include<uC++.h>

_Task VendingMachine;
_Monitor Printer;

_Task NameServer {
    Printer &prt;
    unsigned int numVendingMachines, numStudents;
    VendingMachine **machineList;
    int *idToIndex;                                // transfer the student id to the index of the vending machine
    unsigned int index;                                     // store the current index
    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif
