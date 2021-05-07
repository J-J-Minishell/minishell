#include "../../includes/minishell.h"

void	blt_env(t_minishell *s)
{
	int	i;

	if (ft_find_env_var(s, "PATH=") == -1)
	{
		ft_putstr_fd("bash: env: No such file or directory\n", 2);
		s->exit_status = 127;
		return ;
	}
	i = 0;
	while (s->env[i])
	{
		ft_putstr_fd(s->env[i], s->fd);
		write(s->fd, "\n", 1);
		i++;
	}
	s->exit_status = 0;
}
