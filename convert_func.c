#include "shell.h"

/**
 * long_to_string - Convert number to a string.
 * @number: Number to convert.
 * @string: Buffer to save the num as a string.
 * @base: Base for conversion.
 *
 * Return: Nothing.
 */
void long_to_string(long number, char *string, int base)
{
    int index = 0;
    int inNegative = 0;
    long cociente = number;
    char letters[] = "0123456789abcdef";

    if (cociente == 0)
        string[index++] = '0';

    if (string[0] == '-')
        inNegative = 1;

    while (cociente)
    {
        if (cociente < 0)
            string[index++] = letters[-(cociente % base)];
        else
            string[index++] = letters[cociente % base];
        cociente /= base;
    }

    if (inNegative)
        string[index++] = '-';

    string[index] = '\0';
    str_reverse(string);
}

/**
 * _atoi - Custom atoi function.
 *
 * @s: Pointer to string.
 * Return: 0, or string int.
 */
int _atoi(char *s)
{
    int sign = 1;
    unsigned int number = 0;

    while (!('0' <= *s && *s <= '9') && *s != '\0')
    {
        if (*s == '-')
            sign *= -1;
        if (*s == '+')
            sign *= +1;
        s++;
    }

    while ('0' <= *s && *s <= '9' && *s != '\0')
    {
        number = (number * 10) + (*s - '0');
        s++;
    }

    return (number * sign);
}

/**
 * count_characters - Count the number of characters in a string.
 *
 * @string: Pointer to string.
 * @character: String to be counted.
 * Return: 0, or string int.
 */
int count_characters(char *string, char *character)
{
    int i = 0;
    int counter = 0;

    for (; string[i]; i++)
    {
        if (string[i] == character[0])
            counter++;
    }

    return (counter);
}
