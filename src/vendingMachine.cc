#include "vendingMachine.h"
#include "nameServer.h"
#include "printer.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id,
        unsigned int sodaCost, unsigned int maxStockPerFlavour )
    : prt(prt), nameServer(nameServer), id(id), sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour) {
        memset(inventoryList, 0, sizeof(int)*FLA_SIZE);
}
    
_Nomutex unsigned int VendingMachine::cost() {
    return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
    return id;
}

unsigned int * VendingMachine::inventory() {
    return inventoryList;
}

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ) {
    //TODO
    return BUY;
}

void VendingMachine::restocked() {
    //TODO
}

void VendingMachine::main() {
    prt.print(Printer::Vending, id, 'S', sodaCost);
    nameServer.VMregister(this);
    //TODO
    prt.print(Printer::Vending, id, 'F');
}
