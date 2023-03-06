#ifndef BUILDIN_IN_H
#define BUILDIN_IN_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char *buildInCommands[];
extern int (*buildInFunc[]) (char **);

int buildInLength();
int cd(char **args);
int ls(char **args);
int help();
int programExit();

void die(const char*);
void clear();


#endif
