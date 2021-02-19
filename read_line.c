#include "minishell.h"

void	ft_read_line(t_minishell *s)
{
	char *tmp;
	char *line_joined;

	get_next_line(0, &s->line);
	while (1)
	{
		if (s->line[ft_strlen(s->line) - 1] == 92)
		{
			write(1, "\n> ", 3);
			get_next_line(0, &tmp);
			line_joined = ft_strjoin(s->line, tmp);
			free(s->line);
			free(tmp);
			s->line = line_joined;
		}
		else
			break;
	}
	tmp = ft_strtrim(s->line, "; ");
	free(s->line);
	s->line = tmp;
}
