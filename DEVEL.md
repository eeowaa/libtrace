# Extending `libtrace`

## Adding sources

- Source files should have a `.c` extension and live in the project root.

- The root `Makefile` typically does not need to be modified, but if the source
  file requires special build flags not included in the implicit compilation
  rule, an explicit rule should be created for generating the `.o` file.

- Each source file should have a corresponding set of unit tests.  See the
  ["Adding tests"](#tests) section for organizational conventions.


## Adding tests<a name="tests"/>

- Each `.c` source file in the project root should have a corresponding
  extension-less directory in `tests/`.  For example, `open.c` has a
  corresponding `tests/open` directory.

- Each subdirectory of `tests` should contain an executable `run-tests` script 
  that tests library code compiled from the corresponding source file.  For
  example, `tests/open/run-tests` should test the code in `libtrace.so`
  compiled from `open.c` (and subsequently linked from `open.o`).

- Any additional files needed for testing a specific compilation unit should
  go in the corresponding subdirectory of `tests/`.

- Compilation units that have prerequisite steps to testing should perform
  these steps in the default rule of a `Makefile`.  Any files generated during
  a prerequisite step should be removed by a `clean` rule.


# TODO items

- `[X]` Fix and clean up scaffolding for testing
- `[ ]` Support for 3-arg `open` syscall
- `[ ]` Preprocessor macro for path of interest passed to `open` syscall
- `[ ]` File-based logging of `open` syscalls
- `[-]` Finish documentation