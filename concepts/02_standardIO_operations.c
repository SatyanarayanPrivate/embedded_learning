#include <stdio.h>
#include <errno.h>

/*
Buffered IO:
    - Programs that have to issue many small I/O requests to regular files often perform user-buffered I/O . 
    - This refers to buffering done in user space, either manually by the application, or transparently in a library, not to buffering done by the kernel.
    - As kernel and hardware speak in terms of blocks. So, using the block size or a value that fits neatly inside of a block guarantees block-aligned I/O requests, and prevents extraneous work inside the kernel. Which will result improve in performance.
    - 
*/


// Standard IO: Portablity and user buffering solution, Operates on file pointers not on file descriptors.
    
/* Opening files
FILE * fopen (const char *path, const char *mode);
    - opens the file path according to the given modes.

mode: 
    - r: 
        - Open the file for reading. 
        - The stream is positioned at the start of the file.
    - w: 
        - Open the file for writing. 
        - If the file exists, it is truncated to zero length. If the file does not exist, it is created. 
        - The stream is positioned at the start of the file.
    - a:
        - Open the file for writing in append mode. 
        - The file is created if it does not exist.
        - The stream is positioned at the end of the file. All writes will append to the file.
    - b: Open the file in binary mode, but this value is always ignored on Linux. Some operating systems treat text and binary files differently.
    - r+: 
        - Open the file for both reading and writing. 
        - The stream is positioned at the start of the file.
    - w+: 
        - Open the file for both reading and writing. 
        - If the file exists, it is truncated to zero length. If the file does not exist, it is created. 
        - The stream is positioned at the start of the file. 
    - a+:
        - Open the file for both reading and writing in append mode.
        - The file is created if it does not exist.
        - The stream is positioned at the end of the file. All writes will append to the file.
return:
    - Upon success, fopen( ) returns a valid FILE pointer. 
    - On failure, it returns NULL, and sets errno appropriately.
*/


/* Opening a Stream via File Descriptor

FILE *fopen(int fd, const char *mode);
    - The stream is positioned at the file position associated with the file descriptor.
    - Once a file descriptor is converted to a stream, I/O should no longer be directly performed on the file descriptor. It is, however, legal to do so.
    - Note that the file descriptor is not duplicated, but is merely associated with a new stream. Closing the stream will close the file descriptor as well.
return:
    - On success, fdopen( ) returns a valid file pointer; on failure, it returns NULL.
 
Exmaple:
    FILE *stream;
    int fd;
    fd = open ("/home/kidd/map.txt", O_RDONLY);
    if (fd == &#8722;1)
        // error 
    stream = fdopen (fd, "r");
    if (!stream)
        // error 
*/


/* Closing Streams
int fclose(FILE *stream);
    - Any buffered and not-yet-written data is first flushed. 
return:
    - On success, fclose( ) returns 0. On failure, it returns EOF and sets errno appropriately.
*/

/* Closing All Streams
int fcloseall (void);
    - The fcloseall( ) function closes all streams associated with the current process, including standard in, standard out, and standard error
*/

/* Read Operations
Reading a Character at a Time
int fgetc (FILE *stream);
    - This function reads the next character from stream and returns it as an unsigned char cast to an int. 
    - The casting is done to have a sufficient range for notification of end-of-file or error:EOF is returned in such conditions.
return:
    - The return value of fgetc( ) must be stored in an int. Storing it in a char is a common but dangerous mistake.

Putting the character back
int ungetc (int c, FILE *stream);
return:
     - On success, c is returned; on failure, EOF is returned. A subsequent read on stream will return c

Reading an Entire linetsint fgers
char *fgets(char *str, int size, FILE *stream);
    - This function reads up to one less than size bytes from stream, and stores the results in str.
    - A null character (\0) is stored in the buffer after the bytes read in. 
    - Reading stops after an EOF or a newline character is reached. If a newline is read, the \n is stored in str.
return:
    - On success, str is returned; on failure, NULL is returned.

Reading Binary data
ssize_t fread(char *str, ssize_t size, ssize_t nr, FILE *stream);
    - A call to fread( ) will read up to nr elements of data, each of size bytes, from stream into the buffer pointed at by buf.
    - The file pointer is advanced by the number of bytes read.
return:
    - The number of elements read (not the number of bytes read!) is returned. 
    - The function indicates failure or EOF via a return value less than nr, Unfortunately, it is impossible to know which of the two conditions occurred without using ferror( ) and feof( ).
*/

/*  Write Operations
Writing single character
int fputc (int c, FILE *stream);
    - The fputc( ) function writes the byte specified by c (cast to an unsigned char) to the stream pointed at by stream. 
return: 
    - Upon successful completion, the function returns c. Otherwise, it returns EOF, and errno is set appropriately.

Writing a String of Characters
int fputs(const char *str, FILE *file);
    - A call to fputs( ) writes all of the null-delimited string pointed at by str to the stream pointed at by stream. 
return:
    - On success, fputs( ) returns a nonnegative number. On failure, it returns EOF.

Writing Binary Data
ssize_t fwrite(const char *str, ssize_t size, ssize_t nr, FILE *stream);
    - A call to fwrite( ) will write to stream up to nr elements, each size bytes in length, from the data pointed at by buf.
    - The file pointer will be advanced by the total number of bytes written.
return:
    - The number of elements (not the number of bytes!) successfully written will be returned. 
    - A return value less than nr denotes error.
*/

