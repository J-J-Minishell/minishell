#include "minishell.h"

void	unset_env_var(t_minishell *s, char *unset_var, int delete)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	while (s->env[i])
		i++;
	if (!(tmp = (char **)malloc(sizeof(char *) * i)))
		ft_print_error(s);
	i = 0;
	j = 0;
	while (s->env[i])
	{
		if (i != delete)
		{
			tmp[j] = ft_strdup(s->env[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	free(s->env);
	s->env = tmp;
}

void	blt_unset(t_minishell *s)
{
	int i;
	int j;
	int delete;

	i = 1;
	while (s->tokens[i])
	{
		j = 0;
		delete = 0;
		while (s->env[j])
		{
			if (ft_strncmp(s->env[j], s->tokens[i], ft_strlen(s->tokens[i])) == 0)
				delete = j;
			j++;
		}
		if (delete)
			unset_env_var(s, s->tokens[i], delete);
		i++;
	}
}