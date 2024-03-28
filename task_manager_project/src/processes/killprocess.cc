// killprocess.cc

#include "killprocess.h"
#include <unistd.h>

KillProcess::KillProcess(pid_t pid) : processId(pid) {}

KillProcess::~KillProcess() {}

bool KillProcess::stopProcess() {
    if (kill(processId, SIGSTOP) == 0) {
        return true;
    } else {
        // Handle error, e.g., print an error message
        return false;
    }
}

bool KillProcess::continueProcess() {
    if (kill(processId, SIGCONT) == 0) {
        return true;
    } else {
        // Handle error, e.g., print an error message
        return false;
    }
}

bool KillProcess::killProcess() {
    if (kill(processId, SIGKILL) == 0) {
        return true;
    } else {
        // Handle error, e.g., print an error message
        return false;
    }
}
