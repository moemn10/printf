#include "main.h"

/**
 * Get_Flags - calc flags.
 * @ForaT: Formating Strings print the arguments.
 * Return: Fl.
 */
int get_flags(const char *format, int *i)
{
	int db, let_AP;
	int Fl = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (let_AP = *i + 1; format[let_AP] != '\0'; let_AP++)
	{
		for (db = 0; FLAGS_CH[db] != '\0'; db++)
			if (format[let_AP] == FLAGS_CH[db])
			{
				Fl |= FLAGS_ARR[db];
				break;
			}

		if (FLAGS_CH[db] == 0)
			break;
	}

	*i = let_AP - 1;

	return (Fl);
}
