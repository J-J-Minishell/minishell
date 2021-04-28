#include "../../includes/minishell.h"

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

int	special_chars_cd_2(t_minishell *s)
{
	int	i;

	i = ft_find_env_var(s, "OLDPWD=");
	if (i >= 0)
	{
		free(s->tokens[1]);
		s->tokens[1] = ft_strdup(s->env[i] + 7);
		ft_putstrs_fd(s->tokens[1], "\n", 0, 1);
	}
	else
	{
		ft_putstr_fd("-bash: cd: OLDPWD not set\n", 2);
		s->exit_status = 1;
		return (-1);
	}
	return (0);
}

int	special_chars_cd(t_minishell *s)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
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
		return (special_chars_cd_2(s));
	return (0);
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
		if (special_chars_cd(s) == -1)
			return ;
	if (chdir(s->tokens[1]) == 0)
		change_pwd(s);
	else
	{
		ft_putstrs_fd("-bash: cd: ", s->tokens[1], ": ", 2);
		ft_putstrs_fd(strerror(errno), "\n", 0, 2);
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
			ft_putstr_fd("-bash: cd: HOME not set\n", 2);
			s->exit_status = 1;
		}
	}
}
