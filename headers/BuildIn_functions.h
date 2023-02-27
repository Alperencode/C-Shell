#ifndef BUILDIN_IN_H
#define BUILDIN_IN_H

char *buildInCommands[] = {"ls", "cd", "help", "exit"};

/**
 * <Summary>
 *
 * @param args <Summary>
 * @return <Summary>
 */
int ls(char **args){
    DIR *dir;
    struct dirent *ent;

    dir = opendir(path);

    if (dir == NULL) {
        die("Command error [ls]");
        return -1;
    }

    while ((ent = readdir(dir)) != NULL)
        printf("%s\n", ent->d_name);

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
int help(char **args){
    printf("\nC-Shell (UNIX)\n");
    printf("Type program name and arguments\n");
    printf("Followings are build in commands:\n");

    for(int i=0; i<buildInLength(); i++)
        printf("%s\n", buildInCommands[i]);

   return 1;
}

/**
 * <Summary>
 *
 * @param args <Summary>
 * @return <Summary>
 */
int exit(char **args){
    return 0;
}

#endif
