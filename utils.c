#include "minishell.h"

int		ft_find_env_var(t_minishell *s, char *var)
{
	int	i;

	i = 0;
	while (s->env[i])
	{
		if (!(ft_strncmp(var, s->env[i], ft_strlen(var))))
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_get_env_var_content(t_minishell *s, char *var)
{
	int		i;
	int		j;
	char	*ret;

	i = ft_find_env_var(s, var);
	j = 0;
	while (s->env[i][j] != '=')
		j++;
	ret = strdup(s->env[i] + j + 1);
	return (ret);
}

void	ft_clean_up(t_minishell *s)
{
	if (s->line != NULL)
		s->line = ft_free_ptr(s->line);
	if (s->path != NULL)
		s->path = ft_free_ptr(s->path);
	if (s->home != NULL)
		s->home = ft_free_ptr(s->home);
	if (s->commands != NULL)
		s->commands = ft_free_matrix(s->commands);
	if (s->tokens != NULL)
		s->tokens = ft_free_matrix(s->tokens);
	s->env = ft_free_matrix(s->env);
	s->blt_cmds = ft_free_matrix(s->blt_cmds);
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

void	ft_print_error(t_minishell *s)
{
	printf("Error: %s\n", strerror(errno));
	ft_clean_up(s);
	exit(-1);
}
