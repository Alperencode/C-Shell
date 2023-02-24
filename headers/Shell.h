#ifndef SHELL_H
#define SHELL_H

#define RL_BUFSIZE 1024 // Read Line buffer
#define SL_BUFSIZE 64 // Split Line buffer

void loop();
char* readLine();
char** splitLine(char*, const char*);
int execute(char**);

void die(const char*);

/**
 * Main Shell loop
 */
void loop(){
    char *line, **args;
    int status;

    do{
        printf("\n>");

        line = readLine();
        args = splitLine(line, " \r\r\n\a");
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
    int bufsize = RL_BUFSIZE;

    // Input char
    char c;

    // Allocating buffer for input line
    char *buffer = malloc(sizeof(char) * bufsize);

    if(!buffer) die("Allocation error [RL buffer]");

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
            bufsize += RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);

            if(!buffer) die("Allocation error [RL buffer]");
        }
    }
}

/**
 * Splits the given line with given delims
 *
 * @param line Line to split 
 * @param delims Delims to split the given line
 * @return Array of strings that splitted by delims
 */
char** splitLine(char* line, const char* delims){
    
    // Position tokens array
    int position;

    // Assigning buffersize to variable to increase it later
    int bufsize = SL_BUFSIZE;

    // Allocating space for tokens
    char** tokens = malloc(sizeof(char*) * bufsize);
    char* token;

    if(!tokens) die("Allocation error [SL tokens]");

    // Gathering first token pointer
    token = strtok(line, delims);

    // Walk through other tokens
    while(token != NULL){

        // Assigning current token to tokens
        tokens[position] = token;
        position += 1;

        // If buffer exceeds, reallocate space
        if(position >= bufsize){
            bufsize += SL_BUFSIZE;
            tokens = realloc(tokens, sizeof(char*) * bufsize);
            if(!tokens) die("Allocation error [SL tokens]");
        }

        // Next token
        token = strtok(NULL, delims);
    }

    tokens[position] = NULL;
    return tokens;
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
