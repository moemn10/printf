#include "main.h"

/**
 * Get_Width - Calculat the width for print.
 * @Format: Format strings in which to print the args.
 * @i: List of args To be print.
 * @List: List of args.
 * Return: Wid.
 */
int get_width(const char *format, int *i, va_list list)
{
	int let_Sys;
	int Wid = 0;

	for (let_Sys = *i + 1; format[let_Sys] != '\0'; let_Sys++)
	{
		if (is_digital(format[let_Sys]))
		{
			Wid *= 10;
			Wid += format[let_Sys] - '0';
		}
		else if (format[let_Sys] == '*')
		{
			let_Sys++;
			Wid = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = let_Sys - 1;

	return (Wid);
}
