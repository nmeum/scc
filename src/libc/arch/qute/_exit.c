extern void qute_exit(long status);

void
_exit(int status)
{
	qute_exit(status);
}
