#ifndef LIBDIR
# define LIBDIR /usr/local/lib
#endif
#ifndef LIBNAME
# define LIBNAME trace
#endif

#define STRINGIFY(x) #x
#define STRING(x) STRINGIFY(x)

#define LD_PRELOAD "LD_PRELOAD=" STRING(LIBDIR) "/lib" STRING(LIBNAME) ".so"

#include <alloca.h>
#include <string.h>
#include <sys/syscall.h>

extern int syscall(int, ...);

int execve(const char *pathname, char *const argv[], char *const envp[])
{
	char **ptr = (char **)envp;
	char **newenvp;
	int envc = 0;
	int i = 0;

	/* This is less expensive than sequential `alloca' calls */
	while (ptr && *ptr++)
		++envc;

	/* Save room for extra environment variable + NULL element */
	newenvp = alloca((envc + 2) * sizeof(char *));

	/* Insert at the beginning in case `envp' already has an `LD_PRELOAD'
	 * definition, as `getenv' uses the first definition in `environ' */
	newenvp[i++] = LD_PRELOAD;

	/* Copy the array */
	ptr = (char **)envp;
	while (i < envc + 1) {
		/* Hard to avoid sequential `alloca' here */
		newenvp[i] = alloca(strlen(*ptr));
		strcpy(newenvp[i++], *ptr++);
	}

	/* Terminate appropriately */
	newenvp[i] = (char *)NULL;

	/* Make the actual system call (jumps straight to assembly). */
	return syscall(__NR_execve, pathname, argv, newenvp);
}
