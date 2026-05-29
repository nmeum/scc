#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit $?' INT TERM HUP

tmp1=tmp1.$$

$EXEC scc make -f - <<'EOF' > $tmp1 2>&1
all: target1

target1: target2
	@echo target1

target2: target3
	@echo target2

target3: target1
	@echo target3
EOF

diff $tmp1  - <<EOF
make: warning: <stdin>:11: circular dependency target3 <- target1 dropped
target3
target2
target1
EOF
