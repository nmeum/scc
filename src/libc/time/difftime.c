#include <time.h>

#undef difftime

double
difftime(time_t t1, time_t t2)
{
	return t2 <= t1 ? (double) (t1 - t2) : -(double) (t2 - t1);
}
