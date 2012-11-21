#include <uC++.h>
#include <iostream>
#include <ctime>

using namespace std;

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
		unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : 
			prt(prt), nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines), 
			maxStockPerFlavour(maxStockPerFlavour){
	
	//initialize MPRNG with time seed.
	time_t timet;
	mprng.seed(time(&timet));	          	  
}

void Truck::main(){

	//get vending machine list from name server.
	VendingMachine* vm_list[] = nameServer.getMachineList();
	
	//yield random number [1,10] before shipment.
	yield(mprng(1,10));
	
	//get soda from plant
	while( !plant.getShipment( cargo ) ){
		
		//for each vending machine, get its inventory and restock.
		for( int i = 0; i < numVendingMachines; i++ ){
		
			unsigned int soda_inventory[] = vm_list[i] -> inventory();
			
			//restock soda up to max.
			for( int j = 0; 
				j < sizeof(soda_inventory)/sizeof(unsigned int); i++ ){
				
				//if soda inventory less than max, restock.
				if( soda_inventory[j] < maxStockPerFlavour ){
				
					int diff = maxStockPerFlavour - soda_inventory[j];
					//cargo not/just enough, restock all.
					if( cargo[j] <= diff ){
					
						soda_inventory[j] += cargo[j];
						cargo[j] = 0;
					}
					
					//more cargo, restock up to max.
					else{
					
						soda_inventory[j] = maxStockPerFlavour;
						cargo[j] -= diff;
					}
				}
			} //for
			
			//restock complete, signal.
			vm_list[i] -> restocked();
			
		} //for
	} //while
}