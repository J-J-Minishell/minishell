#include "minishell.h"

void	change_pwd(t_minishell *s)
{
	int		i;
	char	*buf;
	size_t  size;

    size = 4096;
	i = ft_find_env_var(s, "PWD=");
	if (i >= 0)
	{
		buf = ft_strjoin("OLDPWD=", s->env[i] + 4);
		export_env_var(s, buf, 7);
		buf = ft_free_ptr(buf);
		s->env[i] = ft_free_ptr(s->env[i]);
		if (!(buf = malloc(size)))
			ft_print_error(s);
		while ((getcwd(buf, size) == NULL) && errno == ERANGE)
		{
			size = size + 4096;
			buf = ft_free_ptr(buf);
			if (!(buf = ft_realloc(NULL, size)))
				ft_print_error(s);
		}
		s->env[i] = ft_strjoin("PWD=", buf);
		buf = ft_free_ptr(buf);
	}
}

void	special_chars_cd(t_minishell *s)
{
	int		i;
	char	*tmp;

	if (s->tokens[1][0] == '~')
	{
		i = ft_find_env_var(s, "HOME=");
		if (i >= 0)
		{
			tmp = ft_strjoin(s->env[i] + 5, s->tokens[1] + 1);
			free(s->tokens[1]);
			s->tokens[1] = tmp;
		}
	}
	else if (s->tokens[1][0] == '-')
	{
		i = ft_find_env_var(s, "OLDPWD=");
		if (i >= 0)
		{
			free(s->tokens[1]);
			s->tokens[1] = ft_strdup(s->env[i] + 7);
			ft_putstr_fd(s->tokens[1], 0);
			write (0, "\n", 1);
		}
	}
}

int		check_arguments(t_minishell *s)
{
	int i;

	i = 1;
	while (s->tokens[i])
		i++;
	if (i >= 4)
		ft_putstr_fd("cd: too many arguments\n", 0);
	else if (i == 3)
	{
		ft_putstr_fd("cd: string not in pwd: ", 0);
		ft_putstr_fd(s->tokens[1], 0);
		write (0, "\n", 1);
	}
	else
		return (0);
	return (1);
}

void	blt_cd(t_minishell *s)
{
	int		i;

	if (s->tokens[1])
	{
		if (check_arguments(s))
			return ;
		special_chars_cd(s);
		if (chdir(s->tokens[1]) == 0)
			change_pwd(s);
		else
		{
			ft_putstr_fd("cd: no such file or directory: ", 0);
			ft_putstr_fd(s->tokens[1], 0);
			write (0, "\n", 1);
		}
	}
	else
	{
		i = ft_find_env_var(s, "HOME=");
		if (i >= 0)
			if (chdir(s->env[i] + 5) == 0)
				change_pwd(s);
	}
}
