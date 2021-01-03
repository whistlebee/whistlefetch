#ifndef WHISTLE_OS_H
#define WHISTLE_OS_H

#include <stdio.h>

void os_getversion(char *osproduct, size_t size);
void os_getcpuinfo(char* cpuinfo, size_t size);

#endif
