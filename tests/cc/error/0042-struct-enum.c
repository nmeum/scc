/*
PATTERN:
0042-struct-enum.c:9: error: unexpected 'const'
0042-struct-enum.c:10: error: unexpected 'const'
0042-struct-enum.c:11: error: unexpected 'const'
.
*/

struct const tag1 { int v; };
union const tag2 { int v; };
enum const tag3 { VALUE };
