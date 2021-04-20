#include "../../includes/minishell.h"

/*
** Function ft_get_path() first saves in a variable the content of the
** environment $PATH. Then split all the paths contained in that
** variable and check every one of them searching for the command that
** needs to be executed. If the command is founded on one of those paths
** the complete path of the command is saved in s->command_path variable.
** Other than that, s->command_path remains pointing to NULL.
*/

void	ft_get_path(t_minishell *s)
{
	char	**paths;
	char	*complete_path;
	char	*temp;
	char	*path;

	if (s->tokens[0] && (s->tokens[0][0] == '.' || s->tokens[0][0] == '/'))
		ft_abs_or_rel_path(s);
	else
	{
		path = ft_get_env_var_content(s, "PATH");
		//ft_get_env_path(s);
		paths = ft_split(path, ':');
		temp = ft_check_dir(s, paths);
		complete_path = ft_strjoin(temp, "/");
		paths = ft_free_matrix(paths);
		s->command_path = ft_strjoin(complete_path, s->tokens[0]);
		complete_path = ft_free_ptr(complete_path);
		path = ft_free_ptr(path);
	}
}

/*
** Function ft_check_dir() opens, one by one, the directories where the
** executable commands could be founded (those included on $PATH evironment
** variable), and search there for the actual command thar should be executed.
** When the comand is founded, this function returns the appropiate path.
** Other than that, returns NULL pointer.
*/

char	*ft_check_dir(t_minishell *s, char **paths)
{
	DIR				*dir;
	struct dirent	*sd;

	while (*paths)
	{
		dir = opendir(*paths);
		while ((sd = readdir(dir)))
		{
			if (!(ft_strncmp(sd->d_name, s->tokens[0],
				(strlen(s->tokens[0]) + 1))))
			{
				closedir(dir);
				return(*paths);
			}
		}
		closedir(dir);
		*paths++;
	}
	return (NULL);
}

void		ft_rel_back_path(t_minishell *s)
{
	int		len;
	int		i;
	int		backsteps;
	char	*pwd;
	char	*tmp;

	i = 0;
	backsteps = 0;
	while (ft_strnstr(s->tokens[0] + i, "../", 3))
	{
		backsteps++;
		i += 3;
	}
	pwd = ft_get_env_var_content(s, "PWD");
	len = ft_strlen(pwd);
	while (backsteps > 0)
	{
		if (pwd[len - 1] == '/')
			backsteps--;
		len--;
	}
	tmp = ft_substr(pwd, 0, len + 1);
	s->command_path = ft_strjoin(tmp, s->tokens[0] + i);
	ft_free_ptr(tmp);
	ft_free_ptr(pwd);
}

void		ft_abs_or_rel_path(t_minishell *s)
{
	char	*temp;

	temp = ft_get_env_var_content(s, "PWD");
	if (s->tokens[0][0] == '/')
		s->command_path = ft_strdup(s->tokens[0]);
	else if (s->tokens[0][0] == '.' && s->tokens[0][1] == '/')
		s->command_path = ft_strjoin(temp, s->tokens[0] + 2);
	else if (s->tokens[0][0] == '.' && s->tokens[0][1] == '.'
		&& s->tokens[0][2] == '/')
		ft_rel_back_path(s);
	ft_free_ptr(temp);
}
