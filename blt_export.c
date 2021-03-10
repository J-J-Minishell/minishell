#include "minishell.h"

int		print_export_error(char *token)
{
	ft_putstr_fd("-bash: export: '", 0);
	ft_putstr_fd(token, 0);
	ft_putstr_fd("': not a valid identifier\n", 0);
	return (1);
}

void	change_export_var(t_minishell *s, char *export_var, int i)
{
	free(s->env[i]);
	s->env[i] = ft_strdup(export_var);
}

void	export_env_var(t_minishell *s, char *export_var, int len_name)
{
	char	**tmp;
	int		i;

	i = 0;
	while (s->env[i])
	{
		if (ft_strncmp(s->env[i], export_var, len_name) == 0)
			return (change_export_var(s, export_var, i));
		i++;
	}
	i++;
	if (!(tmp = (char **)malloc(sizeof(char *) * i + 8)))
		ft_print_error(s);
	i = 0;
	while (s->env[i])
	{
		tmp[i] = ft_strdup(s->env[i]);
		i++;
	}
	tmp[i++] = ft_strdup(export_var);
	tmp[i] = NULL;
	s->env = ft_free_matrix(s->env);
	s->env = tmp;
}

void	blt_export(t_minishell *s)
{
	int		i;
	int		j;
	int		exit;

	i = 1;
	while (s->tokens[i])
	{
		j = 0;
		if (!ft_isalpha(s->tokens[i][j]) && s->tokens[i][j] != '_')
			exit = print_export_error(s->tokens[i]);
		else
		{
			while(ft_isalnum(s->tokens[i][j]) || s->tokens[i][j] == '_')
				j++;
			if (s->tokens[i][j] == '=')
				export_env_var(s, s->tokens[i], j + 1);
			exit = exit == 1 ? 1 : 0;
		}
		i++;
	}
	if (exit)
		s->exit_status = 1;
	else
		s->exit_status = 0;
}
