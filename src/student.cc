#include <uC++.h>
#include <iostream>
#include "student.h"
#include "MPRNG.h"
#include "printer.h"
#include "nameServer.h"
#include "vendingMachine.h"

using namespace std;
extern PRNG generator;

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, 
        unsigned int maxPurchases )
    : prt(prt), nameServer(nameServer), cardOffice(cardOffice), id(id), maxPurchases(maxPurchases) {

	ramFavFlavour = 0;
	ramMaxPurchases = 0;	
}

void Student::main() {

	//select random number of max purchases and favourite flavour
	ramMaxPurchases = generator(1, maxPurchases);
	ramFavFlavour = generator( 0, 3 );
	prt.print( Printer::Student, id, 'S', ramFavFlavour, ramMaxPurchases );
	//create a watcard
	FWATCard fWCard;
	getNewCard( fWCard );
	getVendingMachine();

	while ( ramMaxPurchases ){
		
		yield( generator(1, 10) );
		buySoda( fWCard );
		continue;		
	} //while

	delete fWCard();
	prt.print( Printer::Student, id, 'F' );
}

void Student::getVendingMachine(){
	
	vm = nameServer.getMachine( id );
	prt.print( Printer::Student, id, 'V', vm->getId() );
}

void Student::getNewCard( FWATCard &fWCard ){
	
	try{

		fWCard = cardOffice.create(id, 5);
	}

	catch( WATCardOffice::Lost ){

		//card lost, get another card.
		prt.print(Printer::Student, id, 'L');
		getNewCard( fWCard );
	}
}

void Student::buySoda( FWATCard &fWCard ){
	
	try{	
		VendingMachine::Status status = vm->buy( (VendingMachine::Flavours)ramFavFlavour, *fWCard() );
		if( status == VendingMachine::BUY ) { 
		
			prt.print(Printer::Student, id, 'B', fWCard() -> getBalance());			
			ramMaxPurchases --;
		}

		else if( status == VendingMachine::STOCK ){
				
			//stock not enough, get another vending machine.
			getVendingMachine();
		}

		else if( status == VendingMachine::FUNDS ){

			//transfer soda price + $5
			fWCard = cardOffice.transfer( id, (vm->cost() + 5), fWCard );
		}

	}

	catch( WATCardOffice::Lost ){

		prt.print(Printer::Student, id, 'L');
		getNewCard( fWCard );
		buySoda( fWCard );
	}
}
