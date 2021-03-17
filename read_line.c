#include "minishell.h"

void	signal_out(t_minishell *s)
{
	ft_putstr_fd("\nlogout\n", 2);
	ft_clean_up(s);
	exit(0);
}

void	ft_read_line(t_minishell *s)
{
	char *tmp;
	char *line_joined;

	if (!get_next_line(0, &s->line))
		signal_out(s);
	while (1)
	{
		if (ft_strlen(s->line) && s->line[ft_strlen(s->line) - 1] == 92)
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
