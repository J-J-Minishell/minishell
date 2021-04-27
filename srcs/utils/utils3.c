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

void	check_signal(t_minishell *s)
{
	char	*tmp;

	if (g_ln)
	{
		if (!ft_strncmp(g_ln, "ctrl^C", 7))
		{
			g_ln = ft_free_ptr(g_ln);
			s->exit_status = 1;
		}
		else if (!ft_strncmp(g_ln, "ctrl^C", 6))
		{
			tmp = ft_substr(g_ln, 6, ft_strlen(g_ln));
			free(g_ln);
			g_ln = tmp;
			s->exit_status = 1;
		}
	}
}
