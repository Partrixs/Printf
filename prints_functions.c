#include "main.h"

/************************* PRINT CHARSS *************************/

/**
 * print_char - Prints all of characters.
 * @types: The List to the arguments.
 * @buffer: A Buffer array to which handles print.
 * @flags:  To Calculate the active flags.
 * @width: for the Width.
 * @precision: for the Precision specification.
 * @size: The Size specifier.
 * Return: No of characters to which printed.
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINTS STRINGS *************************/
/**
 * print_string - Prints strings as description says 
 * @types: Lists all array of arguments.
 * @buffer: Buffer array to handle print.
 * @flags:  Calculates for active flags.
 * @width: brings up width
 * @precision: Precision specification
 * @size: for the Size specifier
 * Return: No of character that prints.
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINTS THE PERCENT SYMBOL. *************************/
/**
 * print_percent - Prints the percent symbol only.
 * @types: The Listing of arguments.
 * @buffer: The Buffer arr to handle print
 * @flags:  For Calculating active flags.
 * @width: bring up the width.
 * @precision: for the Precision specification
 * @size: A Specifier of Size
 * Return: No. of characters that prints
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINTS NO. *************************/
/**
 * print_int - Print the integer.
 * @types: for Listin of argument.
 * @buffer: Buffer array which does handles print.
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/************************* PRINTS ALMIGHTY BINARY *************************/
/**
 * print_binary - Print unsigned no.
 * @types: Lists arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: bring up width.
 * @precision: for Specifier Precision
 * @size: The Size specifier
 * Return: No. of character printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int e, f, k, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	e = va_arg(types, unsigned int);
	f = 2147483648; /* (2 ^ 31) */
	a[0] = e / f;
	for (k = 1; k < 32; k++)
	{
		f /= 2;
		a[k] = (e / f) % 2;
	}
	for (k = 0, sum = 0, count = 0; k < 32; k++)
	{
		sum += a[k];
		if (sum || k == 31)
		{
			char z = '0' + a[k];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
