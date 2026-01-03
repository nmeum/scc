#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

($EXEC scc make -f- -- -42 <<'EOF'
-42:
	@echo 'hyphen-target'
EOF

$EXEC scc make -f- -- MYVAR=-42 <<'EOF'
all:
	@@echo MYVAR is $(MYVAR)
EOF

$EXEC scc make -f- -- MYVAR=myval -42 <<'EOF'
-42:
	@echo MYVAR is $(MYVAR)
EOF
) > $tmp1

diff $tmp1 - <<EOF
hyphen-target
MYVAR is -42
MYVAR is myval
EOF
