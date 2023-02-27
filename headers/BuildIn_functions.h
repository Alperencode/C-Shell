#ifndef BUILDIN_IN_H
#define BUILDIN_IN_H

char *buildInCommands[] = {"ls", "cd", "help", "exit"};

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

int cd(char **args){

    if(chdir(args[1]) != 0) die("Command error [cd]");

    return 1;
}

int help(){
    printf("\nC-Shell (UNIX)\n");
    printf("Type program name and arguments\n");
    printf("Followings are build in commands:\n");

    int len = sizeof(buildInCommands) / sizeof(char*);
    for(int i=0; i<len; i++)
        printf("%s\n", buildInCommands[i]);

   return 1;
}

int exit(){
    return 0;
}

#endif
