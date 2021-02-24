#include "minishell.h"

void    ft_get_path(t_minishell *s)
{
    char    **paths;
    char    *complete_path;
    char    *temp;
    ft_get_env_path(s);
    paths = ft_split(s->path, ':');
    temp = ft_check_dir(s, paths);
    complete_path = ft_strjoin(temp, "/");
    paths = ft_free_matrix(paths);
    s->command_path = ft_strjoin(complete_path, s->tokens[0]);
    complete_path = ft_free_ptr(complete_path);
}

char    *ft_check_dir(t_minishell *s, char **paths)
{
    DIR             *dir;
    struct dirent   *sd;
    while (*paths)
    {
        dir = opendir(*paths);
        while ((sd = readdir(dir)))
        {
            if (!(ft_strncmp(sd->d_name, s->tokens[0], (strlen(s->tokens[0]) + 1))))
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

void    ft_get_env_path(t_minishell *s)
{
    int     i;
    int     j;
    j = 0;
    while ((s->env)[j])
    {
        if (!ft_strncmp("PATH=", (s->env)[j], 5))
        {
            if (!(s->path = malloc(ft_strlen((s->env)[j]) + 1)))
                ft_print_error(s);
            i = 0;
            while (((s->env)[j])[i + 5] != '\0')
            {
                s->path[i] = ((s->env)[j])[i + 5];
                i++;
            }
            s->path[i] = '\0';
            break ;
        }
        else
            j++;
    }
}
