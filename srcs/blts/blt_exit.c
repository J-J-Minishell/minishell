#include "../../includes/minishell.h"

void	exit_errors(t_minishell *s, int error)
{
	if (error == 1)
	{
		ft_putstrs_fd("exit\n-bash: exit: ", s->tokens[1], \
				": numeric argument required\n", 2);
		s->exit_status = 255;
	}
	else if (error == 2)
	{
		ft_putstr_fd("exit\n-bash: exit: too many arguments\n", 0);
		s->exit_status = 1;
	}
}

int	check_numeric_argument(t_minishell *s)
{
	int	i;

	i = 0;
	if (s->tokens[1][0] == '-')
		i++;
	while (s->tokens[1][i])
	{
		if (!ft_isdigit(s->tokens[1][i]))
		{
			exit_errors(s, 1);
			return (0);
		}
		i++;
	}
	return (1);
}

void	blt_exit(t_minishell *s)
{
	int	num;

	if (!s->tokens[1] || (!s->tokens[2] && s->tokens[1][0] == '0' \
		&& s->tokens[1][1] == '\0'))
		s->exit_status = 0;
	else if (check_numeric_argument(s))
	{
		num = ft_atoi(s->tokens[1]);
		s->exit_status = num % 256;
		if (!num)
			exit_errors(s, 1);
		else if (s->tokens[2])
			return (exit_errors(s, 2));
	}
	ft_clean_up(s);
	exit(s->exit_status);
}
