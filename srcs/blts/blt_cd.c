#include "../../includes/minishell.h"

/*
** This function is the second part of the change_pwd() function. Here getcwd()
** is called. But a memory block should be allocated to contain the buffer
** where the path will be saved. Realloc is used in case the buffer would need
** more space.
*/

char	*get_cwd(t_minishell *s, int size)
{
	char	*tmp;
	char	*buf;

	buf = malloc(size);
	if (!buf)
		ft_print_error(s);
	tmp = getcwd(buf, size);
	while (tmp && errno == ERANGE)
	{
		size = size + 4096;
		buf = ft_free_ptr(buf);
		buf = ft_realloc(NULL, size);
		if (!buf)
			ft_print_error(s);
		tmp = getcwd(buf, size);
	}
	return (buf);
}

/*
** When the current directory is changed by cd command, it is necessary to
** update the PWD environment variable. In order to do that, this function
** first save the the actual value in OLDPWD and then calls get_cwd() to
** save the new value in PWD.
*/

void	change_pwd(t_minishell *s)
{
	int		i;
	char	*buf;
	size_t	size;

	size = 4096;
	i = ft_find_env_var(s, "PWD=");
	if (i >= 0)
	{
		buf = ft_strjoin("OLDPWD=", s->env[i] + 4);
		export_env_var(s, buf, 7);
		buf = ft_free_ptr(buf);
		s->env[i] = ft_free_ptr(s->env[i]);
		buf = get_cwd(s, size);
		s->env[i] = ft_strjoin("PWD=", buf);
		buf = ft_free_ptr(buf);
		s->exit_status = 0;
	}
}

/*
** This functions checks if the argument for cd command is one of this two
** cases: '~' or '-'. If the first one is found, it changes the token to
** put the HOME path instead '~'. If HOME environment variable does not
** exists, it takes the value from other variable the program use to stores it.
** If the '-' character is found, the function uses the variable OLDPWD to
** get the path of the previous working directory and make the substitution.
** If OLDPWD doesn't exist an error message is printed.
*/

void	special_chars_cd(t_minishell *s, char *tmp, int i)
{
	if (s->tokens[1][0] == '~')
	{
		i = ft_find_env_var(s, "HOME=");
		if (i >= 0)
			tmp = ft_strjoin(s->env[i] + 5, s->tokens[1] + 1);
		free(s->tokens[1]);
		if (i >= 0)
			s->tokens[1] = tmp;
		else
			s->tokens[1] = ft_strdup(s->home);
	}
	else if (s->tokens[1][0] == '-')
	{
		i = ft_find_env_var(s, "OLDPWD=");
		if (i >= 0)
		{
			free(s->tokens[1]);
			s->tokens[1] = ft_strdup(s->env[i] + 7);
			ft_putstr_fd(s->tokens[1], 1);
			write (0, "\n", 1);
		}
		else
			ft_putstr_fd("-bash: cd: OLDPWD not set", 0);
	}
}

/*
** This function first checks if the argument is surrounded by quotes or double
** quotes. If that is the case, it removes the quotes before continuing the
** execution. If there are no quotes, goes to check if the argument is one of
** the special cases, like '~' that changes to HOME directory, or '-' that
** changes to the previous directory in case there is one. Function
** special_chars_cd() changes token with the special character for the
** corresponding path.
** Then, function continues trying to make the working directory change using
** the system function chdir(). This function returns 0 in case of success or
** -1 in case of error. In case of error, message is printed and exit status is
** set properly. In case of success function change_pwd() is called.
*/

void	cd_with_arguments(t_minishell *s)
{
	int		i;
	char	*tmp;

	if (s->tokens[1][0] == '"' || s->tokens[1][0] == '\'')
	{
		if (s->tokens[1][0] == '"')
			tmp = ft_strtrim(s->tokens[1], "\"");
		else
			tmp = ft_strtrim(s->tokens[1], "\'");
		ft_free_ptr(s->tokens[1]);
		s->tokens[1] = tmp;
	}
	else
		special_chars_cd(s, tmp, i);
	if (chdir(s->tokens[1]) == 0)
		change_pwd(s);
	else
	{
		ft_putstr_fd("-bash: cd: ", 0);
		ft_putstr_fd(s->tokens[1], 0);
		ft_putstr_fd(": No such file or directory", 0);
		write (0, "\n", 1);
		s->exit_status = 1;
	}
}

/*
** The function blt_cd() implements the built-in command 'cd' in our program.
** It has two main blocks. One that takes care of those cases in which there is
** no arguments, changing the work path to the HOME directory. If HOME variable
** exists there is no problem but, in other case, prints an error and set the
** exit status properly.
** The other, when there is an argument, it calls cd_with_arguments() to get
** the job done.
*/

void	blt_cd(t_minishell *s)
{
	int		i;

	if (s->tokens[1])
		cd_with_arguments(s);
	else
	{
		i = ft_find_env_var(s, "HOME=");
		if (i >= 0)
		{
			if (chdir(s->env[i] + 5) == 0)
				change_pwd(s);
		}
		else
		{
			ft_putstr_fd("-bash: cd: HOME not set", 0);
			s->exit_status = 1;
		}
	}
}
