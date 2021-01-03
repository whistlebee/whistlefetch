#include <stdio.h>
#include <sys/sysctl.h>
#include <string.h>

#if defined(__APPLE__) && defined(__MACH__)
void os_getversion(char *osproduct, size_t size) {
  int count = sprintf(osproduct, "macOS ");
  char* version_ptr = osproduct + count;
  if (sysctlbyname("kern.osproductversion", version_ptr, &size, NULL, 0) < 0) {
    strcpy(version_ptr, "error");
  }
}

void os_getcpuinfo(char *cpuinfo, size_t size) {
  sysctlbyname("machdep.cpu.brand_string", cpuinfo, &size, NULL, 0);
}
#endif

