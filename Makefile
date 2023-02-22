Shell: Shell.c
	$(CC) Shell.c -o Shell -Wall -Wextra -pedantic -std=c99 && trap '$(RM) Shell' EXIT; ./Shell
	$(RM) Shell
