/* DESCRIPTION
 *
 *	Simple program (essentially a toy implementation of `cat') that
 *	explicitly invokes either the 2- or 3-argument version of the `open'
 *	syscall:
 *
 *	    int open(const char *pathname, int flags);
 *	    int open(const char *pathname, int flags, mode_t mode);
 *
 * SEE ALSO:
 *	open(2), syscall(2)
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sysexits.h>

#include <errno.h>
extern void error(int status, int errnum, const char *format, ...);

int main(int argc, char *argv[])
{
	char *filename;
	int fd;
	char buf[BUFSIZ];
	ssize_t n;
	int arity = 2;

	if (argc > 1 && strcmp(argv[1], "-3") == 0) {
		arity = 3;
		++argv;
		--argc;
	}

	if (argc > 1) {
		filename = argv[argc - 1];
		if (arity == 2)
			fd = open(filename, O_RDONLY);
		else /* arity == 3 */
			fd = open(filename, O_RDONLY, 0);

		if (fd == -1)
			error(EX_NOINPUT, errno, filename);
	} else {
		filename = "/dev/stdin";
		fd = 0;
	}

	while ((n = read(fd, &buf, BUFSIZ)) > 0)
		if (write(1, buf, n) == -1)
			error(EX_OSERR, errno, "/dev/stdout");

	if (n == -1)
		error(EX_IOERR, errno, filename);

	if (close(fd) == -1)
		error(EX_OSERR, errno, filename);

	return 0;
}
