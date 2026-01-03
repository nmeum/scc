#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

scc make -f- <<EOF > $tmp1 2>&1
.DEFAULT: all
	@echo Hello World!
EOF

diff $tmp1 - <<'EOF'
make: error: <stdin>:3: DEFAULT rule with prerequisites
EOF
