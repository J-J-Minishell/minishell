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

int	double_redirection_error(t_minishell *s, int i)
{
	if (i == -1)
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	else if (g_ln[i] == '<')
		ft_putstr_fd("-bash: syntax error near unexpected token `<'\n", 2);
	else if (g_ln[i] == '>')
		ft_putstr_fd("-bash: syntax error near unexpected token `>'\n", 2);
	s->exit_status = 258;
	return (TRUE);
}
