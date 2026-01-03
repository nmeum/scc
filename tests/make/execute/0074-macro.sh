#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

CC=dcc scc make -f- <<'EOF' > $tmp1 2>&1
all:
	@echo CC=$(CC)
EOF

diff $tmp1 - <<EOF
CC=dcc
EOF
