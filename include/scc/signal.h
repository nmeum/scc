#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <sys/signal.h>

void (*signal(int, void (*)(int)))(int);
int raise(int);

#endif
