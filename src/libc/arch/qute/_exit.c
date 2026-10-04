extern void quebex_exit(long status);

void
_exit(int status)
{
	quebex_exit(status);
}
