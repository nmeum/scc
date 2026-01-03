#!/bin/sh

trap 'rm -f $tmp1 t? t' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

scc make -f- <<'EOF' > $tmp1 2>&1
all: t1 t2

t1 t2: t
t1 t2 t:
	touch $@
EOF

diff $tmp1 - <<EOF
touch t
touch t1
touch t2
EOF
