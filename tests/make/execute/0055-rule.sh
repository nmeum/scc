#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

(set -e
 scc make -if- <<'EOF'
.POSIX:

all:
	@echo Hello World!;\
	false;\
	echo bye
EOF
echo fail) > $tmp1 2> /dev/null

diff $tmp1 - <<EOF
Hello World!
bye
fail
EOF
