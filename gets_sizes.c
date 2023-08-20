#include "main.h"

/**
 * get_size - Calculate size that print the argument.
 * @format: Format strings that will print arguments.
 * @i: The Listed arguments that are printed
 *
 * Return: Exact Accuracy
 */
int get_size(const char *format, int *i)
{
	int curr_b = *i + 1;
	int size = 0;

	if (format[curr_b] == 'l')
		size = S_LONG;
	else if (format[curr_b] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = curr_b - 1;
	else
		*i = curr_b;

	return (size);
}
