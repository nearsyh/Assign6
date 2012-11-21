#include <uC++.h>
#include <iostream>
#include <ctime>

using namespace std;

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
		unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, 
		unsigned int timeBetweenShipments ) : 
			prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), 
			maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour),
			timeBetweenShipments(timeBetweenShipments) {
					
	//initialize MPRNG with time seed.				
	time_t timet;
	mprng.seed(time(&timet));	
	
	is_closing = false;
	soda_produced = new unsigned int[4];
}

void BottlingPlant::main(){

	//create a truck
	Truck *truck = new Truck( prt, nameServer, this, 
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
		
				soda_produced[i] = mprng(0, maxShippedPerFlavour);
			}
		
			produced.V();
		}
	}
}

bool BottlingPlant::getShipment( unsigned int cargo[] ){

	if( is_closing )
		return is_closing;
		
	else {
	
		produced.P();
		cargo = soda_produced;
		return false;
	}
}