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
		s->exit_status = 0;
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
			tmp = ft_strjoin(s->env[i] + 5, s->tokens[1] + 1);
		free(s->tokens[1]);
		s->tokens[1] = i >= 0 ? tmp : ft_strdup(s->home);
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
		else
			ft_putstr_fd("-bash: cd: OLDPWD not set", 0);
	}
}

void	blt_cd(t_minishell *s)
{
	int		i;

	if (s->tokens[1])
	{
		special_chars_cd(s);
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
	else
	{
		i = ft_find_env_var(s, "HOME=");
		if (i >= 0)
			if (chdir(s->env[i] + 5) == 0)
				change_pwd(s);
	}
}
