#pragma once
#include <uC++.h>
#include "nameServer.h"
#include "printer.h"
#include "MPRNG.h"

extern PRNG generator;

_Task BottlingPlant {
	
	Printer &prt;
	NameServer &nameServer;
	unsigned int soda_count, numVendingMachines, maxShippedPerFlavour, 
				 maxStockPerFlavour, timeBetweenShipments;
	
	unsigned int *soda_produced;
	bool is_closing;
    void main();
    
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );

    bool getShipment( unsigned int cargo[] );
};
