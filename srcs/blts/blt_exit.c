#include "../../includes/minishell.h"

void	blt_exit(t_minishell *s)
{
	int	num;

	if (!s->tokens[1] || (!s->tokens[2] && s->tokens[1][0] == '0' \
		&& s->tokens[1][1] == '\0'))			// si no hay argumentos o solo hay 1 argumento y es 0
		s->exit_status = 0;
	else
	{
		num = atoi(s->tokens[1]);
		s->exit_status = num % 256;
		if (!num)
		{
			ft_putstr_fd("exit\n-bash: exit: ", 0);
			ft_putstr_fd(s->tokens[1], 0);
			ft_putstr_fd(": numeric argument required\n", 0);
			s->exit_status = 255;
		}
		else if (s->tokens[2])
		{
			ft_putstr_fd("exit\n-bash: exit: too many arguments\n", 0);
			s->exit_status = 1;
			return ;
		}
	}
	ft_clean_up(s);
	exit(s->exit_status);
}