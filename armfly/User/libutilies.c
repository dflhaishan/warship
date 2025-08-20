#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#if 0
pid_t _getpid_r(void) { return 1; }

int _kill_r(pid_t pid, int sig) { errno = ENOSYS; return -1; }
 
__attribute__((weak)) int _isatty(int fd)
{
    return 1;
}
 
__attribute__((weak)) int _close(int fd)
{
    return -1;
}
 
__attribute__((weak)) int _lseek(int fd, int ptr, int dir)
{
    return -1;
}
 
__attribute__((weak)) int _fstat(int fd, struct stat *st)
{
    return 0;
}

 
__attribute__((weak)) int _read(int file, char *ptr, int len)
{
    return 0;
}
 
__attribute__((weak)) int _write(int file, char *ptr, int len)
{
    return 0;
}
#endif