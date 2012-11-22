#pragma once
#include "printer.h"
#include "nameServer.h"
#include "bottlingPlant.h"
#include "vendingMachine.h"

extern PRNG generator;

_Task Truck {
	Printer &prt;
	NameServer &nameServer;
	BottlingPlant &plant;
	unsigned int cargo[4];
	unsigned int soda_count, numVendingMachines, maxStockPerFlavour;
    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};
