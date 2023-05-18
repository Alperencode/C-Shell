#include "Shell.h"

#define RL_BUFSIZE 1024 // Read Line buffer
#define SL_BUFSIZE 64 // Split Line buffer

/**
 * Main shell loop in order to read and split the line then execute the command 
 */
void loop(){
    char *line, **args;
    int status;
    clear();

    do{
        printf("\n> ");

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
    int position = 0;

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
    int position = 0;

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
 * Executes the given arguments using execvp() function
 *
 * @param args Command arguments to execute
 * @return 1 for success, executes die() function for any errors
 */
int launch(char** args){
    // exec: Replaces the current process with an entirely new one. 

    // pid_t: signed integer type for representing process ID
    pid_t pid;
    int status = 0;

    // fork: Makes duplicate of the process and starts them both running (Parent-Child)
    pid = fork();

    if(pid < 0)
        die("Fork error [EXE]");
    
    else if(pid == 0){
        // Child process
        // execvp: type of exec command, which takes command and its args
        if(execvp(args[0], args) == -1) die("Execution error [Command not found]");
    }
    else
        // Parent process
        do{
            // Parent process waits until child process finish
            waitpid(pid, &status, WUNTRACED);

            // WIFEXITED   : program exited
            // WIFSIGNALED : program killed by signal 
        }while(!WIFEXITED(status) && !WIFSIGNALED(status));

    return 1;
}

/**
 * Executes the given argument by checking if it's build-in or not
 *
 * @param args Command arguments to execute
 * @return 1 for success, executes die() function for any errors
 */
int execute(char **args){
    // If command is empty, return
    if(args[0] == NULL) return 1;

    // Check if command is build-in
    int len = buildInLength();
    for(int i=0; i<len; i++)
        if(strcmp(args[0], buildInCommands[i]) == 0)
            return (*buildInFunc[i])(args);

    return launch(args);
}
