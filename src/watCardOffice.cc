#include "watCardOffice.h"
#include "watCard.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
    : prt(prt), bank(bank), numCouriers(numCouriers) {
        couriers = new Courier[numCouriers];
}

WATCardOffice::~WATCardOffice() {
    assert(job.empty());
    delete []couriers;
}

FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    Job *job = new Job(sid, amount, NULL);
    jobList.push(job);
    return job->result;
}

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
    Job *job = new Job(sid, amount, card);
    jobList.push(job);
    return job->result;
}

Job* WATCardOffice::requestWork() {
    return job->pop();
}

void WATCardOffice::main() {
    // create couriers;
    while(true) {
        _Accept(~WATCardOffice) {
            break;
        } or _Accept(create) {
        } or _Accept(transfer) {
        } or _When(!job->empty()) _Accept(requestWork);
    }
    prt.Print(Printer::WATCardOffice, 'F');
}
