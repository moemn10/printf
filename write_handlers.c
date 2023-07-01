#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Print a strings.
 * @c: Char Types.
 * @buffer: Buffer Arr To handle print.
 * @flags:  Calculat active Flags.
 * @width: Get Width.
 * @precision: Precision Specifier.
 * @size: Size Specifier.
 * Return: Number of Chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int db = 0;
	char len = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		len = '0';

	buffer[db++] = c;
	buffer[db] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (db = 0; db < width - 1; db++)
			buffer[BUFF_SIZE - db - 2] = len;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - db - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - db - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Print a String.
 * @is_negative: List of args.
 * @ind: char Types.
 * @buffer: Buffer Arr to handle print
 * @flags:  Calculat the Flags.
 * @width: Get width.
 * @precision: precision specifier
 * @size: Size Specifier
 * Return: Number of Chars print.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length_one = BUFF_SIZE - ind - 1;
	char len = ' ', ch_root = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		len = '0';
	if (is_negative)
		ch_root = '-';
	else if (flags & F_PLUS)
		ch_root = '+';
	else if (flags & F_SPACE)
		ch_root = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length_one, len, ch_root));
}

/**
 * write_num - Write A Number with buffer.
 * @ind: the number start on the buffer.
 * @buffer: Buffer.
 * @flags: Flags.
 * @width: Width.
 * @precision: Precision Specifier.
 * @length: Num length.
 * @padd: Pading Char.
 * @extra_c: Extra Char.
 * Return: print number on the char.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int precision,
	int length, char padd, char extra_c)
{
	int db, pading = 1;

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (db = 1; db < width - length + 1; db++)
			buffer[db] = padd;
		buffer[db] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], db - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], db - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--pading] = extra_c;
			return (write(1, &buffer[pading], db - pading) +
				write(1, &buffer[ind], length - (1 - pading)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes Number.
 * @is_negative: Number indicating if the Num is Negative
 * @ind: the number start in the buffer.
 * @buffer: Arr of Chars.
 * @flags: Flags Specifiers
 * @width: Width Specifier
 * @precision: Precision Specifier
 * @size: Size specifier
 * Return: write number on the char.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int length_one = BUFF_SIZE - ind - 1, db = 0;
	char pading = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);

	if (precision > 0 && precision < length_one)
		pading = ' ';

	while (precision > length_one)
	{
		buffer[--ind] = '0';
		length_one++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pading = '0';

	if (width > length_one)
	{
		for (db = 0; db < width - length_one; db++)
			buffer[db] = pading;

		buffer[db] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], length_one) + write(1, &buffer[0], db));
		}
		else
		{
			return (write(1, &buffer[0], db) + write(1, &buffer[ind], length_one));
		}
	}

	return (write(1, &buffer[ind], length_one));
}

/**
 * write_pointer - Write Memory Address.
 * @buffer: Arr of chars.
 * @ind: the number start in the buffer
 * @length: Length of num.
 * @width: Width Specifier.
 * @flags: Flags Specifier.
 * @padd: Char Representing the padding.
 * @extra_c: Char representing extra char.
 * @padd_start: which padding should start.
 * Return: Number of write chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int db;

	if (width > length)
	{
		for (db = 3; db < width - length + 3; db++)
			buffer[db] = padd;
		buffer[db] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], db - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], db - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], db - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
