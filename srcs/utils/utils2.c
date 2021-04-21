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
	if (line != NULL)
		line = ft_free_ptr(line);
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
	s->env = ft_free_matrix(s->env);
	s->blt_cmds = ft_free_matrix(s->blt_cmds);
}

void	ft_print_error(t_minishell *s)
{
	printf("Error: %s\n", strerror(errno));
	ft_clean_up(s);
	exit(-1);
}

int		ft_str_is_printable_ascii(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] >= 32 && s[i] <= 254)
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);

}
