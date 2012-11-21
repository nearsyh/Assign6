#include "nameServer.h"
#include "vendingMachine.h"
#include "printer.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents)
    : prt(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
        machineList = new VendingMachine*[numVendingMachines];
        idToIndex = new int[numVendingMachines];
        index = 0;
}
NameServer::~NameServer() {
    delete []machineList;
    delete []idToIndex;
}

void NameServer::VMregister(VendingMachine *machine) {
    assert(index < numVendingMachines);
    idToIndex[machine->getId()] = index;
    machineList[index ++] = machine;
    prt.print(Printer::NameServer, 'R', machine->getId());
}

VendingMachine* NameServer::getMachine( unsigned int id ) {
    assert(id < numVendingMachines && id >= 0);
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
    prt.print(Printer::NameServer, 'F');
}
