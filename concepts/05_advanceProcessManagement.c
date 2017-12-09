


/* Yielding the Processor
int sched_yield (void);
    - A call to sched_yield( ) results in suspension of the currently running process, after which the process scheduler selects a new process to run.
    - return: On success, the call returns 0; on failure, it returns -1, and sets errno.

int nice (int inc);
    - A successful call to nice( ) increments a process' nice value by inc.
    - Only a process with the CAP_SYS_NICE capability (effectively, processes owned by root) may provide a negative value for inc, decreasing its nice value, and thereby
increasing its priority. Consequently, nonroot processes may only lower their priorities (by increasing their nice values).
    - if inc equal to zero return current nice value.
    - returns the newly updated value.

#include <sys/time.h>
#include <sys/resource.h>
int getpriority (int which, int who);
int setpriority (int which, int who, int prio);
    - These calls operate on the process, process group, or user, as specified by which and who.
    - The value of which must be one of PRIO_PROCESS, PRIO_PGRP, or PRIO_USER, in which case 
    - who specifies a process ID, process group ID, or user ID, respectively.
    - If who is 0, the call operates on the current process ID, process group ID, or user ID, respectively.
    - return: A call to getpriority( ) returns the highest priority (lowest numerical nice value) of any of the specified processes.

int ioprio_get (int which, int who)
int ioprio_set (int which, int who, int ioprio)
*/



/*
*/

#if 0
int main() {

    printf("\n");
    return 0;
}
#endif
