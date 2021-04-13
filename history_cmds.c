#include "minishell.h"

/*
** como los carácteres de la flecha se guardan en line se guarda en tmp todo menos los carácteres de la flecha.
** y se borran de la terminal los carácteres de la flecha.
** en resumen esta función deja todo tal cual estaba, pulsar una flecha izq o der no hace nada.
*/
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

/*
** borra toda la línea del terminal.
** si existe history_cmds[index] te copia en line ese history_cmd.
** si index == n_cmds (significa que no estás en ningún history_cmds si no en el comando actual)
** borra line (porque tiene los carácteres de la flecha)
** y si existe new_hist_cmd lo pone en la terminal y hace una copia en line.
*/
void	write_history_cmd(t_minishell *s, int index)
{
	ft_putstr_fd("\033[1000D\033[0K", 2);
	write(1, "$> ", 3);
	if (s->history_cmds && s->history_cmds[index])
	{
		line = ft_free_ptr(line);
		ft_putstr_fd(s->history_cmds[index], 1);
		line = ft_strdup(s->history_cmds[index]);
	}
	else if (index == s->n_cmds)
	{
		line = ft_free_ptr(line);
		if (s->new_hist_cmd)
		{
			ft_putstr_fd(s->new_hist_cmd, 1);
			line = ft_strdup(s->new_hist_cmd);
		}
	}
}

/*
** esta función sólo hace algo cuando has pulsado alguna flecha.
** FLECHA ARRIBA: entra en el primer if y resta uno a index para pasar al anterior history_cmd.
** FLECHA ABAJO: entra en el else if y suma uno a index para pasar al siguiente history_cmd.
** FLECHA IZQ O DER: entra en la función left_right_arrows.
** return index para devolver el índice por si se ha modificado. 
*/
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
