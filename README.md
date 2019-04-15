# libtrace

A minimal library used to trace other library functions and system calls.
Its primary target is EROS product generation.


## Building

Running `make` with no arguments will result in the following steps being
performed by the GNU compiler toolchain:

1. Compile all `.c` source files in the project root into position-independent
   assembly code (PIC).
2. Immediately assemble the in-memory PIC into object code, writing the output
   to disk as `.o` files.
3. Link the object files into a single dynamic library (shared object) and
   write the output to disk as `libtrace.so`.

If you wish to compile only a subset of source files into the library, you can
assign a space-delimited list of `.c` files to a variable named `SRC` and then
pass that variable to `make`.

To give the library a name other than `trace`, assign the alternate name to
`LIBNAME` and pass it onto `make`.  You will need to pass this `LIBNAME` to
**all** subsequent `make` invocations, as well, including those used for
installation, testing, and clean up.  Failure to do so will result in errors.


## Testing

After building the library, a good idea would be to run tests on said library.
With a default build, `make test` will do just that.

If you passed a modified `SRC` to the build step, you will need to pass that
same `SRC` to `make test` so that only the appropriate tests are run.  For
information on how tests are organized, see the <a href="DEVEL.md#tests">"Adding tests"</a>
section of `DEVEL.md`.


## Installing

A simple `make install` will install your library to `/usr/local/lib`.  To
install to a different location, pass one of the two variables to `make`:

- `PREFIX`: overrides `/usr/local`
- `LIBDIR`: overrides the entire path

The user and group ownership of the library will be set to the EUID and EGID of
the `make install` process.  Either assume the correct user and default group
before installation, or utilize `sudo [-u USER] [-g GROUP]` to get this right.

If you wish to test the installed version of the library, there is an
`installcheck` Makefile target for that.  Like the `test` target, you must pass
`SRC` to `make` if you modified it during the build.


## Running

To use the library, simply run a command with the library's path included in
the `LD_PRELOAD` environment variable.  For example:

    LD_PRELOAD=/usr/local/lib/libtrace.so espa-submit

Because this library is used for tracing other library calls and system calls,
it is probably best to perform one-shot modification of `LD_PRELOAD` rather
than exporting it to all child processes.


## Cleaning Up

There are two Makefile targets used for cleaning up files:

- `clean`: removes build and test artifacts
- `uninstall`: removes the library from the installation location

If you overrode either `PREFIX` or `LIBDIR` during installation, you will need
to pass the overridden variable to `make uninstall` for that particular
operation to succeed.
