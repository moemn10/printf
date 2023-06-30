#include "main.h"

/**
 * Get_Precision - Calculat the precision For print.
 * @Format: Format strings in which to print the arg.
 * @i: List of arg to be print.
 * @list: list of Arg.
 * Return: Prec.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int let_Sys = *i + 1;
	int Prec = -1;

	if (format[let_Sys] != '.')
		return (Prec);

	Prec = 0;

	for (let_Sys += 1; format[let_Sys] != '\0'; let_Sys++)
	{
		if (is_digit(format[let_Sys]))
		{
			Prec *= 10;
			Prec += format[let_Sys] - '0';
		}
		else if (format[let_Sys] == '*')
		{
			let_Sys++;
			Prec = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = let_Sys - 1;

	return (Prec);
}

