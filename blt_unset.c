#include "minishell.h"

int		print_unset_error(char *token)
{
	ft_putstr_fd("-bash: unset: '", 0);
	ft_putstr_fd(token, 0);
	ft_putstr_fd("': not a valid identifier\n", 0);
	return (1);
}

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
	int		i;
	int		j;
	int		exit;

	i = 1;
	exit = 0;
	while (s->tokens[i])
	{
		j = ft_find_env_var(s, s->tokens[i]);
		if (!ft_isalpha(s->tokens[i][0]) && s->tokens[i][0] != '_')
			exit = print_unset_error(s->tokens[i]);
		else if (j >= 0)
		{
			unset_env_var(s, s->tokens[i], j);
			exit = exit == 1 ? 1 : 0;
		}
		i++;
	}
	if (exit)
		s->exit_status = 1;
	else
		s->exit_status = 0;
}