#include "shellheader.h"

/**
 * _getenv - get value of given environment variable
 * @var: pointer to Environment variable whose value is needed
 * @env: pointer to array of pointers to environment variables
 *
 * Return: pointer to retrieved value, or NULL on failure
 *donr
 */
char *_getenv(char *var, char **env)
{
	int xa, var_len;
	char *env_var;

	var_len = _strlen(var);
	for (xa = 0; env[idx]; idx++)
	{
		if (_strncmp(env[idx], var, var_len) == 0)
		{
			env_var = env[xa];
			break;
		}
	}
	env_var = _strtok(env_var, "=");
	free(env_var);
	env_var = _strtok(NULL, "=");
	return (env_var);
}
