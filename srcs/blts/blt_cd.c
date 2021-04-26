#include "../../includes/minishell.h"

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

void	cd_with_arguments(t_minishell *s)
{
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
		special_chars_cd(s, NULL, 0);
	if (chdir(s->tokens[1]) == 0)
		change_pwd(s);
	else
	{
		printf("-bash: cd: %s: %s\n", s->tokens[1], strerror(errno));
		s->exit_status = 1;
	}
}

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
			printf("-bash: cd: HOME not set\n");
			s->exit_status = 1;
		}
	}
}
