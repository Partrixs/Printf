#include "main.h"

/**
 * get_width - Calculates width that do prints.
 * @format: Formatted string to which it prints arguments
 * @i: All Listed argument that are printed
 * @list: listed argument
 *
 * Return: for the width
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