/* Seeking operations

inr fseek (FILE *stream, long offset, int whence);
    - If whence is set to 
        - SEEK_SET: the file position is set to offset.
        - SEEK_CUR: the file position is set to the current position plus offset.
        - SEEK_END: the file position is set to the end of the file plus offset.
return:
    - On successful completion, fseek( ) returns 0, clears the EOF indicator,
    - On error, it returns -1, and errno is set appropriately. 
    - The most common errors are invalid stream (EBADF) and invalid whence argument (EINVAL).

Obtaining the Current Stream Position
long ftell (FILE *stream);
return:
    - returns the current stream position of stream
    - On error, it returns -1 and errno is set appropriately.
*/

/* Flushing a Stream
int fflush (FILE *stream);
    - On invocation, any unwritten data in the stream pointed to by stream is flushed to the kernel.
    - If stream is NULL, all open input streams in the process are flushed.

return:
    - On success, fflush() returns 0. On failure, it returns EOF, and errno is set appropriately. 
*/

/* Errors and End-of-File
int ferror (FILE *stream);
    - The error indicator is set by other standard I/O (such as fread()) interfaces in response to an error condition.
return:
    - The function returns a nonzero value if the indicator is set, and 0 otherwise.

int feof (FILE *stream);
    - The EOF indicator is set by other standard I/O interfaces when the end of a file is reached.
return:
    - This function returns a nonzero value if the indicator is set, and 0 otherwise.

void clearerr (FILE *stream);
    - The clearerr( ) function clears the error and the EOF indicators for stream.
*/

/* Obtaining the Associated File Descriptor
int fileno(FILE *stream);
*/

/* Controlling the Buffering
Unbuffered: _IONBF
    - No user buffering is performed. Data is submitted directly to the kernel.
    - Standard error, by default, is unbuffered.
Line-buffered: _IOLBF
    - Buffering is performed on a per-line basis. With each newline character, the buffer is submitted to the kernel.
    - Line buffering makes sense for streams being output to the screen.
    -  Consequently, this is the default buffering used for terminals (standard out is line-buffered by default).
Block-buffered(Full-buffering): _IOFBF
    - Buffering is performed on a per-block basis. it is ideal for files.

int setvbuf (FILE *stream, char *buf, int mode, size_t size);
    - The setvbuf( ) function sets the buffering type of stream to one of mode (_IONBF, _IOLBF or _IOFBF).
    - Except with _IONBF, in which case buf and size are ignored, buf may point to a buffer of size bytes that standard I/O will use as the buffer for the given stream. 
    - If buf is NULL, a buffer is allocated automatically by glibc.
    - The supplied buffer, if any, must exist when the stream is closed.
    - The setvbuf( ) function must be called after opening the stream, but before any other operations have been performed on it. 
return:
    - It returns 0 on success, and a nonzero value otherwise.
*/

/* Manual File Locking
void flockfile (FILE *stream);
    - The function flockfile( ) waits until stream is no longer locked, and then acquires the lock, bumps the lock count, becomes the owning thread of the stream, and returns.

void funlockfile (FILE *stream);
    - The function funlockfile( ) decrements the lock count associated with stream.
    - If the lock count reaches zero, the current thread relinquishes ownership of the stream. Another thread is now able to acquire the lock.
    - These calls can nest. That is, a single thread can issue multiple flockfile( ) calls, and the stream will not unlock until the process issues a corresponding number of funlockfile() calls.

int ftrylockfile (FILE *stream);
    - The ftrylockfile( ) function is a nonblocking version of flockfile( ):
return:
    - If stream is currently locked, ftrylockfile( ) does nothing, and immediately returns a nonzero value.
    - If stream is not currently locked, it acquires the lock, bumps the lock count, becomes the owning thread of stream, and returns 0.

*/

ine main () {

    FILE *filePtr = NULL;
    int ret = 0x00; 
    
    {

        filePtr = fopen ("02Test1", "w");  // creates file with 664 permission
        if (filePtr == NULL) {
            printf ("\nFailed to open file with error: %d", errno);
            return -1;
        }
        
        ret = fputc ('a', filePtr); // will fail as file is opened in write only mode
        if (ret == EOF) {
            printf ("\nFailed to write char");  
            goto exit1;
        }
        printf ("\nwritten char: %c", (char) ret);
        
        ret = fgetc(filePtr); 
        if (ret == EOF) {
            printf ("\nFailed to read char");
            goto exit1;
        }
        printf ("\nRead char: %c", (char) ret);

exit1:        
        fclose (filePtr);
    }   
    
    {    
        filePtr = fopen ("02Test1", "a+");  // creates file with 664 permission
        if (filePtr == NULL) {
            printf ("\nFailed to open file with error: %d", errno);
            return -1;
        }
        
        ret = fgetc(filePtr); 
        if (ret == EOF) {
            printf ("\nFailed to read char");
            goto exit2;
        }
        printf ("\nRead char: %c", (char) ret);

        ret = fputc ('b', filePtr);
        if (ret == EOF) {
            printf ("\nFailed to write char");
            goto exit2;
        }
        printf ("\nwritten char: %c", (char) ret);
        
        ret = fseek (filePtr, -1, SEEK_CUR);    
        if (ret == -1) {
            printf ("\nFailed in seek with error: %d", errno);
            goto exit2;
        }
    
        ret = fgetc(filePtr); 
        if (ret == EOF) {
            printf ("\nFailed to read char");
            goto exit2;
        }
       
        {
            ssize_t retVal = 0x00;
            char buf[] = {"Hello world and bye bye"};
            ssize_t number = sizeof (buf)/2;
            retVal = fwrite (buf, 2, number, filePtr);
            printf ("\nwritten retVal: %d number: %d", (int) retVal, (int) number);

            if (retVal < number) {
                printf ("\nFailed to write Binary data");
                goto exit2;                
            }
        }
         
exit2:
        fclose (filePtr);
    }

    printf ("\n");
    return 0;
}
