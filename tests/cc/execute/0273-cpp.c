#define a(x) #   x

static char *s1 = a(3);
static char *s2 = a( 3 );
static char *s3 = a( 3  2 );
static char *s4 = a ( 3
2);
static char *s5 = a("3 2  1");

static int
cmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
		++s1, ++s2;
	return *s1 == '\0' && *s2 == '\0';
}

int
main(void)
{
	if (!cmp(s1, "3"))
		return 1;
	if (!cmp(s2, "3"))
		return 2;
	if (!cmp(s3, "3 2"))
		return 3;
	if (!cmp(s4, "3 2"))
		return 4;
	if (!cmp(s5, "\"3 2  1\""))
		return 5;

	return 0;
}
