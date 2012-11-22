#pragma once
#include<uC++.h>
#include<queue>
#include "watCard.h"
using namespace std;

_Monitor Printer;
_Monitor Bank;

_Task WATCardOffice {
    struct Args {
        unsigned int sid;
        unsigned int amount;
        WATCard *card;
        Args(unsigned int sid, unsigned int amount, WATCard *card)
            : sid(sid), amount(amount), card(card) {}
    };
    struct Job {				// marshalled arguments and return future
        Args args;				// call arguments (YOU DEFINE "Args")
        FWATCard result;			// return future
        Job( Args args ) : args( args ) {}
    };
    _Task Courier {
        Job *job;
        WATCardOffice &cardOffice;
        void process();
        void main();
    public:
        Courier(WATCardOffice &cardOffice);
    };
    void main();
public:
    _Event Lost {};
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    FWATCard create( unsigned int sid, unsigned int amount );
    FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
private:
    Printer &prt;
    Bank &bank;
    unsigned int numCouriers;
    queue<Job*> jobList;
    Courier **couriers;
};
