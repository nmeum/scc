#!/bin/sh

trap 'rm -f f.? $tmp1 f.?' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

touch -d '1970-01-01 00:00:01' f.c
touch -d '1970-01-01 00:00:02' f.o
touch -d '1970-01-01 00:00:03' f.h
scc make -f - <<'EOF' > $tmp1 2>&1
f.o: f.h

all: f.o
EOF

diff $tmp1 - <<EOF
c99 -O -c f.c
EOF
