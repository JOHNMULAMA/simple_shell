#include "shell.h"

/**
 * tokenize - this function separates the string using a designed delimiter
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void tokenize(data_of_program *data)
{
    const char *delimiter = " \t";
    int i, counter = 2, length;

    length = str_length(data->input_line);

    if (length > 0 && data->input_line[length - 1] == '\n')
        data->input_line[length - 1] = '\0';

    for (i = 0; data->input_line[i]; i++)
    {
        for (int j = 0; delimiter[j]; j++)
        {
            if (data->input_line[i] == delimiter[j])
            {
                counter++;
                break; // Break early once a delimiter is found.
            }
        }
    }

    data->tokens = malloc(counter * sizeof(char *));
    if (data->tokens == NULL)
    {
        perror(data->program_name);
        exit(errno);
    }

    char *token;
    i = 0;
    token = _strtok(data->input_line, delimiter);
    while (token != NULL)
    {
        data->tokens[i] = str_duplicate(token);
        if (i == 0)
            data->command_name = str_duplicate(token);
        token = _strtok(NULL, delimiter);
        i++;
    }
}
