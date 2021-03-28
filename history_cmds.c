#include "minishell.h"

void	left_right_arrow(t_minishell *s, int len)
{
	char	*tmp;

	tmp = ft_substr(line, 0, len - 3);
	line = ft_free_ptr(line);
	line = tmp;
	if (len == 3)
		line = ft_free_ptr(line);
	ft_putstr_fd("\033[4D\033[0K", 2);
}

void	add_history_cmd(t_minishell *s, int index)
{
	if (index == s->n_cmds)
	{
		free(s->new_hist_cmd);
		s->new_hist_cmd = ft_strdup(line);
	}
	else
	{
		free(s->history_cmds[index]);
		s->history_cmds[index] = ft_strdup(line);
	}
}

void	write_history_cmd(t_minishell *s, int index)
{
	ft_putstr_fd("\033[100D\033[0K", 2);
	write(1, "$> ", 3);
	if (s->history_cmds && s->history_cmds[index])
	{
		line = ft_free_ptr(line);
		ft_putstr_fd(s->history_cmds[index], 1);
		line = ft_strdup(s->history_cmds[index]);
	}
	else if (index == s->n_cmds)
	{
		if (!line)
			s->new_hist_cmd = ft_free_ptr(s->new_hist_cmd);
		else if (s->new_hist_cmd)
		{
			line = ft_free_ptr(line);
			ft_putstr_fd(s->new_hist_cmd, 1);
			line = ft_strdup(s->new_hist_cmd);
		}
		else
		{
			line = ft_free_ptr(line);
			ft_putstr_fd("", 1);
		}
	}
}

int		choose_history_cmd(t_minishell *s, int len, int index)
{
	if (len >= 3 &&
		line[len - 3] == 27 && line[len - 2] == 91 && line[len - 1] == 65)
	{
		if (index > 0)
			index--;
		write_history_cmd(s, index);
	}
	else if (len >= 3 &&
		line[len - 3] == 27 && line[len - 2] == 91 && line[len - 1] == 66)
	{
		if (index < s->n_cmds)
			index++;
		write_history_cmd(s, index);
	}
	else if (len >= 3 && line[len - 3] == 27 && line[len - 2] == 91 &&
		(line[len - 1] == 67 || line[len - 1] == 68))
		left_right_arrow(s, len);
	return (index);
}
