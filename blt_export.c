#include "minishell.h"

void	export(t_minishell *s)
{
	int 	i;

	i = 0;
	while (s->env[i])
	{
		ft_putstr_fd("declare -x ", s->fd);
		ft_putstr_fd(s->env[i], s->fd);
		write(s->fd, "\n", 1);
		i++;
	}
}

int		print_export_error(char *token)
{
	char	*tmp;

	tmp = ft_strdup(token);
	if (token[0] == '"')
	{
		ft_free_ptr(tmp);
		tmp = ft_strtrim(token, "\"");
	}
	ft_putstr_fd("-bash: export: `", 0);
	ft_putstr_fd(tmp, 0);
	ft_putstr_fd("': not a valid identifier\n", 0);
	ft_free_ptr(tmp);
	return (1);
}

void	export_env_var(t_minishell *s, char *export_var, int len_name)
{
	int		i;

	i = 0;
	while (s->env[i])
	{
		if (ft_strncmp(s->env[i], export_var, len_name) == 0)
		{
			free(s->env[i]);
			s->env[i] = ft_strdup(export_var);
			return;
		}
		i++;
	}
	s->env = add_new_pos_matrix(s->env, export_var);
}

void	set_exit_status(t_minishell *s, int exit)
{
	if (exit)
		s->exit_status = 1;
	else
		s->exit_status = 0;
}

void	blt_export(t_minishell *s)
{
	int		i;
	int		j;
	int		exit;

	i = 1;
	if (!s->tokens[i])
		export(s);
	exit = 0;
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
		}
		i++;
	}
	set_exit_status(s, exit);
}
