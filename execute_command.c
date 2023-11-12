#include "shell.h"

/**
 * execute - Execute a command.
 * @data: Pointer to program data struct.
 * Return: 0 on success, -1 on failure.
 */
int execute(data_of_program *data)
{
    int retval = 0, status;
    pid_t pid;

    retval = builtins_list(data);
    if (retval != -1)
        return retval;

    retval = find_program(data);
    if (retval)
        return retval;

    pid = fork();
    if (pid == -1)
    {
        perror(data->command_name);
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        retval = execve(data->tokens[0], data->tokens, data->env);
        if (retval == -1)
        {
            perror(data->command_name);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
            errno = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            errno = 128 + WTERMSIG(status);
    }

    return 0;
}
