#include "main.h"

/**
 * can_printable - Evaluating if a char is printable
 * @ch: Char to be evaluated.
 *
 * Return: 1 i sucsess, 0 otherwise
 */
int can_printable(char ch)
{
	if (ch >= 32 && ch < 127)
		return (1);

	return (0);
}

/**
 * append_hexa - Append ascci in hexadecimal code to buffer
 * @buffer: An array of chars.
 * @i: Index at which to start appending.
 * @ascii_code: ASSCI code.
 * Return: Always 3
 */
int append_hexa(char ascii_code, char buffer[], int x)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[x++] = '\\';
	buffer[x++] = 'x';

	buffer[x++] = map_to[ascii_code / 16];
	buffer[x] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digital - Verifies if a char is a digit num
 * @ch: Char to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_digital(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_num - Casting a number to the specified size
 * @n: Number to be casted.
 * @s: Number indicating the type to be casted.
 *
 * Return: Casted value of num
 */
long int convert_size_num(long int n, int s)
{
	if (s == S_LONG)
		return (n);
	else if (s == S_SHORT)
		return ((short)n);

	return ((int)n);
}

/**
 * convert_size_unsigned - Casting a number to the specified size
 * @n: Number to be casted
 * @s: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int convert_size_unsigned(unsigned long int n, int s)
{
	if (s == S_LONG)
		return (n);
	else if (s == S_SHORT)
		return ((unsigned short)n);

	return ((unsigned int)n);
}
