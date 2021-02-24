#include "minishell.h"

void	ft_clean_up(t_minishell *s)
{
	if (s->line != NULL)
		s->line = ft_free_ptr(s->line);
	if (s->path != NULL)
		s->path = ft_free_ptr(s->path);
	s->env = ft_free_matrix(s->env);
	s->commands = ft_free_matrix(s->commands);
	s->tokens = ft_free_matrix(s->tokens);
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
