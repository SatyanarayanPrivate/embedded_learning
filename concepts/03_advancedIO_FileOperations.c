#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/mman.h>


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


/* mmap()
- When you map a file descriptor, the file's reference count is incremented.
- Therefore, you can close the file descriptor after mapping the file, and your process will still have access to it.
- The corresponding decrement of the file's reference count will occur when you unmap the file, or when the process terminates.
- SIGBUS: signal is generated when a process attempts to access a region of a mapping that is no longer valid—example, because the file was truncated after it was mapped.
- SIGSEGV: This signal is generated when a process attempts to write to a region that is mapped read-only.

void * mmap (void *addr, size_t len, int prot, int flags, int fd, off_t offset);
    - mmap( ) asks the kernel to map len bytes of the object represented by the file descriptor fd, starting at offset bytes into the file, into memory. If addr is included, it indicates a preference to use that starting address in memory. The access permissions are dictated by prot, and additional behavior can be given by flags.
    - addr: most of cases 0
    - prot: 
        - PROT_NONE: not be accessed.
        - PROT_READ: The pages may be read.
        - PROT_WRITE: The pages may be written.
        - PROT_EXEC: The pages may be executed.
    - flags: type of mapping, and some elements of its behavior
        - MAP_FIXED:
            - If the kernel is unable to place the mapping at the given address, the call fails.
            - If the address and length parameters overlap an existing mapping, the overlapped pages are discarded and replaced by the new mapping.
        - MAP_PRIVATE:
            - States that the mapping is not shared. The file is mapped copy-on-write
            - any changes made in memory by this process are not reflected in the actual file, or in the mappings of other processes.
        - MAP_SHARED:
            - Shares the mapping with all other processes that map this same file.
            - Writing into the mapping is equivalent to writing to the file. Reads from the mapping will reflect the writes of other processes.
    - return:
            - On success, a call to mmap( ) returns the location of the mapping.
            - On failure, the call returns MAP_FAILED, and sets errno appropriately.
            - A call to mmap( ) never returns 0.
    - example: the following snippet maps the file backed by fd, beginning with its first byte, and extending for len bytes, into a read-only mapping
        void *p;
        p = mmap (0, len, PROT_READ, MAP_SHARED, fd, 0);
        if (p == MAP_FAILED)
            perror ("mmap");

int munmap (void *addr, size_t len);
    - return: On success, munmap( ) returns 0; on failure, it returns -1, and errno is set appropriately. The only standard errno value is EINVAL
*/

/* Resizing a Mapping
void * mremap (void *addr, size_t old_size, size_t new_size, unsigned long flags);    
    - The flags parameter can be either 0 or MREMAP_MAYMOVE, which specifies that the kernel is free to move the mapping.
    - return: returns a pointer to the newly resized memory mapping. On failure, it returns MAP_FAILED, and sets errno.
*/

/* Changing the Protection of a Mapping
int mprotect (const void *addr, size_t len, int prot);
    - return: On success, mprotect( ) returns 0. On failure, it returns -1, and sets errno.
*/


/* Synchronizing a File with a Mapping
- A call to msync( ) flushes back to disk any changes made to a file mapped via mmap(), synchronizing the mapped file with the mapping.
- Without invocation of msync( ), there is no guarantee that a dirty mapping will be written back to disk until the file is unmapped.

int msync (void *addr, size_t len, int flags);
    - flags:
        - MS_ASYNC:
            - Specifies that synchronization should occur asynchronously.
            - The update is scheduled, but the msync( ) call returns immediately without waiting for the writes to take place.
        - MS_INVALIDATE:
            - Specifies that all other cached copies of the mapping be invalidated.
            - Any future access to any mappings of this file will reflect the newly synchronized on-disk contents.
        - MS_SYNC:
            - Specifies that synchronization should occur synchronously.
            - The msync( ) call will not return until all pages are written back to disk.
    - return: On success, returns 0. On failure, the call returns -1, and sets errno appropriately        
*/


int main (int argc, char *argv[]) {
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
            
    { // mmap() and munmap()

        struct stat sb;
        off_t len;
        char *p;
        int fd;
        if (argc < 2) {
            fprintf (stderr, "usage: %s <file>\n", argv[0]);
            return 1;
        }
        fd = open (argv[1], O_RDONLY);
        if (fd == -1) {
            perror ("open");
            return 1;
        }
        if (fstat (fd, &sb) == -1) {    // fstat( ) returns information about a given file
            perror ("fstat");
            return 1;
        }
        if (!S_ISREG (sb.st_mode)) {    // to check for regular file
            fprintf (stderr, "%s is not a file\n", argv[1]);
            return 1;
        }
        p = mmap (0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
        if (p == MAP_FAILED) {
            perror ("mmap");
            return 1;
        }
        if (close (fd) == -1) {
            perror ("close");
            return 1;
        }
        for (len = 0; len < sb.st_size; len++)
            putchar (p[len]);
        if (munmap (p, sb.st_size) == -1) {
            perror ("munmap");
            return 1;
        }
    }


    printf ("\n");
    return 0;
}



