#ifndef PIPE_FUNC_H
#define PIPE_FUNC_H

// Defining constants
#define INPUT_MAX 255
#define CMD_MAX 10
#define MAX_ARGUMENTS 20

// Adding libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>

extern char input;
extern int debug;

void init();
void printWelcome();
void printPromt();
void getCommands();
void parseCommands();
void createPipes();

#endif
