#include "shell.h"

// Constants for error codes
#define FILE_NOT_FOUND_ERROR 127
#define PERMISSION_DENIED_ERROR 126

int check_file(char *full_path);

int find_program(data_of_program *data)
{
    int i = 0, ret_code = 0;
    char **directories;

    if (!data->command_name)
        return FILE_NOT_FOUND_ERROR;

    if (data->command_name[0] == '/' || data->command_name[0] == '.')
        return check_file(data->command_name);

    free(data->tokens[0]);
    data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
    if (!data->tokens[0])
        return FILE_NOT_FOUND_ERROR;

    directories = tokenize_path(data);

    if (!directories || !directories[0])
    {
        errno = FILE_NOT_FOUND_ERROR;
        return FILE_NOT_FOUND_ERROR;
    }

    for (i = 0; directories[i]; i++)
    {
        directories[i] = str_concat(directories[i], data->tokens[0]);
        ret_code = check_file(directories[i]);
        if (ret_code == 0 || ret_code == PERMISSION_DENIED_ERROR)
        {
            errno = 0;
            free(data->tokens[0]);
            data->tokens[0] = str_duplicate(directories[i]);
            free_array_of_pointers(directories);
            return ret_code;
        }
    }

    free(data->tokens[0]);
    data->tokens[0] = NULL;
    free_array_of_pointers(directories);
    return ret_code;
}

char **tokenize_path(data_of_program *data)
{
    int i = 0;
    int counter_directories = 2;
    char **tokens = NULL;
    char *path_variable;

    path_variable = env_get_key("PATH", data);
    if ((path_variable == NULL) || path_variable[0] == '\0')
    {
        return NULL;
    }

    path_variable = str_duplicate(path_variable);

    for (i = 0; path_variable[i]; i++)
    {
        if (path_variable[i] == ':')
            counter_directories++;
    }

    tokens = malloc(sizeof(char *) * counter_directories);

    if (tokens == NULL)
    {
        errno = ENOMEM;
        perror("Error");
        return NULL;
    }

    i = 0;
    tokens[i] = str_duplicate(_strtok(path_variable, ":"));
    while (tokens[i++])
    {
        tokens[i] = str_duplicate(_strtok(NULL, ":"));
    }

    free(path_variable);
    path_variable = NULL;
    return tokens;
}

int check_file(char *full_path)
{
    struct stat file_stats;

    if (stat(full_path, &file_stats) != -1)
    {
        if (S_ISDIR(file_stats.st_mode) || access(full_path, X_OK))
        {
            errno = PERMISSION_DENIED_ERROR;
            return PERMISSION_DENIED_ERROR;
        }
        return 0;
    }

    errno = FILE_NOT_FOUND_ERROR;
    return FILE_NOT_FOUND_ERROR;
}
