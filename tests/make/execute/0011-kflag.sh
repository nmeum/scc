#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

(set -e
 MAKEFLAGS=-k scc make  -f test.mk print-makeflags follow
 echo fail) 2>&1 |
sed 's/:.*: *no-/: no-/' > $tmp1

diff $tmp1 - <<EOF
-k
no-valid-program
sh: no-valid-program: not found
make: warning: target error: error 32512
Hello World!
make: warning: target follow not remade because of errors
EOF
