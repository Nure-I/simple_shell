<<<<<<< HEAD
#include "shell.h"

/**
* INThandler - handles signals and write the prompt
*@sig: signal to handle
*Return: Nothing (void)
*/

void INThandler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
* print_dollar - Function to print the dollar sign
*Return: Nothing(void)
*/

void print_dollar(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

/**
* main - principal function to run the shell
*@argc: argument count
*@argv: argument vector
*@env: enviroment variables
*Return: 0 on exit, 1 if any failures happen
*/

int main(int argc, char **argv, char **env)
{
	char *buffer, **commands;
	size_t length;
	ssize_t characters;
	pid_t pid;
	int status, count;
	(void)argc;
	buffer = NULL, length = 0, count = 0;
	/*write promt only if it's from standard input*/
	print_dollar();
	/*infinite loop*/
	while ((characters = getline(&buffer, &length, stdin)))
	{
		/*signal kill for contro+c */
		signal(SIGINT, INThandler);
		/*check the end of file*/
		if (characters == EOF)
			end_file(buffer);
		count++;
		/*collect commands from the prompt and store in double pointer*/
		commands = array_strtok(buffer);
		/*create new process*/
		pid = fork();
		if (pid == -1)
			fork_fail();
		if (pid == 0)
			execute(commands, buffer, env, argv, count);
		/*free everithing*/
		else
		{
			wait(&status);
			send_to_free(buffer, commands);
		}
		length = 0, buffer = NULL; /*reset for getline*/
		print_dollar();
	}
	if (characters == -1)
		return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
=======
#include "main.h"

/**
 * free_data - frees data structure
 *
 * @datash: data structure
 * Return: no return
 */
void free_data(data_shell *datash)
{
	unsigned int i;

	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @datash: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(data_shell *datash, char **av)
{
	unsigned int i;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	datash->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = _strdup(environ[i]);
	}

	datash->_environ[i] = NULL;
	datash->pid = aux_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datash, av);
	shell_loop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
>>>>>>> 7861a6113d74e940a4d3f4269a214e8c655a047c
}
