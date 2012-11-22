#pragma once
#include<uC++.h>
#include "watCard.h"
#include<queue>
using namespace std;

_Monitor Printer;
_Task Bank;

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

    _Task Courier {
        Job *job;
        WATCardOffice &cardOffice;
        void process() {
            if(!job->args.card)
                job->args.card = new WATCard();
            //bank.withdraw(job->args.amount);
            (job->args.card)->deposit(job->args.amount);
            job->result.delivery(job->args.card);
        }
        void main() {
            while(true) {
                job = cardOffice.requestWork();
                process();
            }
        }
        public:
        Courier(WATCardOffice &cardOffice)
            : cardOffice(cardOffice) {};
    };
    Courier **couriers;
};
