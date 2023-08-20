#include "main.h"

/**
 * is_printable - Function to Evaluate a printable char.
 * @c: The Char that should be evaluated
 *
 * Return: 1 if c can be printed, else just leave it at 0
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - replace by appending ascci in hexxa code to the buffer.
 * @buffer: Arr. of char.
 * @i: the Index of which you append
 * @ascii_code: represents ASSCI CODE
 * Return: to return the int 3
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexx code for this is 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies char as a digit.
 * @c: evaluated char only.
 *
 * Return: if c is a digit return 1, if not, 0.
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - displays an in to the size specified.
 * @num: int which to display.
 * @size: int that indicates type which is displayed.
 *
 * Return: Displayed int.
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Displays an int no which size is specified.
 * @num: int no. that is displayed
 * @size: int that indicates a type to display
 *
 * Return: Displayed value of int.
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
