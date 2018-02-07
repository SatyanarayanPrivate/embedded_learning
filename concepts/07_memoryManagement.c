

/* Dynamic memory

void * malloc(size_t size);
    - allocates size number of bytes, content of allocated data are garbage data.
    - return: on error return NULL, on sucess valid address.

# allocating arrays
void *calloc(size_t nr, size_t size);
    - calloc( ) zeros all bytes in the returned chunk of memory.
    - returns a pointer to a block of memory suitable for holding an array of nr elements, each of size bytes.

# Resizing Allocations
void * realloc(void *ptr, size_t size);
    - resizes the region of memory pointed at by ptr to a new size of size bytes. It returns a pointer to the newly sized memory.
    - If size is 0, the effect is the same as an invocation of free( ) on ptr.
    - If ptr is NULL, the result of the operation is the same as a fresh malloc().
    
# free memory
void free (void *ptr);

*/


/*

void * memset (void *s, int c, size_t n);
    - sets the n bytes starting at s to the byte c and returns s.

int memcmp (const void *s1, const void *s2, size_t n);
    - An invocation compares the first n bytes of s1 to s2, and returns 0 if the blocks of memory are equivalent
    - a value less than zero if s1 is less than s2, and a value greater than zero if s1 is greater than s2.
    
void * memmove (void *dst, const void *src, size_t n);

void * memcpy (void *dst, const void *src, size_t n);
void * memccpy (void *dst, const void *src, int c, size_t n);
    - The memccpy( ) function behaves the same as memcpy( ), except that it stops copying if the function finds the byte c within the first n bytes of src.
    - The call returns a pointer to the next byte in dst after c, or NULL if c was not fo   und.
void * mempcpy (void *dst, const void *src, size_t n);
    - The mempcpy( ) function performs the same as memcpy( ), except that it returns a pointer to the next byte after the last byte copied.

void * memchr (const void *s, int c, size_t n);
    - The memchr( ) function scans the n bytes of memory pointed at by s for the character c,

int mlock (const void *addr, size_t len);
    - A call to mlock( ) locks the virtual memory starting at addr, and extending for len bytes into physical memory.
    - On success, the call returns 0; on failure, the call returns -1, and sets errno as appropriate.    
int munlock (const void *addr, size_t len);
*/

