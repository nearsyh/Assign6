#include <uSemaphore.h>
#include "nameServer.h"
#include "printer.h"
#include "MPRNG.h"

_Task BottlingPlant {
	
	Printer &prt;
	NameServer &nameServer;
	MPRNG mprng;
	Semaphore produced(0);
	unsigned int numVendingMachines, maxShippedPerFlavour, 
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

