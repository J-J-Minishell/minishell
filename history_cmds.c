#include "minishell.h"

int		add_history_cmd(t_minishell *s, int index)
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
	return (index);
}

void	write_history_cmd(t_minishell *s, int index)
{
	ft_putstr_fd("\033[100D\033[0K", 2);
	write(1, "$> ", 3);
	line = ft_free_ptr(line);
	if (s->history_cmds && s->history_cmds[index])
	{
		ft_putstr_fd(s->history_cmds[index], 1);
		line = ft_strdup(s->history_cmds[index]);
	}
	else if (index == s->n_cmds)
	{
		if (!line)
			s->new_hist_cmd = ft_free_ptr(s->new_hist_cmd);
		else if (s->new_hist_cmd)
		{
			ft_putstr_fd(s->new_hist_cmd, 1);
			line = ft_strdup(s->new_hist_cmd);
		}
		else
			ft_putstr_fd("", 1);
	}
}

int		choose_history_cmd(t_minishell *s, int len, int index)
{
	if (len >= 3 && line[len - 3] == 27 && line[len - 2] == 91 && line[len - 1] == 65)
	{
		if (index > 0)
			index--;
		write_history_cmd(s, index);
	}
	else if (len >= 3 && line[len - 3] == 27 && line[len - 2] == 91 && line[len - 1] == 66)
	{
		if (index < s->n_cmds)
			index++;
		write_history_cmd(s, index);
	}
	return (index);
}
