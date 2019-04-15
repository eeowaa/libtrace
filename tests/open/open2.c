/* DESCRIPTION
 *
 * 	Simple program (essentially a toy implementation of `cat') that
 * 	explicitly invokes the 2-argument version of the `open' syscall.
 *
 *	int open(const char *pathname, int flags); <-- THIS ONE
 *	int open(const char *pathname, int flags, mode_t mode);
 *
 * SEE ALSO:
 * 	open(2), syscall(2)
 */

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

	if (argc > 1) {
		filename = argv[argc - 1];
		if ((fd = open(filename, O_RDONLY)) == -1)
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
