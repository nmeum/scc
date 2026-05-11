/*
PATTERN:
0041-iconst.c:16: error: 'POS2' undeclared
0041-iconst.c:16: error: array index in initializer not of integer type
.
*/

enum {
	POS0,
	POS1,
};

int a[] = {
	[POS0] = 1,
	[POS1] = 2,
	[POS2] = 3,
};
