#include "minishell.h"

void	signal_out(t_minishell *s, char **tmp)
{
	if (tmp)
		tmp = ft_free_matrix(tmp);
	ft_putstr_fd("\033[2D\033[0K", 2);
	ft_putstr_fd("logout\n", 2);
	ft_clean_up(s);
	exit(0);
}

void	delete_char(t_minishell *s)
{
	char	*tmp;

	if (line && ft_strlen(line))
	{
		if (ft_strlen(line) == 1)
			line = ft_free_ptr(line);
		else
		{
			tmp = ft_substr(line, 0, ft_strlen(line) - 1);
			free(line);
			line = tmp;
		}
		ft_putstr_fd("\033[3D\033[0K", 2);
	}
	else
		ft_putstr_fd("\033[2D\033[0K", 2);
}

void	add_char_to_line(t_minishell *s, char c)
{
	char	*tmp;
	char	*str;

	if (!(str = malloc(sizeof(char) * 1 + 1)))
		ft_print_error(s);
	str[0] = c;
	str[1] = '\0';
	if (!line && c != 127)
		line = ft_strdup(str);
	else if (c != 127)
	{
		tmp = ft_strjoin(line, str);
		free(line);
		line = tmp;
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
		s->history_cmds = add_new_pos_matrix(s->history_cmds, line);
		s->n_cmds++;
	}
	else if (!line && c == '\n')
		line = ft_strdup("");
	else
	{
		s->history_cmds = add_new_pos_matrix(s->history_cmds, line);
		s->n_cmds++;
	}
	s->new_hist_cmd = ft_free_ptr(s->new_hist_cmd);
	tmp1 = ft_strtrim(line, "; ");
	free(line);
	line = tmp1;
}

void	ft_read_line(t_minishell *s)
{
	char	**tmp;
	char	c;
	int		index;

	index = s->n_cmds;
	tmp = cpy_matrix(s->history_cmds, s->n_cmds);
	while (read(0, &c, 1) && c != '\n' && (c != 4 || line))
	{
		if (index != s->n_cmds && !line)
			index = s->n_cmds;
		if (c == 4)
			ft_putstr_fd("\033[2D\033[0K", 2);
		else
			add_char_to_line(s, c);
		index = choose_history_cmd(s, ft_strlen(line), index);
		if (c == 127)
			delete_char(s);
		if (ft_str_is_printable_ascii(line))
			index = add_history_cmd(s, index);
	}
	if (c == 4)
		signal_out(s, tmp);
	ft_read_line2(s, tmp, index, c);
	if (tmp)
		tmp = ft_free_matrix(tmp);
}