#include "main.h"

/****************** PRINTS THOSE POINTERS ******************/
/**
 * print_pointer - Prints value for the pointer variable.
 * @types: the List arr. of arguments.
 * @buffer: the Buffer arr. to process print.
 * @flags:  this Calculates only active flags.
 * @width: this brings up the width
 * @precision: this specifies precision.
 * @size: this one specifies the size
 * Return: No. of characters to print.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int indexx = BUFF_SIZE - 2, length = 2, padd_start = 1;
	/* length=2, for '0x' */
	unsigned long num_adres;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_adres = (unsigned long)addrs;

	while (num_adres > 0)
	{
		buffer[indexx--] = map_to[num_adres % 16];
		num_adres /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	indexx++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, indexx, length,
		width, flags, padd, extra_c, padd_start));
}

/************************* PRINT A NON PRINTABLE FILE *************************/
/**
 * print_non_printable - for Printing the ascii codes in hexxx of non printable chars only.
 * @types: List arr. of arguments.
 * @buffer: A Buffer arr. to process print.
 * @flags:  This one Calculates the active flags.
 * @width: this brings up the width.
 * @precision: specifies the Precision.
 * @size: specifies the size.
 * Return: No. of chars that print.
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = 0, ofset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[a] != '\0')
	{
		if (is_printable(str[a]))
			buffer[a + ofset] = str[a];
		else
			ofset += append_hexa_code(str[a], buffer, a + ofset);

		a++;
	}

	buffer[a + ofset] = '\0';

	return (write(1, buffer, a + ofset));
}

/************************* PRINTS IN A REVERSE FORMAT *************************/
/**
 * print_reverse - Prints the string backwardly.
 * @types: List arr. of args.
 * @buffer: The Buffer arr to process print.
 * @flags:  this one Calculates the active flags.
 * @width: brings up the width
 * @precision: Specifies the Precision
 * @size: specifies the size
 * Return: No. of chars that print.
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int a, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (a = 0; str[a]; a++)
		;

	for (a = a - 1; a >= 0; a--)
	{
		char z = str[a];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PRINTS THAT STRING IN ROT13 FORMAT *************************/
/**
 * print_rot13string - This Prints the strings in rot13
 * @types: List arr. of args.
 * @buffer: The Buffer arr. that process print
 * @flags:  To Calculate active flags.
 * @width: brings up width
 * @precision: specifies for precision.
 * @size: The specifier of a size
 * Return: No. of char.
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int a, b;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (a = 0; str[a]; a++)
	{
		for (b = 0; in[b]; b++)
		{
			if (in[b] == str[a])
			{
				x = out[b];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[b])
		{
			x = str[a];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
