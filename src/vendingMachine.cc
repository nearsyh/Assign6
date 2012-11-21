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
    prt.print(Printer::Vending, id, 'r');
    return inventoryList;
}

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ) {
    if(inventoryList[flavour] <= 0) return STOCK;
    // TODO card balance
    return BUY;
}

void VendingMachine::restocked() {
    //TODO
}

void VendingMachine::main() {
    prt.print(Printer::Vending, id, 'S', sodaCost);
    nameServer.VMregister(this);
    //TODO
    while(true) {
        _Accept(~VendingMachine)
        or _Accept(inventory) {
            _Accept(restocked);
            prt.print(Printer::Vending, id, 'R');
        } or _Accpent(buy);
    }
    prt.print(Printer::Vending, id, 'F');
}
