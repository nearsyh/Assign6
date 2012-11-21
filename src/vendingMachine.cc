#include "vendingMachine.h"
#include "nameServer.h"
#include "watCard.h"
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
    else if(card.getBalance() < sodaCost) return FUNDS;// TODO card balance
    else {
        card.withdraw(sodaCost);
        prt.print(Printer::Vending, id, 'R');
        return BUY;
    }
}

void VendingMachine::restocked() {
    //TODO
    prt.print(Printer::Vending, id, 'R');
}

void VendingMachine::main() {
    prt.print(Printer::Vending, id, 'S', sodaCost);
    nameServer.VMregister(this);
    //TODO
    while(true) {
        _Accept(~VendingMachine) {
            prt.print(Printer::Vending, id, 'F');
        } or _Accept(inventory) {
            _Accept(restocked);
        } or _Accept(buy);
    }
}
