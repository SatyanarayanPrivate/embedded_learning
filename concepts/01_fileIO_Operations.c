#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


/*
#include <fcntl.h>
int open (const char *fileName, int flags);
int open (const char *fileName, int flags, mode_t mode);
flags:
    - can be bitwise-ORed with one or more flag values.
    - should be one of O_RDONLY, O_WRONLY or O_RDWR
    - O_ASYNC: A signal (SIGIO by default) will be generated when the specified file becomes readable or writable. This flag is available only for terminals and sockets, not for regular files.
    - O_CREAT: If the file denoted by name does not exist, the kernel will create it. If the file already exists, this flag has no effect unless O_EXCL is also given.
    - O_SYNC: The file will be opened for synchronous I/O. No write operation will complete until the data has been physically written to disk; normal read operations are already synchronous, so this flag has no effect on reads.
    - O_NONBLOCK: If possible, the file will be opened in nonblocking mode. Neither the open( ) call, nor any other operation will cause the process to block (sleep) on the I/O. This behavior may be defined only for FIFOs.
    - O_SYNC: flag may be passed to open( ), indicating that all I/O on the file should be synchronized

mode: Permission of file
    - S_IRWXU: Owner has read, write, and execute permission.
    - S_IRUSR: Owner has read permission.
    - S_IWUSR: Owner has write permission.
    - S_IRWXG: Group has read, write, and execute permission.
    - S_IRGRP: Group has read permission.

return: On error, both return -1, and set errno to an appropriate error value.
*/


/*
#include <unistd.h>
ssize_t read (int fd, void *buf, size_t len);
    - Each call reads up to len bytes into buf from the current file offset of the file referenced by fd.
    - no bytes are available for reading, the call will block (sleep) until the bytes become available (if file descriptor not opened in nonblocking mode).
return: 
    - On success, the number of bytes written into buf is returned. On error, the call returns -1, and errno is set.
    - returns 0 to indicate end-of-file (EOF)
    - if O_NONBLOCK was given to open( ) and there is no data to read, the read( ) call will return -1, and set errno to EAGAIN instead of blocking
*/


/*

ssize_t write (int fd, const void *buf, size_t count);
    - A call to write( ) writes up to count bytes starting at buf to the current file position of the file referenced by the file descriptor fd.

return: 
    - On success, the number of bytes written is returned, and the file position is updated in kind.
    - On error, -1 is returned, and errno is set appropriately. 
    - A call to write( ) can return 0, but this return value does not have any special meaning; it simply implies that zero bytes were written.
*/


/*
    O_SYNC: flag may be passed to open( ), indicating that all I/O on the file should be synchronized
int fsync (int fd);
    - A call to fsync( ) ensures that all dirty data associated with the file mapped by the file descriptor fd is written back to disk. The file descriptor fd must be open for writing
    - The call writes back both data and metadata, such as creation timestamps, and other attributes contained in the inode.
return: 
    - It will not return until the hard drive says that the data and metadata are on the disk.
    - On success 0 and -1 on failure with error value errno.

int fdatasync (int fd);
    - This system call does the same thing as fsync( ), except that it only flushes data.
*/


/*
int close (int fd);
    - A call to close( ) unmaps the open file descriptor fd, and disassociates the process from the file.

return: returns 0 on success. On error, it returns -1, and sets errno appropriately.
*/


/*
off_t lseek (int fd, off_t pos, int origin);
    - he behavior of lseek( ) depends on the origin argument, which can be one of the following:
        - SEEK_CUR: The current file position of fd is set to its current value plus pos, which can be negative, zero, or positive.
        - SEEK_END: The current file position of fd is set to the current length of the file plus pos, which can be negative, zero, or positive. A pos of zero sets the offset to the end of the file.
        - SEEK_SET: The current file position of fd is set to pos. A pos of zero sets the offset to the beginning of the file.
return: 
    - call returns the new file position on success. On error, it returns -1 and errno is set as
appropriate.
*/


/*
ssize_t pread (int fd, void *buf, size_t count, off_t pos);
    - call reads up to count bytes into buf from the file descriptor fd at file position pos.

ssize_t pwrite (int fd, const void *buf, size_t count, off_t pos);
    - call writes up to count bytes from buf to the file descriptor fd at file position pos.

return: 
    - On success, both calls return the number of bytes read or written.
    - A return value of 0 from pread( ) indicates EOF; from pwrite( ), a return value of 0 indicates that the call did not write anything. 
    - On error, both calls return -1 and set errno appropriately.
*/

