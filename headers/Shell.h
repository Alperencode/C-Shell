#ifndef SHELL_H
#define SHELL_H

#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "BuildIn_functions.h"

void loop();
char* readLine();
char** splitLine(char*, const char*);
int launch(char**);
int execute(char**);

#endif
