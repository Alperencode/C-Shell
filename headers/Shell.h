#ifndef SHELL_H
#define SHELL_H

void loop();
char* readLine();
char** splitLine();
int execute();

void loop(){
    char *line, **args;
    int status;


    do{
        printf("\n>");

        line = readLine();
        args = splitLine(line);
        status = execute(args);

        free(line);
        free(args);

    }while(status);

}

#endif
