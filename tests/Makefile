SHELL := /bin/sh

### Unit-level Rules ###

UNITS := $(patsubst %.c,%,$(shell cd .. && echo *.c))
UNIT_TESTS :=
UNIT_CLEANS :=

define defrules
.PHONY: $1
$1:
	$(and $(wildcard $1/Makefile),cd $1 && $(MAKE))

.PHONY: test-$1
test-$1: $1
	cd $1 && ./run-tests
	@echo '==> SUCCESS'
UNIT_TESTS += test-$1

.PHONY: clean-$1
clean-$1:
	$(and $(wildcard $1/Makefile),cd $1 && $(MAKE) clean)
UNIT_CLEANS += clean-$1
endef

$(foreach unit,$(UNITS),$(eval $(call defrules,$(unit))))

### Top-level Rules ###

.PHONY: all
all: $(UNITS)
	@echo $(UNITS)

.PHONY: test
test: $(UNIT_TESTS)
	@echo $(UNIT_TESTS)

.PHONY: clean
clean: $(UNIT_CLEANS)
	@echo $(UNIT_CLEANS)
