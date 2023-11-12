#include "shell.h"

/**
 * expand_variables - Expand variables in the input line.
 * @data: A pointer to the program's data structure.
 *
 * Return: Void, sets errno.
 */
void expand_variables(data_of_program *data)
{
    int i, j;
    char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

    if (data->input_line == NULL)
        return;

    buffer_add(line, data->input_line);

    for (i = 0; line[i]; i++)
    {
        if (line[i] == '#' || line[i] == '$')
        {
            if (line[i] == '$' && line[i + 1] == '?')
            {
                // Expand $? to the value of errno.
                line[i] = '\0';
                long_to_string(errno, expansion, 10);
                buffer_add(line, expansion);
                buffer_add(line, data->input_line + i + 2);
            }
            else if (line[i] == '$' && line[i + 1] == '$')
            {
                // Expand $$ to the process ID.
                line[i] = '\0';
                long_to_string(getpid(), expansion, 10);
                buffer_add(line, expansion);
                buffer_add(line, data->input_line + i + 2);
            }
            else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
            {
                continue; // Ignore $ followed by space or end of line.
            }
            else if (line[i] == '$')
            {
                // Expand other $variables.
                for (j = 1; line[i + j] && line[i + j] != ' '; j++)
                    expansion[j - 1] = line[i + j];
                expansion[j - 1] = '\0';
                temp = env_get_key(expansion, data);
                line[i] = '\0';
                expansion[0] = '\0';
                buffer_add(expansion, line + i + j);
                temp ? buffer_add(line, temp) : 1;
                buffer_add(line, expansion);
            }
        }
    }

    if (!str_compare(data->input_line, line, 0))
    {
        free(data->input_line);
        data->input_line = str_duplicate(line);
    }
}

/**
 * expand_alias - Expand aliases in the input line.
 * @data: Pointer to the struct of program data.
 *
 * Return: Void, sets errno.
 */
void expand_alias(data_of_program *data)
{
    int i, j, was_expanded = 0;
    char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

    if (data->input_line == NULL)
        return;

    buffer_add(line, data->input_line);

    for (i = 0; line[i]; i++)
    {
        for (j = 0; line[i + j] && line[i + j] != ' '; j++)
            expansion[j] = line[i + j];
        expansion[j] = '\0';

        temp = get_alias(data, expansion);
        if (temp)
        {
            expansion[0] = '\0';
            buffer_add(expansion, line + i + j);
            line[i] = '\0';
            buffer_add(line, temp);
            buffer_add(line, expansion);
            was_expanded = 1;
        }
        break; // Assuming you want to expand only the first alias.
    }

    if (was_expanded)
    {
        free(data->input_line);
        data->input_line = str_duplicate(line);
    }
}

/**
 * buffer_add - Append a string at the end of the buffer.
 * @buffer: Buffer to be filled.
 * @str_to_add: String to be put in the buffer.
 * Return: The new length of the buffer.
 */
int buffer_add(char *buffer, char *str_to_add)
{
    int length, i;

    length = str_length(buffer);

    for (i = 0; str_to_add[i]; i++)
    {
        buffer[length + i] = str_to_add[i];
    }

    buffer[length + i] = '\0';

    return (length + i);
}
