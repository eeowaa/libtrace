#ifndef LIBDIR
# define LIBDIR /usr/local/lib
#endif
#ifndef LIBNAME
# define LIBNAME trace
#endif

#define STRINGIFY(x) #x
#define STRING(x) STRINGIFY(x)

#define LD_PRELOAD "LD_PRELOAD=" STRING(LIBDIR) "/lib" STRING(LIBNAME) ".so"

#include <stdio.h>
#include <sys/syscall.h>

extern int syscall(int, ...);

int execve(const char *pathname, char *const argv[], char *const envp[])
{
	char **head = (char **)envp;
	while (head && *head++)
		fprintf(stderr, "%s\n", *head);

	/* Make the actual system call (jumps straight to assembly). */
	return syscall(__NR_execve, pathname, argv, envp);
}
