#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H
#include <uC++.h>

#define FLA_SIZE 3
_Monitor Printer;
_Task NameServer;
_Task WATCard;

_Task VendingMachine {
    Printer &prt;
    NameServer &nameServer;
    unsigned int id, sodaCost, maxStockPerFlavour; 
    unsigned int inventoryList[FLA_SIZE];
    void main();
  public:
    enum Flavours { ORANGE, GINGER, APPLE };// flavours of soda (YOU DEFINE)
    enum Status { BUY , STOCK, FUNDS };		// purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif
