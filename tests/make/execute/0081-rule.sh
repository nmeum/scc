#!/bin/sh

trap 'rm -f f.c f.o f' EXIT
trap 'exit 1' HUP INT TERM

echo hello > f.c

scc make -sf- <<'EOF'
.c:
	echo hello > $@

all: f
EOF

diff f.c f
