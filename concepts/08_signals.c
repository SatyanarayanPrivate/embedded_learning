
/*
- There are two signals that cannot be ignored: SIGKILL and SIGSTOP.

typedef void (*sighandler_t)(int);
sighandler_t signal (int signo, sighandler_t handler);
    - A successful call to signal() removes the current action taken on receipt of the signal signo, and instead handles the signal with the signal handler specified by handler.
    
# Waiting for a Signal, Any Signal
int pause (void);
    
# Sending a Signal
int kill (pid_t pid, int signo);
    - If pid is 0, signo is sent to every process in the invoking process' process group.
    - If pid is -1, signo is sent to every process for which the invoking process has permission to send a signal, except itself and init.
    - If pid is less than -1, signo is sent to the process group -pid.
    
# Sending a Signal to Yourself
int raise(int signo);

*/ 