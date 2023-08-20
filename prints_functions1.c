#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Prints unsigned no. or int.
 * @types: List arr. of arguments.
 * @buffer: Buffer arr. to handle print
 * @flags:  for Calculating active flags
 * @width: bring up width.
 * @precision: Specified. Precision.
 * @size: for Size specifier.
 * Return: No. of chars to print.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num /= 10;
	}

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NO. TO OCTAL NOTATIONS  ****************/
/**
 * print_octal - Prints unsigned int in octal notation
 * @types: List arr. for arguments.
 * @buffer: Buffer arr. for handling the print.
 * @flags:  Calculating for active flags.
 * @width: bring up width.
 * @precision: precision specifier.
 * @size: the size specifier.
 * Return: No. of characters to print.
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[a--] = '0';

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NO. TO HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print.
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: a precise specifier
 * @size: the Size specifier.
 * Return: No. of chars to print
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/************* PRINTS A UNSIGNED NO IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Print unsigned no. in upper hexadecimal notation.
 * @types: List arr. of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precise specifier.
 * @size: A size specification.
 * Return: No of chars to print.
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** PRINTS HEXXX NO. IN UPPER OR EVEN LOWER **************/
/**
 * print_hexa - Prints a hexadecimal int in upper or even lower
 * @types: List arr. of arg.
 * @map_to: Arr. of values to map the int.
 * @buffer: A Buffer arr. to process print.
 * @flags:  for Calculating active flags
 * @flag_ch: To Calculate active flags.
 * @width: brign up width.
 * @precision: Specifies Precision.
 * @size: specifies Size
 * @size: A size specifier
 * Return: No. of chars to print.
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[a--] = flag_ch;
		buffer[a--] = '0';
	}

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}
