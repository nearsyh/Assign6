#ifndef NAMESERVER_H
#define NAMESERVER_H
#include<uC++.h>

_Task VendingMachine;
_Monitor Printer;

_Task NameServer {
    Printer &prt;
    unsigned int numVendingMachines, numStudents;
    VendingMachine **machineList;
    unsigned int index;
    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif
