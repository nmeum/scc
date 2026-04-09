#!/bin/sh

#
# This job is very easy because app and kernel ABI are identical
# until the 4th parameter, so we only have to set the syscall
# number in rax

sed -n "
     s/[ 	]*#.*//
     /$1/p" syscall.lst |
while read num name nargs
do
cat <<EOF > $name.s
	.file	"$name.s"

	.globl	$name
$name:
	`case $nargs in 4|5|6)
		echo "movq       %rcx,%r10"
		;;
	esac`
	movq	\$$num,%rax
1:	syscall
	jb	2f
	retq

2:	movq	%rax,(errno)
	movq	\$-1,%rax
	retq

	.section .openbsd.syscalls, "a", @progbits
	.long 1b
	.long $num
EOF
done
