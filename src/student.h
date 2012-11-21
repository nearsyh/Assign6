#ifndef STUDENT_H
#define STUDENT_H

#include <uC++.h>
#include "printer.h"
#include "nameServer.h"
#include "watCardOffice.h"
#include "vendingMachine.h"
//_Monitor Printer;
//_Task NameServer;
//_Task WATCardOffice;

_Task Student {
    Printer &prt;
    NameServer &nameServer;
    WATCardOffice &cardOffice;
    unsigned id, maxPurchases;
	VendingMachine *vm;
	unsigned int ramFavFlavour, ramMaxPurchases;
    void main();
	void getVendingMachine();
	void getNewCard( FWATCard &fWCard );
	void buySoda( FWATCard &fWCard );
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif
