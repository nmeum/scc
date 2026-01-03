#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

SHELL=foo \
$EXEC scc make -f- <<'EOF' > $tmp1 2>&1
all:
	@echo $(SHELL)
EOF

diff $tmp1 - <<EOF
/bin/sh
EOF
