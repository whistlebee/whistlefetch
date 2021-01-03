#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/sysctl.h>
#include <unistd.h>
#include <string.h>
#include "os.h"


int format_seconds(char *in, size_t size, unsigned long seconds) {
  char *formatter;
  unsigned long desc_chars;

  int int_days = seconds / (24 * 60 * 60);
  int int_hours = (seconds - (int_days * 24 * 60 * 60)) / (60 * 60);
  int int_minutes = (seconds % (60 * 60)) / 60;
  int rt;
  
  char *cur = in;
  unsigned long remaining = (unsigned long)size;

  if (int_days > 0) {
    if (int_days > 1) {
      formatter = "%d days ";
    } else {
      formatter = "%d day ";
    }
    desc_chars = strlen(formatter) - 1;
    if (remaining < 8 + desc_chars) {
      return -1;
    }
    rt = snprintf(cur, 8 + desc_chars, formatter, int_days);
    cur += rt;
    remaining -= rt;
  }
  
  if (int_hours > 0) {
    if (int_hours > 1) {
      formatter = "%d hours ";
    } else {
      formatter = "%d hour ";
    }
    desc_chars = strlen(formatter) - 1;
    if (remaining < 2 + desc_chars) {
      return -1;
    }
    rt = snprintf(cur, 2 + desc_chars, formatter, int_hours);
    cur += rt;
    remaining -= rt;
  }

  if (int_minutes > 0) {
    if (int_minutes > 1) {
      formatter = "%d minutes";
    } else {
      formatter = "%d minute";
    }
    desc_chars = strlen(formatter) - 1;
    if (remaining < 2 + desc_chars) {
      return -1;
    }
    rt = snprintf(cur, 2 + desc_chars, formatter, int_minutes);
    cur += rt;
    remaining -= rt;
  }

  return cur - in;
}


void get_login_nodename(char *login_nodename, struct utsname *ui, size_t size) {
  const char *login = getlogin();
  snprintf(login_nodename, size, "%s@%s", login, ui->nodename);
}


int main() {
  struct timespec si;
  struct utsname ui;
  char uptime[64];
  char osproduct[256];
  char cpuinfo[256];
  char login_nodename[128];
  char login_underline[128];
  
  uname(&ui);
  get_login_nodename(login_nodename, &ui, sizeof(login_nodename));
  for (unsigned long i = 0; i < strlen(login_nodename); ++i) {
    login_underline[i] = '-';
  }

  // for now don't worry about other platforms
  clock_gettime(CLOCK_UPTIME_RAW_APPROX, &si);
  format_seconds(uptime, 64, si.tv_sec);

  os_getversion(osproduct, sizeof(osproduct));
  os_getcpuinfo(cpuinfo, sizeof(cpuinfo));

  const char * out =
               "%s\n"
               "%s\n"
               "cpu   : %s\n"
               "os    : %s\n"
               "kernel: %s %s\n"
               "uptime: %s\n";
  printf(out, login_nodename, login_underline, cpuinfo, osproduct, ui.sysname, ui.release, uptime);
  return 0;
}
