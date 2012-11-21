#include <uC++.h>
#include <iostream>
#include "bottlingPlant.h"
#include "truck.h"

using namespace std;

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines, 
	unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ) : 
		prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour), 
			maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments) {
					
	is_closing = false;
	soda_produced = new unsigned int[4];
}

void BottlingPlant::main(){

	//create a truck
	Truck *truck = new Truck( prt, nameServer, *this, 
			numVendingMachines, maxStockPerFlavour );
	
	while( true ){
	
		_Accept( ~BottlingPlant ){
		
			is_closing = true;
			delete truck;
			break;
		} or _Accept( getShipment ){
		
			//in production
			yield(timeBetweenShipments);
			for( int i = 0; i < 4; i++ ){
		
				soda_produced[i] = generator(0, maxShippedPerFlavour);
			}
		
		}
	}
}

bool BottlingPlant::getShipment( unsigned int cargo[] ){

	if( is_closing )
		return is_closing;
		
	else {
	
		cargo = soda_produced;
		return false;
	}
}
