#ifndef BUILDIN_IN_H
#define BUILDIN_IN_H

char *buildInCommands[] = {"ls", "cd", "help", "exit"};

int buildInLength();
int cd(char **args);
int ls(char **args);
int help();
int programExit();

void die(const char*);
void clear();

int (*buildInFunc[]) (char **) = {
  &ls,
  &cd,
  &help,
  &programExit,
};


/**
 * <Summary>
 *
 * @return <Summary>
 */
int buildInLength(){
	return (int)(sizeof(buildInCommands) / sizeof(char*));
}

/**
 * <Summary>
 *
 * @param args <Summary>
 * @return <Summary>
 */
int ls(char **args){
    DIR *dir;
    struct dirent *ent;
    char* dir_path;

    // If no argument is passed, list the current directory
    if(args[1] == NULL)
        dir_path = getcwd(NULL, 0);
    else
        dir_path = args[1];
    
    dir = opendir(dir_path);

    if(dir == NULL) die("Command error [ls]");

    int counter = 0;
    while((ent = readdir(dir)) != NULL){
        if(counter < 5)
            printf("%s | ", ent->d_name);
        else{
            printf("\n%s | ", ent->d_name);
            counter = 0;
        }
        counter += 1;
    }

    printf("\n");
    closedir(dir);
    return 1;
}

/**
 * <Summary>
 *
 * @param args <Summary>
 * @return <Summary>
 */
int cd(char **args){

    if(chdir(args[1]) != 0) die("Command error [cd]");

    return 1;
}


/**
 * <Summary>
 *
 * @param args <Summary>
 * @return <Summary>
 */
int help(){
    printf("\n == C-Shell (UNIX) == \n");
    printf("\n- Usage: Type program name and arguments.\n");
    printf("- Followings are build in commands:\n");

    for(int i=0; i<buildInLength(); i++)
        printf("%d) %s\n", i+1, buildInCommands[i]);

   return 1;
}

/**
 * <Summary>
 *
 * @param args <Summary>
 * @return <Summary>
 */
int programExit(){
    return 0;
}

/**
 * Prints an error message and exits the program.
 *
 * @param message The error message to print.
 */
void die(const char* message){
    perror(message);
    exit(1);
}

/**
 * Prints an error message and exits the program.
 *
 * @param message The error message to print.
 */
void clear(){
    system("clear");
}

#endif
