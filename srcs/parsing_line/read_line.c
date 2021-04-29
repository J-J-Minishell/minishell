#include "../../includes/minishell.h"

void	signal_out(t_minishell *s, char **tmp)
{
	if (tmp)
		tmp = ft_free_matrix(tmp);
	ft_putstr_fd("\033[2D\033[0K", 2);
	ft_putstr_fd("exit\n", 2);
	ft_clean_up(s);
	exit(s->exit_status);
}

void	delete_char(t_minishell *s, int index)
{
	char	*tmp;
	int		len;

	len = ft_strlen(g_ln);
	if (g_ln && len)
	{
		if (len > 1 && g_ln[len - 2] == -62 && (g_ln[len - 1] == -95 || \
			g_ln[len - 1] == -70))
			tmp = ft_substr(g_ln, 0, len - 2);
		else
			tmp = ft_substr(g_ln, 0, len - 1);
		free(g_ln);
		g_ln = tmp;
		ft_putstr_fd("\033[3D\033[0K", 2);
		add_history_cmd(s, index);
	}
	else
		ft_putstr_fd("\033[2D\033[0K", 2);
}

void	add_char_to_line(t_minishell *s, char c)
{
	char	*tmp;
	char	*str;

	str = malloc(sizeof(char) * 1 + 1);
	if (!str)
		ft_print_error(s);
	str[0] = c;
	str[1] = '\0';
	if (!g_ln && c != 127)
		g_ln = ft_strdup(str);
	else if (c != 127)
	{
		tmp = ft_strjoin(g_ln, str);
		free(g_ln);
		g_ln = tmp;
	}
	str = ft_free_ptr(str);
}

void	ft_read_line2(t_minishell *s, char **tmp, int index, char c)
{
	char	*tmp1;

	if (index != s->n_cmds)
	{
		free(s->history_cmds[index]);
		s->history_cmds[index] = ft_strdup(tmp[index]);
		if (g_ln[0] != '\0')
		{
			s->history_cmds = add_new_pos_matrix(s->history_cmds, g_ln);
			s->n_cmds++;
		}
	}
	else if (!g_ln && c == '\n')
		g_ln = ft_strdup("");
	else if (g_ln[0] != '\0')
	{
		s->history_cmds = add_new_pos_matrix(s->history_cmds, g_ln);
		s->n_cmds++;
	}
	s->new_hist_cmd = ft_free_ptr(s->new_hist_cmd);
	tmp1 = ft_strtrim(g_ln, " ");
	free(g_ln);
	g_ln = tmp1;
}

void	ft_read_line(t_minishell *s, int index, char c, char **tmp)
{
	tmp = cpy_matrix(s->history_cmds, s->n_cmds);
	while (read(0, &c, 1) && c != '\n' && (c != 4 || (g_ln && g_ln[0] != '\0')))
	{
		check_signal(s, 0);
		if (!g_ln)
		{
			index = s->n_cmds;
			s->new_hist_cmd = ft_free_ptr(s->new_hist_cmd);
		}
		if (c == 4)
			ft_putstr_fd("\033[2D\033[0K", 2);
		else
			add_char_to_line(s, c);
		index = choose_history_cmd(s, ft_strlen(g_ln), index);
		if (c == 127)
			delete_char(s, index);
		if (ft_str_is_printable_ascii(g_ln))
			add_history_cmd(s, index);
	}
	check_signal(s, 0);
	if (c == 4)
		signal_out(s, tmp);
	ft_read_line2(s, tmp, index, c);
	if (tmp)
		tmp = ft_free_matrix(tmp);
}
