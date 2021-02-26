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

void	blt_cd(t_minishell *s)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	if (s->tokens[1])
	{
		if (s->tokens[1][0] == '~')
		{
			tmp = ft_get_env_var_content(s, "HOME=");
			tmp2 = ft_strjoin(tmp, s->tokens[1] + 1);
			free(s->tokens[1]);
			s->tokens[1] = tmp2;
			tmp = ft_free_ptr(tmp);
		}
		if (chdir(s->tokens[1]) == 0)
			change_pwd(s);
		else
		{
			tmp = ft_strjoin("cd: no such file or directory: ", s->tokens[1]);
			ft_putstr_fd(tmp, 0);
			write (0, "\n", 1);
			tmp = ft_free_ptr(tmp);
		}
	}
	else
	{
		i = ft_find_env_var(s, "HOME=");
		if (chdir(s->env[i] + 5) == 0)
			change_pwd(s);
	}
}
