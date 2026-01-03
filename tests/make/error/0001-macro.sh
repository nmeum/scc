#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' INT TERM HUP

tmp1=tmp1.$$

$EXEC scc make -f - <<'EOF' > $tmp1 2>&1
FLAGS=Hello $(EFLAGS)
all: $(DIRS)
	@echo Hello World

$(DIRS): FORCE
	@echo Bye

FORCE:
EOF

diff $tmp1  - <<EOF
make: error: <stdin>:5: missing target
EOF
