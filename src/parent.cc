#include "parent.h"
#include "printer.h"
#include "bank.h"
#include "MPRNG.h"

extern PRNG generator;

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay)
    : prt(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}

void Parent::main() {
    prt.print(Printer::Parent, 'S');
    while(true) {
        _Accept(~Parent) {
            break;
        } else {
            /* pick a student and an amount randomly */
            int id = generator(numStudents-1);
            int money = generator(1, 3);
            yield(parentalDelay);
            bank.deposit(id, money);
            prt.print(Printer::Parent, 'D', id, money);
        }
    }
    prt.print(Printer::Parent, 'F');
}
