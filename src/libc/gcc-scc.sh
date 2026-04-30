#!/bin/sh

set -e

while getopts gr:O:a:s:o:c o
do
	case $o in
	g)
		g=-g
		;;
	O)
		opti=-O1
		;;
	r)
		root=$OPTARG
		;;
	a)
		abi=$OPTARG
		;;
	s)
		sys=$OPTARG
		;;
	o)
		out=$OPTARG
		;;
	c)
		onlycc=1
		;;
	*)
		echo >&2 "usage: gcc-scc [-o outfile] [-c] [-r root] [-a abi] [-s sys] file"
		exit 1
		;;
	esac
done
shift $((OPTIND-1))

sys=${sys:-`uname | tr 'A-Z' 'a-z'`}
abi=${abi:-amd64}
out=${out:-a.out}
root=${root:-${SCCPREFIX:-`dirname $0`/..}}
inc=$root/include/scc
arch_inc=$inc/bits/$abi
sys_inc=$inc/bits/$sys
sys_arch_inc=$inc/bits/$sys/$abi
lib=$root/lib/scc/${abi}-${sys}
crt=$root/lib/scc/${abi}-${sys}/crt.o
obj=${1%.c}.o
cc=${CROSS_COMPILE}cc
ld=${CROSS_COMPILE}ld

case `uname` in
OpenBSD)
	nopie=-no-pie
	;;
esac

includes="-nostdinc -I$inc -I$arch_inc -I$sys_inc -I$sys_arch_inc"
cflags="$opti -std=c99 -w -fno-pie -fno-stack-protector -ffreestanding -static"
ldflags="-z nodefaultlib -static -L$lib"

if test ${onlycc:-0} -eq 1
then
	$cc $cflags $includes -c "$@"
else
	for i
	do
		case $i in
		*.c)
			$cc $g $cflags $includes -c "$i"
			;;
		esac
	done

	# convert *.c args to *.o while correctly maintaing IFS chars
	for i
	do
		shift
		case $i in
		*.c)
			set -- "$@" "${i%c}o"
			;;
		*)
			set -- "$@" "$i"
			;;
		esac
	done

	$ld $g $ldflags $nopie $crt "$@" -lc -lcrt -o "$out"
fi
