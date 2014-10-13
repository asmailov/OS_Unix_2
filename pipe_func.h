#ifndef PIPE_FUNC_H
#define PIPE_FUNC_H

// Defining constants
#define INPUT_MAX 255
#define PIPE_MAX 5

// Adding libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>

char *userName;
char hostName[HOST_NAME_MAX];
char currDir[PATH_MAX];
char input;
char cmdBuffer[INPUT_MAX];

void init();
void printWelcome();
void printPromt();
void getCommands();

#endif
