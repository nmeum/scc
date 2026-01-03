#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

scc make -f- <<'EOF' > $tmp1 2>&1
VAR =\
        all\
        f1\
        f2\

OBJS = f.$O

O = e

$(VAR) all : $(OBJS)
	@echo done

f.$O:
	@echo yeah!
EOF

diff $tmp1 - <<EOF
yeah!
done
EOF
