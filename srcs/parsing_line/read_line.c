#include "../../includes/minishell.h"

void	signal_out(t_minishell *s, char **tmp)
{
	if (tmp)
		tmp = ft_free_matrix(tmp);
	ft_putstr_fd("\033[2D\033[0K", 2);
	ft_putstr_fd("logout\n", 2);
	ft_clean_up(s);
	exit(0);
}

/*
** si existe line y no es una cadena vacia("") tiene que borrar un carácter y los dos carácteres de delete "^?",
** si no, borra sólo los dos del delete, excepto si es "¡" o "º" que se guardan como si fuesen
** dos caracteres (-62 y -95 para "¡" y -70 para "º").
** dentro del if guarda en tmp = line menos un caracter y llama a add_history_cmd() 
*/
void	delete_char(t_minishell *s, int index)
{
	char	*tmp;
	int		len;

	len = ft_strlen(line);
	if (line && len)
	{
		if (len > 1 && line[len - 2] == -62 && (line[len - 1] == -95 || \
			line[len - 1] == -70))
			tmp = ft_substr(line, 0, len - 2);
		else
			tmp = ft_substr(line, 0, len - 1);
		free(line);
		line = tmp;
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

/*
** si el index != s->n_cmds (significa que has salido del bucle en un history_cmd) hace free de ese history_cmd
** y hace una copia del mismo history_cmd antiguo, sin haberlo modificado. si line no es una cadena vacía añade
** una posición en history_cmds con el comando que haya en line. (es para que no añada un history_cmd de una cadena vacía ("")).
** si no existe line y c == salto de línea (pulsar enter sin haber escrito nada) copia en line una string vacía (es para que
** en el main no entre en ft_process_line()).
** si line no es una cadena vacia (sirve por si has escrito algo, lo borras todo y pulsas enter) añade
** una posición en history_cmds con el comando que haya en line.
** al final hace el ft_strtrim para quitar los espacios al principio y al final de line.
*/
void	ft_read_line2(t_minishell *s, char **tmp, int index, char c)
{
	char	*tmp1;

	if (index != s->n_cmds)
	{
		free(s->history_cmds[index]);
		s->history_cmds[index] = ft_strdup(tmp[index]);
		if (line[0] != '\0')
		{
			s->history_cmds = add_new_pos_matrix(s->history_cmds, line);
			s->n_cmds++;
		}
	}
	else if (!line && c == '\n')
		line = ft_strdup("");
	else if (line[0] != '\0')
	{
		s->history_cmds = add_new_pos_matrix(s->history_cmds, line);
		s->n_cmds++;
	}
	s->new_hist_cmd = ft_free_ptr(s->new_hist_cmd);
	tmp1 = ft_strtrim(line, " ");
	free(line);
	line = tmp1;
}

/*
** copia la matriz s->history_cmds en tmp.
** como se ha cambiado el termios de la terminal la funcion read() lee carácter por carácter.
** si el carácter leído no es un salto de linea o un ctrl^D en una linea NULL o vacía (ej: si escribes algo
** y haces ctrl^D no hace nada porque existe line) entra dentro del while.
** si no existe line (unico caso al hacer ctrl^C) index se iguala al numero de history_cmds y se borra el comando actual
** al hacer ctrl^D escribe en la terminal "^D" entonces se borran los dos últimos carácteres. si no se añade a line.
** si pulsas la tecla delete(127) entra en delete_char().
** la función ft_str_is_printable_ascii() es para que sólo se guarde en los history_cmds los carácteres imprimibles del
** código ascii (para que no guarde los carácteres de las flechas o de señales).
*/
void	ft_read_line(t_minishell *s)
{
	char	**tmp;
	char	c;
	int		index;

	index = s->n_cmds;
	tmp = cpy_matrix(s->history_cmds, s->n_cmds);
	while (read(0, &c, 1) && c != '\n' && (c != 4 || (line && line[0] != '\0')))
	{
		if (!line && (index = s->n_cmds))
			s->new_hist_cmd = ft_free_ptr(s->new_hist_cmd);
		if (c == 4)
			ft_putstr_fd("\033[2D\033[0K", 2);
		else
			add_char_to_line(s, c);
		index = choose_history_cmd(s, ft_strlen(line), index);
		if (c == 127)
			delete_char(s, index);
		if (ft_str_is_printable_ascii(line))
			add_history_cmd(s, index);
	}
	if (c == 4)
		signal_out(s, tmp);
	ft_read_line2(s, tmp, index, c);
	if (tmp)
		tmp = ft_free_matrix(tmp);
}
