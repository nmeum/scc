#!/bin/sh

trap 'rm -f f.c f.o f' EXIT
trap 'exit $?' HUP INT TERM

echo hello > f.c

$EXEC scc make -sf- <<'EOF'
.c:
	echo hello > $@

all: f
EOF

diff f.c f
