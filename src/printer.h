#ifndef PRINTER_H
#define PRINTER_H
#include<uC++.h>
_Monitor Printer {
    unsigned int numStudents, numVendingMachines, numCouriers, total;
    bool *change;
    unsigned int *param[2], *numParam;
    char *states;
    void printState();
    void printFinish(unsigned int index);
public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    ~Printer();
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
private:
    int KIND_ID(Kind kind, int id);
};
#endif
