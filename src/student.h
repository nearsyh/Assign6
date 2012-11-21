#ifndef STUDENT_H
#define STUDENT_H

_Monitor Printer;
_Task NameServer;
_Task WATCardOffice;

_Task Student {
    Printer prt;
    NameServer nameServer;
    WATCardOffice cardOffice;
    unsigned id, maxPurchases;
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif
