#include "../../includes/minishell.h"

void	delete_redirections(t_minishell *s, int redirections, int i)
{
	char	**tokens;
	int		len;
	int		j;

	len = i - (redirections * 2);
	tokens = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tokens)
		ft_print_error(s);
	i = 0;
	j = 0;
	while (s->tokens[i])
	{
		if (!ft_strncmp(s->tokens[i], ">>", 3) || \
		!ft_strncmp(s->tokens[i], ">", 2) || !ft_strncmp(s->tokens[i], "<>", 3))
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
	tokens = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tokens)
		ft_print_error(s);
	i = 0;
	j = 0;
	while (s->tokens[i])
	{
		if (!ft_strncmp(s->tokens[i], "<", 2))
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

int	check_in_redirections(t_minishell *s)
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
			if (s->fdi == -1)
			{
				printf("-bash: %s: %s\n", s->tokens[2], strerror(errno));
				s->exit_status = 1;
				return (-1);
			}
			redirections++;
		}
		i++;
	}
	if (redirections)
		delete_in_redirections(s, redirections, i);
	return (0);
}

int	output_redirections(t_minishell *s, int i, int redirections)
{
	if (!ft_strncmp(s->tokens[i], ">", 2))
	{
		s->fd = open(s->tokens[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
		redirections++;
	}
	else if (!ft_strncmp(s->tokens[i], "<>", 3))
	{
		s->fd = open(s->tokens[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
		close(s->fd);
		s->fd = 1;
		s->fdi = open(s->tokens[i + 1], O_RDONLY, 0);
		redirections++;
	}
	else if (ft_strncmp(s->tokens[i], ">>", 3) == 0)
	{
		s->fd = open(s->tokens[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
		redirections++;
	}
	if (s->fd < 0)
	{
		s->fd = 1;
		ft_putstr_fd("error", 2);
	}
	return (redirections);
}

int	check_redirections(t_minishell *s)
{
	int		i;
	int		redirections;

	redirections = 0;
	i = 0;
	while (s->tokens[i])
	{
		redirections = output_redirections(s, i, redirections);
		i++;
		if (s->fd != 1 && s->tokens[i] && (!ft_strncmp(s->tokens[i], ">", 2) || \
			!ft_strncmp(s->tokens[i], ">>", 3)))
			close(s->fd);
	}
	if (redirections)
		delete_redirections(s, redirections, i);
	if (check_in_redirections(s) == -1)
		return (-1);
	return (0);
}
