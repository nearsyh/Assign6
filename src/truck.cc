#include <uC++.h>
#include <iostream>
#include "truck.h"

using namespace std;

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
		unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : 
			prt(prt), nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines), 
			maxStockPerFlavour(maxStockPerFlavour){
	
	soda_count = 0;
}

void Truck::main(){
	
	prt.print(Printer::Truck, 'S');
	//get vending machine list from name server.
	VendingMachine **vm_list = nameServer.getMachineList();
	
	//get soda from plant
	while( !plant.getShipment( cargo ) ){
	
		soda_count = 0;
		//got cargo, cal total soda count;
		for( int i = 0; i < 4; i++ ){

			soda_count += cargo[i];
		}

		prt.print( Printer::Truck, 'P', (int)soda_count);

		//for each vending machine, get its inventory and restock.
		for( unsigned int i = 0; (i < numVendingMachines) && 
			(soda_count > 0); i++ ){
		
			bool is_successful = true;
			unsigned int soda_unplenished = 0;

			unsigned int *soda_inventory = vm_list[i] -> inventory();
			prt.print( Printer::Truck, 'd', vm_list[i] -> getId(), soda_count );
			//restock soda up to max.
			for( unsigned int j = 0; j < 4; j++ ){
				
				
				//if soda inventory less than max, restock.
				if( soda_inventory[j] < maxStockPerFlavour ){
				
					unsigned int diff = maxStockPerFlavour - soda_inventory[j];
					//cargo not enough, restock all.
					if( cargo[j] < diff ){
							
						soda_inventory[j] += cargo[j];
						soda_count -= cargo[j];
						soda_unplenished += diff - cargo[j];
						cargo[j] = 0;
						is_successful = false;
					}
					
					//more cargo, restock up to max.
					else{
					
						soda_inventory[j] = maxStockPerFlavour;
						soda_count -= diff;
						cargo[j] -= diff;
					}
				}
				
			} //for
			
			//restock complete, signal.
			vm_list[i] -> restocked();
			
			//if restocking not successful
			if( !is_successful )
				prt.print( Printer::Truck, 'U', vm_list[i] -> getId(), soda_unplenished );
			
			prt.print( Printer::Truck, 'D', vm_list[i] -> getId(), soda_count );
		} //for
	
		//yield random number [1,10] before shipment.
		yield(generator(1,10));
		
	} //while

	prt.print( Printer::Truck, 'F' );
}
