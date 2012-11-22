#include "watCardOffice.h"
#include "watCard.h"
#include "printer.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
    : prt(prt), bank(bank), numCouriers(numCouriers) {
        couriers = new Courier*[numCouriers];
        for(unsigned int i = 0; i < numCouriers; i ++)
            couriers[i] = new Courier(*this);
}

WATCardOffice::~WATCardOffice() {
    assert(jobList.empty());
    for(unsigned int i = 0; i < numCouriers; i ++)
        delete couriers[i];
    delete []couriers;
}

FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    Job *job = new Job(Args(sid, amount, NULL));
    jobList.push(job);
    return job->result;
}

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
    Job *job = new Job(Args(sid, amount, card));
    jobList.push(job);
    return job->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
    Job *job = jobList.front();
    jobList.pop();
    return job;
}

void WATCardOffice::main() {
    // create couriers;
    while(true) {
        _Accept(~WATCardOffice) {
            break;
        } or _Accept(create) {
        } or _Accept(transfer) {
        } or _When(!jobList.empty()) _Accept(requestWork);
    }
    prt.print(Printer::WATCardOffice, 'F');
}

/*****************************************************************/
/*                      task courier                             */
/*****************************************************************/
WATCardOffice::Courier::Courier(WATCardOffice &cardOffice)
            : cardOffice(cardOffice) {};

void WATCardOffice::Courier::process() {
    if(!job->args.card)
        job->args.card = new WATCard();
    //bank.withdraw(job->args.amount);
    (job->args.card)->deposit(job->args.amount);
    job->result.delivery(job->args.card);
}
void WATCardOffice::Courier::main() {
    while(true) {
        job = cardOffice.requestWork();
        process();
    }
}
