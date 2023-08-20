#include "main.h"

/**
 * get_width - Calculate width for a print
 * @format: Formatted string to print an argument.
 * @i: for Listed arguments that prints.
 * @list: The listed arguments.
 *
 * Return: only for width
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_b;
	int width = 0;

	for (curr_b = *i + 1; format[curr_b] != '\0'; curr_b++)
	{
		if (is_digit(format[curr_b]))
		{
			width *= 10;
			width += format[curr_b] - '0';
		}
		else if (format[curr_b] == '*')
		{
			curr_b++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_b - 1;

	return (width);
}
