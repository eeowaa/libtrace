#include <stdio.h>
#include <sys/syscall.h>

extern int syscall(int, ...);

int open(const char *pathname, int flags)
{
	fputs("<intercepted>\n", stderr);
	return syscall(__NR_open, pathname, flags);
}
