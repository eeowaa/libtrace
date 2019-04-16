#include <fcntl.h> /* __OPEN_NEEDS_MODE, O_LARGEFILE */
#include <bits/typesizes.h> /* __OFF_T_MATCHES_OFF64_T */

#ifdef __OFF_T_MATCHES_OFF64_T
# define EXTRA_OPEN_FLAGS 0
#else
# define EXTRA_OPEN_FLAGS O_LARGEFILE
#endif

#include <stdarg.h>
#include <stdio.h>
#include <sys/syscall.h>

extern int syscall(int, ...);

int open(const char *filename, int flags, ...)
{
	int mode = 0;
	va_list arg;

	/* If O_CREAT or O_TMPFILE is in OFLAG, we have a third argument: mode. */
	if (__OPEN_NEEDS_MODE(flags)) {
		va_start(arg, flags);
		mode = va_arg(arg, int);
		va_end(arg);
	}

	/* This is where we do tracing. */
	fprintf(stderr, "[TRACE] %s\n", filename);

	/* Make the actual system call (jumps straight to assembly). */
	return syscall(__NR_open, filename, flags | EXTRA_OPEN_FLAGS, mode);
}
