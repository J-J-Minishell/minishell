#include "../../includes/minishell.h"

/*
** This function manage the situation when export command is called with no
** arguments. It will print every environment variable with the statement
** "declare -x" fordward to them.
*/

void	export(t_minishell *s)
{
	int	i;

	i = 0;
	while (s->env[i])
	{
		ft_putstr_fd("declare -x ", s->fd);
		ft_putstr_fd(s->env[i], s->fd);
		write(s->fd, "\n", 1);
		i++;
	}
}

int	print_export_error(t_minishell *s, char *token)
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
			return ;
		}
		i++;
	}
	s->env = add_new_pos_matrix(s->env, export_var);
}

/*
** This function first check if the initial character of the name of the
** variable that should be exported is alphabetic. In case it is not, it calls
** print_export_error() because this first char should be alphabetic.
** Then, is looks if the character is now analyzing is '=' or '\'. In that
** case returns to the caller. If it is not one of those,
*/

int	check_export_error(t_minishell *s, int i, int j)
{
	if (j == 0 && !ft_isalpha(s->tokens[i][j]))
	{
		s->exit_status = print_export_error(s, s->tokens[i]);
		return (1);
	}
	else if (s->tokens[i][j] == '=' || s->tokens[i][j] == '\\')
		return (0);
	else if (!ft_isalnum(s->tokens[i][j]) && j > 0 && s->tokens[i][j] != '\\')
	{
		s->exit_status = print_export_error(s, s->tokens[i]);
		return (1);
	}
	return (0);
}

/*
** This function first check if export command was called with no arguments.
** In that case, it calls export_no_arguments() function. If not, it starts
** exploring the arguments. If a character not allowed in an environment
** variable is detected, function check_export_error() is called. If '='
** character is detected function export_env_variable() is called in order
** to create or actualize the variable with the information next to the
** equal sign.
*/

void	blt_export(t_minishell *s)
{
	int		i;
	int		j;

	i = 1;
	if (!s->tokens[i])
		export(s);
	while (s->tokens[i])
	{
		j = 0;
		while (s->tokens[i][j])
		{
			if (check_export_error(s, i, j))
				break ;
			else if (s->tokens[i][j] == '=')
			{
				export_env_var(s, s->tokens[i], j + 1);
				break ;
			}
			j++;
		}
		i++;
	}
}
