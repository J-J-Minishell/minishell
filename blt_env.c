#include "minishell.h"

void	blt_env(t_minishell *s)
{
	int 	i;

	i = 0;
	while (s->env[i] != NULL)
		printf("%s\n", s->env[i++]);
}
