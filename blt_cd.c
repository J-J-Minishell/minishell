#include "minishell.h"

void	blt_cd(t_minishell *s)
{
	int		i;

	chdir(s->tokens[1]);
	i = -1;
	while (s->env[++i])
	{
		if (!(ft_strncmp("PWD=", s->env[i], 4)))
		{
			s->env[i] = ft_free_ptr(s->env[i]);
			s->env[i] = ft_strdup(s->tokens[1]);
			break ;
		}
	}
}
