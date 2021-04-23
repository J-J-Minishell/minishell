#include "../../includes/minishell.h"

void	left_right_arrow(int len)
{
	char	*tmp;

	tmp = ft_substr(g_ln, 0, len - 3);
	g_ln = ft_free_ptr(g_ln);
	g_ln = tmp;
	if (len == 3)
		g_ln = ft_free_ptr(g_ln);
	ft_putstr_fd("\033[4D\033[0K", 2);
}

void	add_history_cmd(t_minishell *s, int index)
{
	if (index == s->n_cmds)
	{
		free(s->new_hist_cmd);
		s->new_hist_cmd = ft_strdup(g_ln);
	}
	else
	{
		free(s->history_cmds[index]);
		s->history_cmds[index] = ft_strdup(g_ln);
	}
}

void	write_history_cmd(t_minishell *s, int index)
{
	ft_putstr_fd("\033[1000D\033[0K", 2);
	write(1, "$> ", 3);
	if (s->history_cmds && s->history_cmds[index])
	{
		g_ln = ft_free_ptr(g_ln);
		ft_putstr_fd(s->history_cmds[index], 1);
		g_ln = ft_strdup(s->history_cmds[index]);
	}
	else if (index == s->n_cmds)
	{
		g_ln = ft_free_ptr(g_ln);
		if (s->new_hist_cmd)
		{
			ft_putstr_fd(s->new_hist_cmd, 1);
			g_ln = ft_strdup(s->new_hist_cmd);
		}
	}
}

int	choose_history_cmd(t_minishell *s, int len, int index)
{
	if (len >= 3 && \
		g_ln[len - 3] == 27 && g_ln[len - 2] == 91 && g_ln[len - 1] == 65)
	{
		if (index > 0)
			index--;
		write_history_cmd(s, index);
	}
	else if (len >= 3 && \
		g_ln[len - 3] == 27 && g_ln[len - 2] == 91 && g_ln[len - 1] == 66)
	{
		if (index < s->n_cmds)
			index++;
		write_history_cmd(s, index);
	}
	else if (len >= 3 && g_ln[len - 3] == 27 && g_ln[len - 2] == 91 && \
		(g_ln[len - 1] == 67 || g_ln[len - 1] == 68))
		left_right_arrow(len);
	return (index);
}
