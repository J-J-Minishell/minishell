#include "../../includes/minishell.h"

void	check_actual_dir(t_minishell *s)
{
	char	*tmp;
	char	*actual_dir;

	tmp = ft_strjoin("/", s->tokens[0]);
	actual_dir = ft_strjoin(s->pwd, tmp);
	tmp = ft_free_ptr(tmp);
	s->command_path = actual_dir;
}

void	ft_get_path(t_minishell *s)
{
	char	**paths;
	char	*complete_path;
	char	*tmp;
	char	*path;

	if (s->tokens[0] && (s->tokens[0][0] == '.' || s->tokens[0][0] == '/'))
		return (ft_abs_or_rel_path(s));
	path = ft_get_env_var_content(s, "PATH");
	if (path == NULL)
		return (check_actual_dir(s));
	else
	{
		paths = ft_split(path, ':');
		path = ft_free_ptr(path);
		tmp = ft_check_dir(s, paths);
		if (!tmp)
		{
			paths = ft_free_matrix(paths);
			return (check_actual_dir(s));
		}
		complete_path = ft_strjoin(tmp, "/");
		paths = ft_free_matrix(paths);
		s->command_path = ft_strjoin(complete_path, s->tokens[0]);
		complete_path = ft_free_ptr(complete_path);
	}
}

char	*ft_check_dir(t_minishell *s, char **paths)
{
	int				i;
	DIR				*dir;
	struct dirent	*sd;

	i = -1;
	while (paths[++i])
	{
		dir = opendir(paths[i]);
		if (dir)
		{
			sd = readdir(dir);
			while (dir && sd)
			{
				if (!(ft_strncmp(sd->d_name, s->tokens[0], \
					(strlen(s->tokens[0]) + 1))))
				{
					closedir(dir);
					return (paths[i]);
				}
				sd = readdir(dir);
			}
			closedir(dir);
		}
	}
	return (NULL);
}

void	ft_rel_back_path(t_minishell *s)
{
	int		len;
	int		i;
	int		backsteps;
	char	*tmp;

	i = 0;
	backsteps = 0;
	while (ft_strnstr(s->tokens[0] + i, "../", 3))
	{
		backsteps++;
		i += 3;
	}
	len = ft_strlen(s->pwd);
	while (backsteps > 0)
	{
		if (s->pwd[len - 1] == '/')
			backsteps--;
		len--;
	}
	tmp = ft_substr(s->pwd, 0, len + 1);
	s->command_path = ft_strjoin(tmp, s->tokens[0] + i);
	ft_free_ptr(tmp);
}

void	ft_abs_or_rel_path(t_minishell *s)
{
	if (s->tokens[0][0] == '/')
		s->command_path = ft_strdup(s->tokens[0]);
	else if (s->tokens[0][0] == '.' && s->tokens[0][1] == '/')
		s->command_path = ft_strjoin(s->pwd, s->tokens[0] + 1);
	else if (s->tokens[0][0] == '.' && s->tokens[0][1] == '.'
		&& s->tokens[0][2] == '/')
		ft_rel_back_path(s);
}
