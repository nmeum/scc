#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

(scc make -f - error hello 2>&1 |
sed 's/sh:.*: *no-/sh: no-/' > $tmp1) <<EOF
.IGNORE:

error:
	no-valid-program
EOF

diff $tmp1 - <<EOF
no-valid-program
sh: no-valid-program: not found
make: error: don't know how to make hello
EOF
