#include "main.h"

/* *PRINT CHAR* */

/**
 * print_char - Prints a character
 * @types: Listing an arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculating active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size of specifier
 * Return: Number of charters printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char a = va_arg(types, int);

	return (handle_write_char(a, buffer, flags, width, precision, size));
}
/* *PRINT A STRING* */
/**
 * print_string - Printing a string
 * @types: Listing an arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculating active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size of specifier
 * Return: Number of charcters printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int l = 0, x;
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

	while (str[l] != '\0')
		l++;

	if (precision >= 0 && precision < l)
		l = precision;

	if (width > l)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], l);
			for (x = width - l; x > 0; x--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (x = width - l; x > 0; x--)
				write(1, " ", 1);
			write(1, &str[0], l);
			return (width);
		}
	}

	return (write(1, str, l));
}
/* *PRINT PERCENT SIGN* */
/**
 * print_percent - Printing a percent sign
 * @types: Listing an arguments
 * @buffer: Buffer Array to handle print
 * @flags:  Calculating active flags
 * @width: get Width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of charcters printed
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

/* *PRINT Integer* */
/**
 * print_int - Printing integer
 * @types: Listing an arguments
 * @buffer: Buffer Array to handle print
 * @flags:  Calculating active flags
 * @width: geting Width.
 * @precision: Precision specification
 * @size: Size of specifier
 * Return: Numbers of characters printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	int N = 0;
	long int J = va_arg(types, long int);
	unsigned long int n;

	J = convert_size_number(J, size);

	if (J == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	n = (unsigned long int)J;

	if (J < 0)
	{
		n = (unsigned long int)((-1) * J);
		N = 1;
	}

	while (n > 0)
	{
		buffer[x--] = (n % 10) + '0';
		n /= 10;
	}

	x++;

	return (write_number(N, x, buffer, flags, width, precision, size));
}

/* *PRINT BINARY* */
/**
 * print_binary - Printing an unsigned number
 * @types: Listing an arguments
 * @buffer: Buffer Array to handle print
 * @flags:  Calculating active flags
 * @width: geting width.
 * @precision: Precision specification
 * @size: Size of specifier
 * Return: Numbers of charcters printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int J, k, x, s;
	unsigned int c[32];
	int ct;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	J = va_arg(types, unsigned int);
	k = 2147483648; /* (2 ^ 31) */
	c[0] = J / k;
	for (x = 1; x < 32; x++)
	{
		k /= 2;
		c[x] = (J / k) % 2;
	}
	for (x = 0, s = 0, ct = 0; x < 32; x++)
	{
		s += c[x];
		if (s || x == 31)
		{
			char b = '0' + c[x];

			write(1, &b, 1);
			ct++;
		}
	}
	return (ct);
}
