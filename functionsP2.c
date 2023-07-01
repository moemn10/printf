#include "main.h"

/* *PRINT UNSIGNED NUMBER* */
/**
 * print_unsigned - Printing an unsigned number
 * @types: Listing an  arguments
 * @buffer: Buffering array to handle print
 * @flags:  Calculating active flags
 * @width: geting width
 * @precision: Precision of specification
 * @size: Size of specifier
 * Return: Number of charcters printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	unsigned long int n = va_arg(types, unsigned long int);

	n = convert_size_unsigned int(n, size);

	if (n == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (n > 0)
	{
		buffer[x--] = (n % 10) + '0';
		n /= 10;
	}

	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}

/* *PRINT UNSIGNED NUMBER IN OCTAL* */
/**
 * print_octal - Printing an unsigned number in octal notation
 * @types: Listing an arguments
 * @buffer: Buffering an array to handle print
 * @flags:  Calculating active flags
 * @width: geting width
 * @precision: Precision of specification
 * @size: Size of specifier
 * Return: Number of charcters printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int x = BUFF_SIZE - 2;
	unsigned long int n = va_arg(types, unsigned long int);
	unsigned long int init_n = n;

	UNUSED(width);

	n = convert_size_unsigned int(n, size);

	if (n == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (n > 0)
	{
		buffer[x--] = (n % 8) + '0';
		n /= 8;
	}

	if (flags & F_HASH && init_n != 0)
		buffer[x--] = '0';

	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}

/* *PRINT UNSIGNED NUMBER IN HEXADECIMAL* */
/**
 * print_hexadecimal - Printing an unsigned number in hexadecimal notation
 * @types: Listing an arguments
 * @buffer: Buffering an array to handle print
 * @flags:  Calculating active flags
 * @width: geting  width
 * @precision: Precision of specification
 * @size: Size of specifier
 * Return: Number of charcters printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/* *PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL* */
/**
 * print_hexa_upper - Printing an unsigned number in upper hexadecimal notation
 * @types: Listing an arguments
 * @buffer: Buffering an array to handle print
 * @flags:  Calculating active flags
 * @width: geting width
 * @precision: Precision of specification
 * @size: Size specifier
 * Return: Number of charcters printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/* *PRINT HEXX NUM IN LOWER OR UPPER* */
/**
 * print_hexa - Printing a hexadecimal number in lower or upper
 * @types: Listing an arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffering an array to handle print
 * @flags:  Calculating active flags
 * @flag_ch: Calculating active flags channel
 * @width: geting width
 * @precision: Precision of specification
 * @size: Size of specifier
 * @size: Size of specification
 * Return: Number of charcters printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	unsigned long int n = va_arg(types, unsigned long int);
	unsigned long int init_n = n;

	UNUSED(width);

	n = convert_size_unsigned int(n, size);

	if (n == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (n > 0)
	{
		buffer[x--] = map_to[n % 16];
		n /= 16;
	}

	if (flags & F_HASH && init_n != 0)
	{
		buffer[x--] = flag_ch;
		buffer[x--] = '0';
	}

	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}
