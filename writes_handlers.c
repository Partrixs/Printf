#include "main.h"

/************************* WRITES THE HANDLE *************************/
/**
 * handle_write_char - Writes out the string.
 * @c: types of char to be Displayed..
 * @buffer: An Buffer arr. to process print..
 * @flags:  for Calculating active flags only..
 * @width: writes the width.
 * @precision: Specifies the precision.
 * @size: specifies Size only.
 *
 * Return: no. of char to print
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at the left then it is paddind at the buffer's right */
	int a = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[a++] = c;
	buffer[a] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (a = 0; a < width - 1; a++)
			buffer[BUFF_SIZE - a - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - a - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - a - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE THE INT *************************/
/**
 * write_number - writes out a string.
 * @is_negative: List arr. of args
 * @ind: types char......
 * @buffer: the Buffer arr. which processes print...
 * @flags:  active flags which is calculated...
 * @width: brings up the width..
 * @precision: specifies the precision..
 * @size: Specifies only the size..
 *
 * Return: No. of char which id to print.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - Writes out an int using buffer..
 * @ind: Index for which an int starts on buffer..
 * @buffer: the Buffer only...
 * @flags: the Flags only....
 * @width: bring in width..
 * @prec: specifies the Precision..
 * @length: Number length
 * @padd: Padds the char...
 * @extra_c: more of the char..
 *
 * Return: No. of char that display.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int a, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (a = 1; a < width - length + 1; a++)
			buffer[a] = padd;
		buffer[a] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign an extra char on the left side to buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], a - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char on left buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], a - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char for the left padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], a - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - will Write unsigned no.
 * @is_negative: No indicating if int is negative.
 * @ind: Index of which an int starts in buffer...
 * @buffer: The Arr. of char only.
 * @flags: speccifier for Flags...
 * @width: brings in the Width...
 * @precision: to specify the precision...
 * @size: to specify the size..
 *
 * Return: No. of char which is written.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The int. is stored on the bufer right which also starts at position i */
	int length = BUFF_SIZE - ind - 1, a = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  0 char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (a = 0; a < width - length; a++)
			buffer[a] = padd;

		buffer[a] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], a));
		}
		else /* Asign extra chars on left to padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], a) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}
/**
 * write_pointer - Displays a memory address
 * @buffer: Arr. for char.
 * @ind: Index for which the int starts in buffer.
 * @length: Len. of int.
 * @width: Specifier for width..
 * @flags: Specifies for Flags...
 * @padd: Char to represent padding..
 * @extra_c: Char that represents an extra char.
 * @padd_start: the Index for padding to start.
 *
 * Return: No. of written char.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int a;

	if (width > length)
	{
		for (a = 3; a < width - length + 3; a++)
			buffer[a] = padd;
		buffer[a] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char on left side buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], a - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], a - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char on left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], a - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
