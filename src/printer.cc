#include "printer.h"
#include<iostream>
using namespace std;


Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers )
    : numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {
        total = numStudents + numVendingMachines + numCouriers + 5;
        change = new bool[total];
        param[0] = new unsigned int[total];
        param[1] = new unsigned int[total];
        numParam = new unsigned int[total];
        states = new char[total];
        memset(change, 0, sizeof(bool)*total);
        cout << "Parent\tWATOff\tNames\tTruck\tPlant\t";
        for(unsigned int i = 0; i < numStudents; i ++) 
            cout << "Stud" << i << "\t";
        for(unsigned int i = 0; i < numVendingMachines; i ++)
            cout << "Mach" << i << "\t";
        for(unsigned int i = 0; i < numCouriers; i ++)
            cout << "Cour" << i << "\t";
        cout << endl;
        for(unsigned int i = 0; i < total; i ++)
            cout << "*******\t";
        cout << endl;
}

Printer::~Printer() {
    delete []change;
    delete []param[0];
    delete []param[1];
    delete []states;
    delete []numParam;
    for(int i = 0; i < 23; i ++) cout << "*";
    cout << endl;
}

void Printer::printState() {
    for(unsigned int i = 0; i < total; i ++) {
        if(change[i]) {
            cout << (char)states[i];
            switch(numParam[i]) {
                case 0: break;
                case 1: cout << " " << param[0][i]; break;
                case 2: cout << " " << param[0][i] << "," << param[1][i]; break;
                default: break;
            }
        }
        cout << "\t";
        change[i] = false;
    } cout << endl;
    for(unsigned int i = 0; i < total; i ++)
        assert(!change[i])
}
void Printer::printFinish(unsigned int index) {
    for(unsigned int i = 0; i < index; i ++) cout << "...\t";
    cout << "F\t";
    for(unsigned int i = index + 1; i < total; i ++) cout << "...\t";
    cout << endl;
}

int Printer::KIND_ID(Kind kind, int id = 0) {
    assert(kind <= Courier);
    if(kind < Student) return (int)kind;
    else if(kind == Student) return 5 + id;
    else if(kind == Vending) return 5 + numStudents + id;
    else if(kind == Courier) return 5 + numStudents + numVendingMachines + id;
    else return -1;
}

void Printer::print( Kind kind, char state ) {
    unsigned int index = KIND_ID(kind);
    if(change[index]) printState();
    states[index] = state;
    numParam[index] = 0;
    if(state == 'F') printFinish(index);
    else change[index] = true;
}
void Printer::print( Kind kind, char state, int value1 ) {
    print(kind, state);
    unsigned int index = KIND_ID(kind);
    param[0][index] = value1;
    numParam[index] = 1;
    assert(change[index]);
}
void Printer::print( Kind kind, char state, int value1, int value2 ) {
    print(kind, state, value1);
    unsigned int index = KIND_ID(kind);
    param[1][index] = value2;
    numParam[index] = 2;
    assert(change[index]);
}
void Printer::print( Kind kind, unsigned int id, char state ) {
    unsigned int index = KIND_ID(kind, id);
    if(change[index]) printState();
    states[index] = state;
    numParam[index] = 0;
    if(state == 'F') printFinish(index);
    else change[index] = true;
}
void Printer::print( Kind kind, unsigned int id, char state, int value1 ) {
    print(kind, id, state);
    unsigned int index = KIND_ID(kind, id);
    param[0][index] = value1;
    numParam[index] = 1;
    assert(change[index]);
}
void Printer::print( Kind kind, unsigned int id, char state, int value1, int value2 ) {
    print(kind, id, state, value1);
    unsigned int index = KIND_ID(kind, id);
    param[1][index] = value2;
    numParam[index] = 2;
    assert(change[index]);
}