/*
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
int select (int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
    - The select( ) system call provides a mechanism for implementing synchronous multiplexing I/O.
    - A call to select( ) will block until the given file descriptors are ready to perform I/O, or until an optionally specified timeout has elapsed

    - n: value of the highest-valued file descriptor in any set, plus one.
    - readfds: set are watched to see if data is available for reading (that is, if a read operation will complete without blocking). 
    - writefds: set are watched to see if a write operation will complete without blocking. 
    - exceptfds: set are watched to see if an exception has occurred, or if out-of-band data is available (these states apply only to sockets)
    - timeout: a pointer to a timeval structure, which is defined as follows:
        #include <sys/time.h>
        struct timeval {
            long tv_sec;
            long tv_usec;
        };
    - A given set may be NULL, in which case select( ) does not watch for that event 

return:
    - On successful return, each set is modified such that it contains only the file descriptors that are ready for I/O of the type delineated by that set. 
        - For example, assume two file descriptors, with the values 7 and 9, are placed in the readfds set. 
        - When the call returns, if 7 is still in the set, that file descriptor is ready to read without blocking. 
        - If 9 is no longer in the set, it is probably not readable without blocking.
    - On success, select( ) returns the number of file descriptors ready for I/O, among all three sets. 
    - If a timeout was provided, the return value may be 0. On error, the call returns -1, and errno is set

FD_ZERO(fd_set *set);
    - FD_ZERO removes all file descriptors from the specified set. It should be called before every invocation of select( )

FD_SET(int fd, fd_set *set);
    - FD_SET adds a file descriptor to a given set

FD_CLR(int fd, fd_set *set);
    - FD_CLR removes a file descriptor from a given set

FD_ISSET(int fd, fd_set *set);
    - FD_ISSET tests whether a file descriptor is part of a given set. 
return:  
    - a nonzero integer if the file descriptor is in the set and 0 if it is not.
    - FD_ISSET is used after a call from select( ) returns to test whether a given file descriptor is ready for action.
*/

int main () {

    int fd1 = 0x00;
    int fd2 = 0x00;
    ssize_t ret = 0x00;
    
    // Try to open file not present: will return error with -1
    fd1 = open ("fileNotPresent", O_RDONLY); 
    printf ("\nfd1: %d", fd1);
    close (fd1); 


    // Open same file multiple times 
    fd1 = open ("fileRCr1", O_CREAT); 
    printf ("\nfd1: %d", fd1);      
    fd2 = open ("fileRCr1", O_RDONLY); 
    printf ("\nfd2: %d", fd2);      
    close (fd1); 
    close (fd2);
    
    { // Permission 
        
        char buf[10] = {0};
        //extern int errno;

        fd1 = open ("fileRwCr2", O_WRONLY | O_CREAT, S_IRWXU); 
        ret = read (fd1, buf, 2);   // return error
        if (ret == -1)
        {
            printf ("\nFailed to read file with error %d", errno);
        }
        printf ("\nfd1: %d ret: %d", fd1, (int)ret);
        close (fd1); 
    }   

   { // read non-blocking
        char buf[10] = {0};
    
        fd1 = open ("fileRwCr2", O_RDONLY | O_CREAT, S_IRWXU); 
        start:
        ret = read (fd1, buf, 3);
        printf ("\nfd1: %d ret: %d errno: %d", fd1, (int)ret, errno);
        if (ret == -1) {
            if (errno == EINTR) {
                goto start; /* failed due to system interrupt */
            }
            if (errno == EAGAIN) {
                /* resubmit later */
            }
            else {
                /* error */
            }
        }
        close (fd1); 
    }   

    {   // write

        char buf1[] = {"test data"};
        char *buf = buf1;
        ssize_t len = sizeof(buf1);
        ssize_t retv = 0x00;

        fd1 = open ("fileRwCr2", O_WRONLY | O_CREAT | O_NONBLOCK, S_IRWXU); 
        printf ("\nfd1: %d retv: %d errno: %d", fd1, (int)retv, errno);
        retv = write (fd1, buf, len);
        printf ("\nfd1: %d retv: %d errno: %d", fd1, (int)retv, errno);
        /*
        while (len != 0 && (retv = write (fd1, buf, len) != 0)) {
        printf ("\nfd1: %d retv: %d errno: %d len: %d", fd1, (int)retv, errno, len);
            if (ret == -1) {
                if (errno == EINTR)
                    continue;
                perror ("write");
                break;
            }
            len -= retv;
            buf += retv;
        }
        */
        close (fd1); 
    }

    {//
#define TIMEOUT 5
#define BUF_LEN 1024
        struct timeval tv;
        fd_set readfds;
        int ret;
        /* Wait on stdin for input. */
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        /* Wait up to five seconds. */
        tv.tv_sec = TIMEOUT;
        tv.tv_usec = 0;
        /* All right, now block! */
        ret = select (STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
        if (ret == -1) {
            perror ("select");
            return 1;
        } else if (!ret) {
            printf ("\n%d seconds elapsed.\n", TIMEOUT);
            return 0;
        }
        /*
        * Is our file descriptor ready to read?
        * (It must be, as it was the only fd that
        * we provided and the call returned
        * nonzero, but we will humor ourselves.)
        */
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            char buf[BUF_LEN+1];
            int len;
            /* guaranteed to not block */
            len = read (STDIN_FILENO, buf, BUF_LEN);
            if (len == -1) {
                perror ("read");
                return 1;
            }
            if (len) {
            buf[len] = '\0';
            printf ("\nread: %s\n", buf);
            }
        }
    }
            

    printf ("\n");
    return 0;
}
