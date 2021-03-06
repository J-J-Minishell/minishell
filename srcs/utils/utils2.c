#include "../../includes/minishell.h"

char	*error_backslash_var(t_minishell *s, char *token)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	while (token[++i])
	{
		if (token[i] != '\\')
			j++;
	}
	tmp = malloc(sizeof(char) * ft_strlen(token) - j + 1);
	if (!tmp)
		ft_print_error(s);
	i = -1;
	j = 0;
	while (token[++i])
	{
		if (token[i] != '\\')
			tmp[j++] = token[i];
	}
	tmp[j] = '\0';
	return (tmp);
}

void	*ft_free_matrix(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i])
	{
		if (matrix[i] != NULL)
			matrix[i] = ft_free_ptr(matrix[i]);
		i++;
	}
	if (matrix != NULL)
		matrix = ft_free_ptr(matrix);
	return (NULL);
}

void	ft_clean_up(t_minishell *s)
{
	if (g_ln != NULL)
		g_ln = ft_free_ptr(g_ln);
	if (s->home != NULL)
		s->home = ft_free_ptr(s->home);
	if (s->commands != NULL)
		s->commands = ft_free_matrix(s->commands);
	if (s->command_path != NULL)
		s->command_path = ft_free_ptr(s->command_path);
	if (s->tokens != NULL)
		s->tokens = ft_free_matrix(s->tokens);
	if (s->history_cmds != NULL)
		s->history_cmds = ft_free_matrix(s->history_cmds);
	if (s->pwd != NULL)
		s->pwd = ft_free_ptr(s->pwd);
	s->env = ft_free_matrix(s->env);
	s->blt_cmds = ft_free_matrix(s->blt_cmds);
}

void	ft_print_error(t_minishell *s)
{
	ft_putstr_fd("-bash: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
	ft_clean_up(s);
	exit(-1);
}

int	ft_str_is_printable_ascii(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] >= 32)
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}
