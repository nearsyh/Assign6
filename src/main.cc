#include "nameServer.h"
#include "vendingMachine.h"
#include "printer.h"
#include "config.h"
#include "bottlingPlant.h"
#include "bank.h"
#include "watCardOffice.h"
#include "student.h"
#include "MPRNG.h"
#include<iostream>
using namespace std;

PRNG generator;

#define TIME 100

#define CLEAN_ARRAY(length, array) {\
    for(unsigned int i = 0; i < length; i ++) delete array[i];\
}

void uMain::main() {
    /* input analysis and read config */
    int seed;
    ConfigParms param;
    processConfigFile(argc >= 2 ? argv[1] : "soda_config", param);
    seed = argc >= 3 ? atoi(argv[2]) : getpid();
    if(seed <= 0 || argc > 3) {
        cerr << "Usage: " << argv[0] << " [ config-file [ random-seed (> 0) ] ]" << endl;
        return;
    }

    /* initialize all parts */
    generator.seed(seed);
    Printer prt(param.numStudents, param.numVendingMachines, param.numCouriers );
    NameServer *nameServer = new NameServer(prt, param.numVendingMachines, param.numStudents);
    VendingMachine *machines[param.numVendingMachines];
    for(unsigned int i = 0; i < param.numVendingMachines; i ++)
        machines[i] = new VendingMachine(prt, *nameServer, i, param.sodaCost, param.maxStockPerFlavour );
    BottlingPlant *bottlingPlant = new BottlingPlant( prt, *nameServer, param.numVendingMachines, param.maxShippedPerFlavour, param.maxStockPerFlavour, param.timeBetweenShipments );
    Bank *bank = new Bank(param.numStudents);
    WATCardOffice *cardOffice = new WATCardOffice(prt, *bank, param.numCouriers );
    Student *students[param.numStudents];
    for(unsigned int i = 0; i < param.numStudents; i ++)
        students[i] = new Student(prt, *nameServer, *cardOffice, i, param.maxPurchases );

    for(int i = 0; i < TIME; i ++);
    CLEAN_ARRAY(param.numStudents, students);
	delete bottlingPlant;
    CLEAN_ARRAY(param.numVendingMachines, machines);
	delete nameServer;
    delete cardOffice;
    delete bank;
}
