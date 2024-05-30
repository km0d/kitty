#ifndef HIDE_H
#define HIDE_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool vm_bios(void) __attribute__((visibility("hidden")));
bool vm_sys(void) __attribute__((visibility("hidden")));
bool hypervisor_flag(void) __attribute__((visibility("hidden")));

#endif
