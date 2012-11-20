#include "nameServer.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents)
    : prt(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
        machineList = new VendingMachine*[numVendingMachines];
        index = 0;
}
NameServer::~NameServer() {
    delete []machineList;
}

void NameServer::VMregister(VendingMachine *machine) {
    assert(index < numVendingMachines);
    machineList[index ++] = machine;
}

VendingMachine* NameServer::getMachine( unsigned int id ) {
    assert(id < numVendingMachines && id >= 0);
    return machineList[id];
}

VendingMachine** NameServer::getMachineList() {
    assert(machineList != NULL);
    return machineList;
}

/********************************************/
/*             main function                */
/********************************************/
void NameServer::main() {
    while(index < numVendingMachines)
        _Accept(VMregister);
}
