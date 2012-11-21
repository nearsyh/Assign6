#include "nameServer.h"
#include "vendingMachine.h"
#include "printer.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents)
    : prt(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
        machineList = new VendingMachine*[numVendingMachines];
        idToIndex = new int[numStudents];
        index = 0;
        for(int i = 0; i < numStudents; i ++)
            idToIndex[i] = -1;
}
NameServer::~NameServer() {
    delete []machineList;
    delete []idToIndex;
}

void NameServer::VMregister(VendingMachine *machine) {
    assert(index < numVendingMachines);
    machineList[index ++] = machine;
    prt.print(Printer::NameServer, 'R', machine->getId());
}

VendingMachine* NameServer::getMachine( unsigned int id ) {
    assert(id < numStudents && id >= 0);
    if(idToIndex[id] == -1) idToIndex[id] = id % numVendingMachines;
    else idToIndex[id] = (idToIndex[id] + 1) % numVendingMachines;
    return machineList[idToIndex[id]];
}

VendingMachine** NameServer::getMachineList() {
    assert(machineList != NULL);
    return machineList;
}

/********************************************/
/*             main function                */
/********************************************/
void NameServer::main() {
    prt.print(Printer::NameServer, 'S');
    while(index < numVendingMachines)
        _Accept(VMregister);
    while(true) {
        _Accept(~NameServer) {
            prt.print(Printer::NameServer, 'F');
        } or _Accept(getMachineList) {
        } or _Accept(getMachine);
    }
}
