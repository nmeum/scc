#!/bin/sh

cleanup()
{
	r=$?
	rm -f test.txt
	kill -KILL $pid 2>/dev/null
	if test $1 -ne 0
	then
		kill -KILL $$
	fi
	trap - EXIT
	exit $?
}

rm -f file.txt
trap 'cleanup 0' EXIT
trap 'cleanup 1' INT TERM HUP

$EXEC scc make -f - <<'EOF' &
file.txt:
	@touch $@
	@while : ; do sleep 1 ; done
EOF
pid=$!

sleep 10 && echo timeout >&2 && kill $$ 2>/dev/null &
timer=$!

while :
do
	if test -f file.txt
	then
		kill $pid
		wait $pid
		kill $timer
		break
	fi
done

! test -f file.txt
