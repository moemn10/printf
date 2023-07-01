#include "main.h"
/**
 * handle_print - Prints an arg
 * @fmt: Format string in which to print the args.
 * @list: List of args to be print.
 * @ind: Ind.
 * @buffer: Buffer Arr To Handle Print.
 * @flags: Calculat Active Flags
 * @width: Get Width
 * @precision: Precision Specification.
 * @size: Size Specifier
 * Return: 1 Or 2.
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int let_Sys, len = 0, db_Chars = -1;
	fmt_t fm_data[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pt}, {'S', print_non_printable},
		{'r', print_rev}, {'R', print_rot13}, {'\0', NULL}
	};
	for (let_Sys = 0; fm_data[let_Sys].fmt != '\0'; let_Sys++)
		if (fmt[*ind] == fm_data[let_Sys].fmt)
			return (fm_data[let_Sys].fn(list, buffer, flags, width, precision, size));

	if (fm_data[let_Sys].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		len += write(1, &fmt[*ind], 1);
		return (len);
	}
	return (db_Chars);
}
