#include "../../includes/minishell.h"

int	check_backslash(char *str, int i)
{
	int		counterbar;

	counterbar = 0;
	while (i > 0 && str[--i] == '\\')
		counterbar++;
	if (counterbar % 2)
		return (FALSE);
	return (TRUE);
}
