#include "../../includes/minishell.h"

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

int	input_redirections(t_minishell *s, char *tmp)
{
	s->fdi = open(tmp, O_RDONLY, 0);
	if (s->fdi == -1)
	{
		if (tmp && tmp[0] == '\0')
			ft_putstr_fd("bash: ambiguous redirect\n", 2);
		else
		{
			ft_putstrs_fd("-bash: ", tmp, ": ", 2);
			ft_putstrs_fd(strerror(errno), "\n", 0, 2);
		}
		s->fdi = 0;
		s->exit_status = 1;
		return (1);
	}
	return (0);
}

int	check_in_redirections(t_minishell *s)
{
	int	i;
	int	redirections;

	i = 0;
	redirections = 0;
	while (s->tokens[i])
	{
		if (ft_strncmp(s->tokens[i], "<", 2) == 0)
		{
			if (input_redirections(s, ft_strtrim(s->tokens[i + 1], "\"'")))
				return (-1);
			redirections++;
		}
		i++;
	}
	if (redirections)
		delete_in_redirections(s, redirections, i);
	return (0);
}
