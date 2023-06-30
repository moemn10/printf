#include "main.h"

/* *PRINT POINTER* */
/**
 * print_pointer - Printing the value of a pointer variable
 * @types: Listing an arguments
 * @buffer: Buffer an array to handle print
 * @flags:  Calculating active flags
 * @width: geting width
 * @precision: Precision of specification
 * @size: Size of specifier
 * Return: Number of characters printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char ex = 0, p = ' ';
	int D = BUFF_SIZE - 2, l = 2, ps = 1; 
	unsigned long na;
	char map_to[] = "0123456789abcdef";
	void *ad = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (ad == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	na = (unsigned long)ad;

	while (na > 0)
	{
		buffer[D--] = map_to[na % 16];
		na /= 16;
		l++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		p = '0';
	if (flags & F_PLUS)
		ex = '+', l++;
	else if (flags & F_SPACE)
		ex = ' ', l++;

	D++;

	return (write_pointer(buffer, D, l,
		width, flags, D, ex, ps));
}

/* *PRINT NON PRINTABLE* */
/**
 * print_non_printable - Printing ascii codes in hexa of non printable chars
 * @types: Listing an arguments
 * @buffer: Buffering an array to handle print
 * @flags:  Calculating active flags
 * @width: geting width
 * @precision: Precision of specification
 * @size: Size of specifier
 * Return: Number of charcters printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = 0, o = 0;
	char *st = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (st == NULL)
		return (write(1, "(null)", 6));

	while (st[x] != '\0')
	{
		if (is_printable(st[x]))
			buffer[x + o] = st[x];
		else
			o += append_hexa_code(st[x], buffer, x + o);

		x++;
	}

	buffer[x + o] = '\0';

	return (write(1, buffer, x + o));
}

/* *PRINT REVERSE* */
/**
 * print_reverse - Printing reverse string.
 * @types: Listing an arguments
 * @buffer: Buffering an array to handle print
 * @flags:  Calculating active flags
 * @width: geting width
 * @precision: Precision of specification
 * @size: Size of specifier
 * Return: Numbers of charcters printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int x, ct = 0;

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
	for (x = 0; str[x]; x++)
		;

	for (x = x - 1; x >= 0; x--)
	{
		char b = str[x];

		write(1, &b, 1);
		ct++;
	}
	return (ct);
}
/* *PRINT A STRING IN ROT13* */
/**
 * print_rot13string - Printing a string in rot13.
 * @types: Listing an arguments
 * @buffer: Buffering an array to handle print
 * @flags:  Calculating active flags
 * @width: geting width
 * @precision: Precision of specification
 * @size: Size of specifier
 * Return: Numbers of charcter printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char z;
	char *str;
	unsigned int x, y;
	int ct = 0;
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
	for (x = 0; str[x]; x++)
	{
		for (y = 0; in[y]; y++)
		{
			if (in[y] == str[x])
			{
				z = out[y];
				write(1, &z, 1);
				ct++;
				break;
			}
		}
		if (!in[y])
		{
			z = str[x];
			write(1, &z, 1);
			ct++;
		}
	}
	return (ct);
}
