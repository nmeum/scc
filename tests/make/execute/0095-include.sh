#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

scc make -f- MK=test.mk hello <<'EOF' > $tmp1 2>&1
MK = fail.mk
include $(MK)
EOF

diff $tmp1 - <<EOF
Hello World!
EOF
