#include <stdio.h>

/* Stat
 # include <sys/types.h>                                                                         *
 #include <sys/stat.h>
 #include <unistd.h>
 int stat (const char *path, struct stat *buf);
 int fstat (int fd, struct stat *buf);
 int lstat (const char *path, struct stat *buf);
    - stat( ) returns information about  the file denoted by the path, path.
    - fstat( ) returns information about the file represented by the file descriptor fd.
    - lstat( ) is identical to stat( ), except that in the case of a symbolic link, lstat( ) returns information about the link itself and not the target file.
    - return: 0 on success, -1 on error and set errno.
*/

/* Permission and ownership
int chmod (const char *path, mode_t mode);
int fchmod (int fd, mode_t mode);
    - return: 0 on success, -1 on error and set errno.

int chown (const char *path, uid_t owner, gid_t group);
int lchown (const char *path, uid_t owner, gid_t group);
int fchown (int fd, uid_t owner, gid_t group);
    - return: 0 on success, -1 on error and set errno.
*/

/* Directories
 char * getcwd (char *buf, size_t size);
    - current working directory as an absolute pathname into the buffer pointed at by buf, which is of length size bytes, and returns a pointer to buf.
    - return: On failure, the call returns NULL, and sets errno.

char * get_current_dir_name (void);

Change directory
int chdir (const char *path);
int fchdir (int fd);
    - On success, both calls return 0. On failure, both calls return -1 and sets errno.
    
int mkdir (const char *path, mode_t mode);    
    - return: 0 on success, -1 on error and set errno.

int rmdir (const char *path);    
    - return: 0 on success, -1 on error and set errno.

DIR * opendir (const char *name);    
int dirfd (DIR *dir);
    - Obtain the file descriptor behind a given directory stream.
    - return: on error return -1.

Reading from a directory stream
struct dirent * readdir (DIR *dir);
    - On failure, readdir( ) also returns NULL.
    - To differentiate between an error and having read all of the files, applications must set errno to 0 before each readdir( ) invocation, and then check both the return value and errno
int closedir (DIR *dir);

Example:
int find_file_in_dir (const char *path, const char *file)
{
    struct dirent *entry;
    int ret = 1;
    DIR *dir;
    dir = opendir (path);
    errno = 0;
    while ((entry = readdir (dir)) != NULL) {
        if (!strcmp(entry->d_name, file)) {
            ret = 0;
            break;
        }
    }
    if (errno && !entry)
        perror ("readdir");
    closedir (dir);
    return ret;
}
*/

/* Hard and symbolic Links
int link (const char *oldpath, const char *newpath);    
int symlink (const char *oldpath, const char *newpath);
    - return: 0 on success, -1 on error and set errno.
    
int unlink (const char *pathname);
    - A successful call to unlink( ) deletes pathname from the filesystem, and returns 0.
    - If that name was the last reference to the file, the file is deleted from the filesystem.
    - If, however, a process has the file open, the kernel will not delete the file from the filesystem until that process closes the file. Once no process has the file open, it is deleted.
    - If pathname refers to a symbolic link, the link, not the target, is destroyed.
    - return: 0 on success, -1 on error and set errno.
*/    
    
int main () {
    
    return 0;
}