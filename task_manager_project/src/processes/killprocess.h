// killprocess.h

#ifndef KILLPROCESS_H
#define KILLPROCESS_H

#include <signal.h>

class KillProcess {
public:
    KillProcess(pid_t processId);
    ~KillProcess();

    bool stopProcess();
    bool continueProcess();
    bool killProcess();

private:
    pid_t processId;
};

#endif // KILLPROCESS_H
