#ifndef SHELL_H
#define SHELL_H

#define BUFFSIZE 1024

void loop();
char* readLine();
char** splitLine();
int execute();

void die();

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

/**
 * Reads input line and return input as char buffer
 *
 * @return Input line buffer
 */
char* readLine(){

    // Position for line
    int position;

    // Assigning buffersize to variable to increase it later
    int bufsize = BUFFSIZE;

    // Input char
    char c;

    // Allocating buffer for input line
    char *buffer = malloc(sizeof(char) * bufsize);

    // Error handling for buffer
    if(!buffer) die("Allocation error");

    while(1){

        c = getchar();

        // If input ends, add null char and return
        if(c == EOF || c == '\n'){
            buffer[position] = '\0';
            return buffer;
        }else
            // Append char to buffer
            buffer[position] = c;

        position += 1;

        // If buffer exceeds, reallocate space
        if(position >= bufsize){
            bufsize += BUFFSIZE;
            buffer = realloc(buffer, bufsize);

            if(!buffer) die("Allocation error");
        }

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

#endif
