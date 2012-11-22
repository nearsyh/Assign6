#include "watCardOffice.h"
#include "watCard.h"
#include "printer.h"
#include "bank.h"
#include "MPRNG.h"
#include <iostream>
using namespace std;

extern PRNG generator;

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
    : prt(prt), bank(bank), numCouriers(numCouriers) {
    couriers = new Courier*[numCouriers];
    isFinished = true;
    for(unsigned int i = 0; i < numCouriers; i ++)
        couriers[i] = new Courier(prt, i, *this, bank);
}

WATCardOffice::~WATCardOffice() {
    assert(jobList.empty());
    isFinished = true;
    for(unsigned int i = 0; i < numCouriers; i ++)
        delete couriers[i];
    delete []couriers;
}

FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    prt.print(Printer::WATCardOffice, 'C', sid, amount);
    Job *job = new Job(Args(sid, amount, NULL));
    jobList.push(job);
    return job->result;
}

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
    prt.print(Printer::WATCardOffice, 'T', sid, amount);
    Job *job = new Job(Args(sid, amount, card));
    jobList.push(job);
    return job->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
    prt.print(Printer::WATCardOffice, 'W');
    if(jobList.empty()) return NULL;
    Job *job = jobList.front();
    jobList.pop();
    return job;
}

void WATCardOffice::main() {
    prt.print(Printer::WATCardOffice, 'S');
    while(true) {
        _Accept(~WATCardOffice) {
            for(unsigned int i = 0; i < numCouriers; i ++)
                _Accept(requestWork);
            break;
        } or _Accept(create) {
        } or _Accept(transfer) {
        } or _When(!jobList.empty()) _Accept(requestWork) {
        }
    }
    prt.print(Printer::WATCardOffice, 'F');
}

/*****************************************************************/
/*                      task courier                             */
/*****************************************************************/
WATCardOffice::Courier::Courier(Printer &prt, unsigned int id, WATCardOffice &cardOffice, Bank &bank)
            : prt(prt), id(id), cardOffice(cardOffice), bank(bank) {};

void WATCardOffice::Courier::process() {
    if(!job->args.card)
        job->args.card = new WATCard();
    prt.print(Printer::Courier, id, 't', job->args.sid, job->args.amount);
    bank.withdraw(job->args.sid, job->args.amount);
    (job->args.card)->deposit(job->args.amount);
    if(generator(1, 6) == 1) assert(job->result.exception(new Lost()));
    job->result.delivery(job->args.card);
    prt.print(Printer::Courier, id, 'T', job->args.sid, job->args.amount);
    delete job;
}

void WATCardOffice::Courier::main() {
    prt.print(Printer::Courier, id, 'S');
    while(true) {
        job = cardOffice.requestWork();
        if(job) process();
        else break;
    }
    prt.print(Printer::Courier, id, 'F');
}
