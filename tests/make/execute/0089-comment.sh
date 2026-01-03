#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'rm -f $tmp1' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f- <<'EOF' > $tmp1 2>&1
VAR = Hello World!  # This is a comment
all:
	@echo '$(VAR)'
EOF

diff $tmp1 - <<EOF
Hello World!  
EOF
