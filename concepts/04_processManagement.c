
/* Running new process
int execl (const char *path, const char *arg, ...);
    - path: new program path which to be loaded.
    - arg: First argument to new program. The ellipsis signifies a variable number of arguments—the execl() function is variadic , which means that additional arguments may optionally follow, one by one. The list of arguments must be NULL-terminated
    - return:
        - Normally, execl( ) does not return. A successful invocation ends by jumping to the entry point of the new program, and the just-executed code no longer exists in the process' address space.
        - on error return -1 and sets errno.
    - example:
        int ret;
        ret = execl ("/bin/vi", "vi", "/home/kidd/hooks.txt", NULL);
        if (ret == -1)
            perror ("execl");

int execlp (const char *file, const char *arg, ...);
int execle (const char *path, const char *arg, ..., char * const envp[]);
int execv (const char *path, char *const argv[]);
int execvp (const char *file, char *const argv[]);
int execve (const char *filename, char *const argv[], char *const envp[]); 
    - The l and v delineate whether the arguments are provided via a l ist or an array ( v ector).
    - The p denotes that the user's full p ath is searched for the given file.
    - the e notes that a new environment is also supplied for the new process
    - example:
        const char *args[] = { "vi", "/home/kidd/hooks.txt", NULL };
        int ret;
        ret = execvp ("vi", args);
        if (ret == -1)
            perror ("execvp");

pid_t fork (void)
    - return: In the child, a successful invocation of fork( ) returns 0. In the parent, fork() returns the pid of the child. -1 on error with sets errno.
    - example:
        pid_t pid;
        pid = fork ( );
        if (pid > 0)
            printf ("I am the parent of pid=%d!\n", pid);
        else if (!pid)
            printf ("I am the baby!\n");
        else if (pid == -1)
            perror ("fork");

pid_t vfork (void);
    - A successful invocation of vfork() has the same behavior as fork(), except that the child process must immediately issue a successful call to one of the exec functions, or exit by calling _exit()
    - The vfork( ) system call avoids the address space and page table copies by suspending the parent process until the child terminates or executes a new binary image 
*/


/* Terminating Parent process
void exit(int status);
    - A call to exit() performs some basic shutdown steps, and then instructs the kernel to terminate the process.
    - The status parameter is used to denote the process' exit status.status & 0377 is returned to the parent.

- Before terminating the process, the C library performs the following shutdown steps, in order:
    1. Call any functions registered with atexit( ) or on_exit( ), in the reverse order of their registration.
    2. Flush all open standard I/O streams.
    3. Remove any temporary files created with the tmpfile( ) function.
void _exit(int status)
    - These steps finish all the work the process needs to do in user space, so exit( ) invokes the system call _exit( ) to let the kernel handle the rest of the termination process

int atexit (void (*function)(void));
    - A successful invocation of atexit( ) registers the given function to run during normal process termination; i.e. when a process is terminated via either exit( ) or a return from main( ).
    - If a process invokes an exec function, the list of registered functions is cleared (as the functions no longer exist in the new process' address space).
    - If a process terminates via a signal, the registered functions are not called.

int on_exit (void (*function)(int, void *), void *arg);
    - The status argument is the value passed to exit( ) or returned from main( ).
    - The arg argument is the second parameter passed to on_exit( ).
*/

/* Waiting for Terminated Child Processes
pid_t wait (int *status)
    - A call to wait( ) returns the pid of a terminated child, or -1 on error. If no child has terminated, the call blocks until a child terminates.

Waiting for a Specific Process
pid_t waitpid (pid_t pid, int *status, int options);
    - pid: for which process wait for.
        - <-1: Wait for any child process whose process group ID is equal to the absolute value of this value
            - example: passing -500 waits for any process in process group 500.
        - -1: Wait for any child process. This is the same behavior as wait().
        - 0: Wait for any child process that belongs to the same process group as the calling process.
        - > 0: Wait for any child process whose pid is exactly the value provided.
            - example: passing 500 waits for the child process with pid 500.
    - status: as like wait();
    - option: WNOHANG: Do not block, but return immediately if no matching child process has already terminated,
    - return:
        - On success, waitpid( ) returns the pid of the process whose state has changed.
        - If WNOHANG is specified, and the specified child or children have not yet changed state, waitpid( ) returns 0.
        - On error, the call returns -1, and errno is set.


Launching and Waiting for a New Process
#define _XOPEN_SOURCE        // if we want WEXITSTATUS, etc.
#include <stdlib.h>

int system (const char *command);
    - On success, the return value is the return status of the command as provided by wait()
*/

