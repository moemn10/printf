#include "main.h"

/**
 * Get_size - Calculat the size arg.
 * @Format: Format strings in which to print the arg.
 * @i: List of arg to be print.
 * Return: len..
 */
int get_size(const char *format, int *i)
{
	int let_Sys = *i + 1;
	int len = 0;

	if (format[let_Sys] == 'l')
		len = S_LONG;
	else if (format[let_Sys] == 'h')
		len = S_SHORT;

	if (len == 0)
		*i = let_Sys - 1;
	else
		*i = let_Sys;

	return (len);
}
