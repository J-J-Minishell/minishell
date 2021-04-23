#include "../../includes/minishell.h"

/*
** Function in charge of get the characters inside quotes block printed.
*/

int	quotes(t_minishell *s, int i, int j)
{
	int		single_q;
	int		double_q;

	double_q = (s->tokens[i][j] == '"');
	single_q = (s->tokens[i][j] == '\'');
	while (s->tokens[i][j] && (double_q || single_q))
	{
		j++;
		double_q *= (s->tokens[i][j] != '"');
		single_q *= (s->tokens[i][j] != '\'');
		if (double_q || single_q)
		{
			if (s->tokens[i][j] == '\\' && j > 0 && s->tokens[i][j - 1] == '\\')
				j++;
			write(s->fd, s->tokens[i] + j, 1);
		}
	}
	return (j);
}

/*
** This function search in each token passed to echo command if there is the
** '~' character alone. If it is found the function get the character
** replaced for the home path stored in the HOME variable.
*/

void	check_special_tokens(t_minishell *s)
{
	int		i;
	char	*tmp;
	int		j;

	i = 1;
	while (s->tokens[i])
	{
		if (s->tokens[i][0] == '~' && s->tokens[i][1] == '\0')
		{
			tmp = ft_get_env_var_content(s, "HOME");
			if (tmp)
			{
				ft_free_ptr(s->tokens[i]);
				s->tokens[i] = ft_strdup(tmp);
			}
		}
		i++;
	}
}

/*
** This function checks if there should be a newline printed or not. When there
** is a '-' character at the beginning of the token and it is followed by one
** or more 'n' characters the flag new line is deactivated.
*/

int	flag_newline(t_minishell *s, char *token)
{
	int	i;
	int	j;
	int	newline;

	newline = FALSE;
	i = 0;
	if (token[i] == '-' && token[i + 1] == 'n')
	{
		newline = TRUE;
		while (token[++i] != '\0')
		{
			if (token[i] != 'n')
			{
				newline = FALSE;
				break ;
			}
		}
		if (newline == TRUE)
			return (newline);
	}
	return (newline);
}

/*
** This function is in charge of print the arguments passed to echo command.
** If double or single quotes are present in an argument it calls quotes()
** function to take care of that. This function also consider the case when
** there is a '\'. The next character next to it will not be printed. If the
** character is not next to a counterbar it will be printed.
** And finally, if there are more arguments a space will be printed.
*/

void	print_tokens(t_minishell *s, int i)
{
	int	j;

	j = -1;
	while (s->tokens[i][++j])
	{
		if (s->tokens[i][j] == '"' || s->tokens[i][j] == '\'')
			j = quotes(s, i, j);
		else if (s->tokens[i][j] != '\\')
			write(s->fd, s->tokens[i] + j, 1);
	}
	if (j && s->tokens[i + 1])
		write(s->fd, " ", 1);
}

/*
** This function starts calling check_special_tokens() in order to look if one
** of the tokens is '~'. In that case the token is replaced for HOME path. Then
** it checks if a new line should be printed at the end. In order to do that it
** calls the function flag_newline() that will set the flag newline. Next step
** is get the arguments to echo printed. Function print_tokens() will do that.
** And finaly it will print newline if the flag is active.
*/

void	cmd_echo(t_minishell *s)
{
	int		i;
	int		j;
	int		newline;

	check_special_tokens(s);
	newline = TRUE;
	i = 0;
	while (flag_newline(s, s->tokens[++i]))
		newline = FALSE;
	while (s->tokens[i])
	{
		print_tokens(s, i);
		i++;
	}
	if (newline)
		write(s->fd, "\n", 1);
	s->exit_status = 0;
}
