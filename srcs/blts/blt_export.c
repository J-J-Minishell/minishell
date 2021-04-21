#include "../../includes/minishell.h"

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

int		print_export_error(t_minishell *s, char *token)
{
	char	*tmp;

	tmp = error_backslash_var(s, token);
	if (token[0] == '"')
	{
		free(tmp);
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

int		check_export_error(char *token, int j)
{
	if (j == 0 && !ft_isalpha(token[j]))
		return (1);
	else if (token[j] == '=' || token[j] == '\\')
		return (0);
	else if (!ft_isalnum(token[j]) && j > 0 && token[j - 1] != '\\')
		return (1);
	return (0);
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
		while (s->tokens[i][j])
		{
			if (check_export_error(s->tokens[i], j))
			{
				s->exit_status = print_export_error(s, s->tokens[i]);
				break;
			}
			else if (s->tokens[i][j] == '=')
			{
				export_env_var(s, s->tokens[i], j + 1);
				break;
			}
			j++;
		}
		i++;
	}
}
