#include "main.h"

/**
 * get_precision - Calculates to the precision that prints.
 * @format: For Formatted string to which it does print the argument.
 * @i: Every List of argument that is printed
 * @list: The list of all the arguments
 *
 * Return: for the Precision
 */
int get_precision(const char *format, int *i, va_list list)
{
	int curr_b = *i + 1;
	int precision = -1;

	if (format[curr_b] != '.')
		return (precision);

	precision = 0;

	for (curr_b += 1; format[curr_b] != '\0'; curr_b++)
	{
		if (is_digit(format[curr_b]))
		{
			precision *= 10;
			precision += format[curr_b] - '0';
		}
		else if (format[curr_b] == '*')
		{
			curr_b++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_b - 1;

	return (precision);
}
