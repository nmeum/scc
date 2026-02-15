#!/bin/sh

trap 'rm -f $tmp' EXIT
trap 'exit $?' HUP INT TERM

tmp=$$.tmp

$EXEC scc make -f test2.mk MOREOBJS='a.o b.o' <<'EOF' > $tmp

diff -u - $tmp <<EOF
MAKEFLAGS=MOREOBJS=a.o b.o
MOREOBJS=a.o b.o
OBJS= a.o b.o main.o
MAKEFLAGS=MOREOBJS='a.o b.o'
MAKEFLAGS=MOREOBJS=a.o b.o
MOREOBJS=a.o b.o
OBJS= a.o b.o main.o
EOF
