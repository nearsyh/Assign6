#include "watCard.h"

WATCard::WATCard() {
    balance = 0;
}

void WATCard::deposit( unsigned int amount ) {
    balance += amount;
}
void WATCard::withdraw( unsigned int amount ) {
    balance -= amount;
    assert(balance >= 0);
}
unsigned int WATCard::getBalance() {
    assert(balance >= 0);
    return balance;
}
