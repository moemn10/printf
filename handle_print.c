#include "main.h"
/**
 * Handle_Print - Prints an arg.
 * @Format: Format string in which to print the args.
 * @List: List of args to be print..
 * @Ind: Ind.
 * @buffer: Buffer Arr To Handle Print.
 * @Flags: Calculat Active Flags.
 * @Width: Get Width.
 * @precision: Precision Specification.
 * @Size: Size Specifier.
 * Return: 1 Or 2.
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int let_Sys, len = 0, db_Chars = -1;
	fmt_t format_data[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (let_Sys = 0; format_data[let_Sys].fmt != '\0'; let_Sys++)
		if (fmt[*ind] == format_data[let_Sys].fmt)
			return (format_data[let_Sys].fn(list, buffer, flags, width, precision, size));

	if (format_data[let_Sys].fmt == '\0')
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
