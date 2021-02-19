#include "minishell.h"

void	ft_clean_up(t_minishell *s)
{
	if (s->line != NULL)
		ft_free_ptr(s->line);
	if (s->path != NULL)
		ft_free_ptr(s->path);
	ft_free_matrix(s->env);
	ft_free_matrix(s->commands);
	ft_free_matrix(s->tokens);
	ft_free_matrix(s->blt_cmds);
}

void	ft_free_matrix(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i])
	{
		if (matrix[i] != NULL)
			ft_free_ptr(matrix[i]);
		i++;
	}
	if (matrix != NULL)
		ft_free_ptr(matrix);
}

void	ft_print_error(t_minishell *s)
{
	printf("Error: %s\n", strerror(errno));
	ft_clean_up(s);
	exit(-1);
}