#if 0
/* Daemons
    - In general, a program performs the following steps to become a daemon:
        1. Call fork( ). This creates a new process, which will become the daemon.
        2. In the parent, call exit( ). This ensures that the original parent (the daemon's grandparent) is satisfied that its child terminated, that the daemon's parent is no
    longer running, and that the daemon is not a process group leader. This last point is a requirement for the successful completion of the next step.
        3. Call setsid( ), giving the daemon a new process group and session, both of which have it as leader. This also ensures that the process has no associated controlling terminal (as the process just created a new session, and will not assign one).
        4. Change the working directory to the root directory via chdir( ). This is done because the inherited working directory can be anywhere on the filesystem.Daemons tend to run for the duration of the system's uptime, and you don't want to keep some random directory open, and thus prevent an administrator from unmounting the filesystem containing that directory.
        5. Close all file descriptors. You do not want to inherit open file descriptors, and, unaware, hold them open.
        6. Open file descriptors 0, 1, and 2 (standard in, standard out, and standard error) and redirect them to /dev/null .
    - example:
        int main (void)
        {
            pid_t pid;
            int i;
            
            pid = fork ( ); /* create new process */
            if (pid == -1)
                return -1;
            else if (pid != 0)
                exit (EXIT_SUCCESS);
            if (setsid ( ) == -1) /* create new session and process group */
                return -1;
            if (chdir ("/") == -1) /* set the working directory to the root directory */
                return -1;
            for (i = 0; i < NR_OPEN; i++) /* close all open files--NR_OPEN is overkill, but works */
                close (i);
            /* redirect fd's 0,1,2 to /dev/null */
            open ("/dev/null", O_RDWR);  /* stdin */
            dup (0); /* stdout */
            dup (0); /* stderror */
            /* do its daemon thing... */
            return 0;
        }

#include <unistd.h>
int daemon (int nochdir, int noclose);
    - On success, the call returns 0. On failure, the call returns -1, and errno is set to a valid error code from fork() or setsid().

#endif 

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#if 0
int main() {


    printf ("\n");
    return 0;
}
#endif

#if 1

void child0_exit() {
    printf ("\n<<<<<<<< pid: %d exited calling %s >>>>>>>>>", getpid(), __func__);
    exit (-1);
}

int main () {

    pid_t retVal = 0x00;
    int count = 0x00;

    printf ("\n");

    for (count = 0x00; count < 3; count ++) {
        retVal = fork ();
        if (retVal == 0x00) {
            switch (count) {
                case 0x00:
                {
                    printf ("\nchild %d started", getpid());
                    sleep (2);
                    printf ("\nchild %d going to terminate", getpid());
                    atexit (child0_exit);
                }
                break;
                case 0x01:
                {
                    printf ("\nchild %d started", getpid());
                    while (1) { sleep (2);};
                    printf ("\nchild %d going to terminate", getpid());
                }
                break;
                case 0x02:
                {
                    printf ("\nchild %d started", getpid());
                    sleep (4);
                    printf ("\nchild %d going to terminate", getpid());
                    exit (-2);
                }
                break;
                default:
                {
                }
                break;
            }
            break;
        }
    }
    if (retVal > 0) {   
       //for (count = 0x00; count < 3; count ++)
        count = 0x00;
        while (count++ < 3)
        {
            /*
            int status = 0x00;
            retVal = wait (&status);
            printf ("\n>>>>>>>>>> Wait() retVal: %d with status: %d <<<<<<<<<<<<", retVal, status);
            */
            int status;
            pid_t pid;
            pid = wait (&status);
            if (pid == -1)
                perror ("wait");
            if (WIFEXITED (status))
                printf ("Child %d Normal termination with exit status=%d\n", pid, WEXITSTATUS (status));
            if (WIFSIGNALED (status))
                printf ("Child %d Killed by signal=%d%s\n", pid, WTERMSIG (status), WCOREDUMP (status) ? " (dumped core)" : "");
            if (WIFSTOPPED (status))
                printf ("Child %d Stopped by signal=%d\n", pid, WSTOPSIG (status));
            if (WIFCONTINUED (status))
                printf ("child %d Continued\n", pid);

            sleep(1);
        }
    }
    
    printf("\n");
    return 0;
}

#endif

#if 0
int main() {
    pid_t retVal = 0x00;

    retVal = fork();
    if (retVal == 0x00)
    {
        while (1)       // on parent process exit ppid chaanged to other init or upstart pid
        {
            sleep (2);
            printf ("\nchild pid: %d, ppid: %d", getpid(), getppid());
        }
    }
    else {
        printf ("\nParent pid: %d", getpid());
    }    

    printf ("\n");
    return 0;
}
#endif
