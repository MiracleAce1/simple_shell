#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

/**
 * main - A simple shell program designed to run commands and lot more
 * Author: Ace
 *
 * when this program is compiled and excuted, it will creat a new shell,
 * and it will run a lot functions which has been included in the program,
 * such as getline sysmtem call and strtok and lot more and reads the imput
 * from teminal.
 *
 * retturn: 0;
 */

int main(void)
{
	size_t n = 0;
	char *buff = malloc(sizeof(char) * n);
	char *prompt = "$ ";
	ssize_t ace;
	pid_t pid;
	int status;
	extern char **environ;
	char *argv = NULL;

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ace = getline(&buff, &n, stdin);

		if (ace == -1)
		{
			perror("getline is unsuccessful");
			free(buff);
			exit(EXIT_FAILURE);
		}
		if (buff[ace - 1] == '\n')
		{
			buff[ace - 1] = '\0';
		}
		if (strcmp(buff, "exit") == 0)
		{
			break;
		}

		/*using the fork system call*/
		pid = fork();
		if (pid == -1)
		{
			perror("fork is unsuccessful");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			char *args[70];
			char *token;
			int i = 0;

			/*tokenising the executable command*/
			token = strtok(buff, " ");
			while (token != NULL)
			{
				args[i++] = token;
				token = strtok(NULL, " ");
			}
			args[i] = NULL;

			/*using execve system call*/
			execve(args[0], args, environ);
			perror(buff);
			exit(EXIT_FAILURE);
		}
		else /*(waitpid(pid, &status, 0) == -1)8*/
		{
			waitpid(pid, NULL, 0);
			/* perror("Error (wait)");
			 * exit(EXIT_FAILURE);*/
		}
	}
	free(buff);
	/*free(args);*/

	return 0;
}
