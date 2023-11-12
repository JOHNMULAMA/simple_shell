#include "shell.h"

/**
 * str_length - return length of string
 * @string: ptr to str
 * Return: length of str
 */
int str_length(const char *string)
{
    if (string == NULL)
        return 0;

    int length = 0;
    while (string[length] != '\0')
    {
        length++;
    }
    return length;
}

/**
 * str_duplicate - duplicate the string
 * @string: str to be duplicated
 * Return: ptr to the array
 */
char *str_duplicate(const char *string)
{
    if (string == NULL)
        return NULL;

    int length = str_length(string) + 1;

    char *result = malloc(sizeof(char) * length);

    if (result == NULL)
    {
        perror("Error");
        errno = ENOMEM;
        return NULL;
    }

    for (int i = 0; i < length; i++)
    {
        result[i] = string[i];
    }

    return result;
}

/**
 * str_compare - Compare strings
 * @string1: String one
 * @string2: String two
 * @number: num of char to be compared, 0 if infinite
 * Return: 1 if the strings are similar, 0 if the strings not
 */
int str_compare(const char *string1, const char *string2, int number)
{
    if (string1 == NULL && string2 == NULL)
        return 1;

    if (string1 == NULL || string2 == NULL)
        return 0;

    if (number == 0)
    {
        int iterator = 0;
        while (string1[iterator] != '\0')
        {
            if (string1[iterator] != string2[iterator])
                return 0;
            iterator++;
        }
        return 1;
    }
    else
    {
        for (int iterator = 0; iterator < number; iterator++)
        {
            if (string1[iterator] != string2[iterator])
                return 0;
        }
        return 1;
    }
}

/**
 * str_concat - concatenate strings.
 * @string1: String one
 * @string2: String two
 * Return: ptr to the str
 */
char *str_concat(const char *string1, const char *string2)
{
    if (string1 == NULL)
        string1 = "";
    if (string2 == NULL)
        string2 = "";

    int length1 = str_length(string1);
    int length2 = str_length(string2);

    char *result = malloc(sizeof(char) * (length1 + length2 + 1));
    if (result == NULL)
    {
        perror("Error");
        errno = ENOMEM;
        return NULL;
    }

    int i, j;

    for (i = 0; i < length1; i++)
    {
        result[i] = string1[i];
    }

    for (j = 0; j < length2; j++, i++)
    {
        result[i] = string2[j];
    }

    result[i] = '\0';
    return result;
}

/**
 * str_reverse - function to reverse a string.
 *
 * @string: ptr to str.
 * Return: void.
 */
void str_reverse(char *string)
{
    int i = 0, length = str_length(string) - 1;
    char hold;

    while (i < length)
    {
        hold = string[i];
        string[i++] = string[length];
        string[length--] = hold;
    }
}
