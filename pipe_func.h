#ifndef PIPE_FUNC_H
#define PIPE_FUNC_H

// Adding libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>

char *userName;
char hostName[HOST_NAME_MAX];
char currDir[PATH_MAX];

void init();
void printWelcome();
void printPromt();

#endif
