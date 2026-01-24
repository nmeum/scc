#!/bin/sh

trap 'rm -f f.? $tmp1 $tmp2 f.?' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$
tmp2=tmp2.$$

cat >$tmp1 <<'EOF'
f.o: f.h

all: f.o
EOF

(touch f.c f.h
$EXEC scc make -f $tmp1
touch f.c
scc make -f $tmp1) > $tmp2

diff $tmp2 - <<EOF
c99 -O -c f.c
EOF
