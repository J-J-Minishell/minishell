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

int	output_redirections(t_minishell *s, int i, char *tmp)
{
	if (!ft_strncmp(s->tokens[i], ">", 2))
		s->fd = open(tmp, O_RDWR | O_CREAT | O_TRUNC, 0666);
	else if (!ft_strncmp(s->tokens[i], "<>", 3))
	{
		s->fd = open(tmp, O_RDWR | O_CREAT | O_TRUNC, 0666);
		close(s->fd);
		s->fd = 1;
		s->fdi = open(tmp, O_RDONLY, 0);
	}
	else if (!ft_strncmp(s->tokens[i], ">>", 3))
		s->fd = open(tmp, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (tmp)
		free(tmp);
	if (s->fd < 0)
	{
		s->fd = 1;
		if (tmp && tmp[0] == '\0')
			ft_putstr_fd("bash: ambiguous redirect\n", 2);
		else
			ft_putstrs_fd("-bash: ", tmp, ": Permission denied\n", 2);
		return (1);
	}
	return (0);
}

int	check_redirections(t_minishell *s)
{
	int		i;
	int		redirections;

	redirections = 0;
	i = 0;
	while (s->tokens[i])
	{
		if (!ft_strncmp(s->tokens[i], "<>", 2) || \
		!ft_strncmp(s->tokens[i], ">", 3) || !ft_strncmp(s->tokens[i], ">>", 3))
		{
			if (output_redirections(s, i, ft_strtrim(s->tokens[i + 1], "\"'")))
				return (-1);
			redirections++;
		}
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
