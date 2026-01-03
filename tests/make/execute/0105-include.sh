#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f - <<'EOF' > $tmp1 2>&1
prefix = /usr/local
includedir = ${prefix}/include

all:
	@echo $(includedir)
EOF

diff $tmp1 - <<EOF
/usr/local/include
EOF
