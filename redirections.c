#include "minishell.h"

void	delete_redirections(t_minishell *s, int redirections, int i)
{
	char	**tokens;
	int		len;
	int		j;

	len = i - (redirections * 2);
	if (!(tokens = (char **)malloc(sizeof(char *) * (len + 1))))
		ft_print_error(s);
	i = 0;
	j = 0;
	while (s->tokens[i])
	{
		if (!ft_strncmp(s->tokens[i], ">", 2) || !ft_strncmp(s->tokens[i], ">>", 3))
			i += 2;
		else
		{
			tokens[j] = ft_strdup(s->tokens[i]);
			j++;
			i++;
		}
	}
	tokens[j] = NULL;
	s->tokens = ft_free_matrix(s->tokens);
	s->tokens = tokens;
}

void	delete_in_redirections(t_minishell *s, int redirections, int i)
{
	char	**tokens;
	int		len;
	int		j;

	len = i - (redirections * 2);
	if (!(tokens = (char **)malloc(sizeof(char *) * (len + 1))))
		ft_print_error(s);
	i = 0;
	j = 0;
	while (s->tokens[i])
	{
		if (!ft_strncmp(s->tokens[i], "<", 2))
			i += 2;
		else if (!ft_strncmp(s->tokens[i], "<>", 3))
		{
			i += 2;
			close(s->fd);
			s->fd = 1;
		}
		else
		{
			tokens[j] = ft_strdup(s->tokens[i]);
			j++;
			i++;
		}
	}
	tokens[j] = NULL;
	s->tokens = ft_free_matrix(s->tokens);
	s->tokens = tokens;
}

void	check_in_redirections(t_minishell *s)
{
	int		i;
	int		redirections;

	redirections = 0;
	i = 0;
	while (s->tokens[i])
	{
		if (ft_strncmp(s->tokens[i], "<", 2) == 0)
		{
			s->fdi = open(s->tokens[i + 1], O_RDONLY, 0);
			redirections++;
		}
		else if (ft_strncmp(s->tokens[i], "<>", 3) == 0)
		{
			s->fdi = open(s->tokens[i + 1], O_RDONLY, 0);
			redirections++;
		}
		i++;
	}
	if (redirections)
		delete_in_redirections(s, redirections, i);
}

void	check_redirections(t_minishell *s)
{
	int		i;
	int		redirections;

	redirections = 0;
	i = 0;
	while (s->tokens[i])
	{
		if (ft_strncmp(s->tokens[i], ">", 2) == 0)
		{
			s->fd = open(s->tokens[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
			redirections++;
		}
		else if (ft_strncmp(s->tokens[i], "<>", 3) == 0)
		{
			s->fd = open(s->tokens[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
			redirections++;
		}
		else if (ft_strncmp(s->tokens[i], ">>", 3) == 0)
		{
			s->fd = open(s->tokens[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
			redirections++;
		}
		i++;
		if (s->fd != 1 && s->tokens[i] && (!ft_strncmp(s->tokens[i], ">", 2) ||
			!ft_strncmp(s->tokens[i], ">>", 3)))
			close(s->fd);
	}
	if (redirections)
		delete_redirections(s, redirections, i);
	check_in_redirections(s);
}
