#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/uio.h>

/* Advanced FILE IO



*/



/* readv() and writev()
int readv (int fd, struct iovec *iov, int count);
    - The readv() function reads count segments from the file descriptor fd into the buffers described by iov.
    - count must be larger than zero, and less than or equal to IOV_MAX, which is defined in <limits.h>.

int writev (int fd, struct iovec *iov, int count);
    - The writev() function writes at most count segments from the buffers described by iov into the file descriptor fd
    - count must be larger than zero, and less than or equal to IOV_MAX, which is defined in <limits.h>.
return:
    - On success, readv( ) and writev( ) return the number of bytes read or written, respectively. This number should be the sum of all count iov_len values.
    - On error, the system calls return -1, and set errno as appropriate.

Each iovec structure describes an independent disjoint buffer, which is called a segment :
#include <sys/uio.h>
struct iovec {
    void *iov_base;     // pointer to start of buffer 
    size_t iov_len;     // size of buffer in bytes
};
    - A set of segments is called a vector.
    - Each segment in the vector describes the address and length of a buffer in memory to or from which data should be written or read.
    - The readv() function fills each buffer of iov_len bytes completely before proceeding to the next buffer.
    - The writev( ) function always writes out all full iov_len bytes before proceeding to the next buffer.

*/


int main () {
    {// readv and writev
        struct iovec iov[3];
        ssize_t nr;
        int fd, i;
        char *buf[] = {
                        "The term buccaneer comes from the word boucan.\n",
                        "A boucan is a wooden frame used for cooking meat.\n",
                        "Buccaneer is the West Indies name for a pirate.\n" 
                        };
        fd = open ("03Test01", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fd == -1) {
            perror ("open");
            return 1;
        }
        /* fill out three iovec structures */
        for (i = 0; i < 3; i++) {
            iov[i].iov_base = buf[i];
            iov[i].iov_len = strlen (buf[i]);
        }
        /* with a single call, write them all out */
        nr = writev (fd, iov, 3);
        if (nr == -1) {
            perror ("writev");
            return 1;
        }
        printf ("wrote %d bytes\n", (int)nr);

        if (close (fd)) {
            perror ("close");
            return 1;
        }

        

        char foo[48] = {0}, bar[51] = {0}, baz[49] = {0};
        fd = open ("03Test01", O_RDONLY);
        if (fd == -1) {
            perror ("open");
            return 1;
        }
        /* set up our iovec structures */
        iov[0].iov_base = foo;
        iov[0].iov_len = sizeof (foo);
        iov[1].iov_base = bar;
        iov[1].iov_len = sizeof (bar);
        iov[2].iov_base = baz;
        iov[2].iov_len = sizeof (baz);
        /* read into the structures with a single call */
        nr = readv (fd, iov, 3);
        if (nr == -1) {
            perror ("readv");
            return 1;
        }
        for (i = 0; i < 3; i++)
            printf ("\n%d: %s\n", i, (char *) iov[i].iov_base);
        if (close (fd)) {
            perror ("close");
            return 1;
        }
    }
            
    printf ("\n");
    return 0;
}



