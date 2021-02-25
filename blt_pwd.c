#include "minishell.h"

void    blt_pwd(t_minishell *s)
{
    int i;

    i = find_env_var(s, "PWD=");
    if (i >= 0)
    {
        ft_putstr_fd(s->env[i] + 4, 0);
        write(1, "\n", 1);
    }
}

//
//    --- LINUX VERSION ---
//
// void blt_pwd(t_minishell *s)
// {
//  int     i;
//  char    *pwd;
//  pwd = getcwd(NULL, 0);
//  ft_putstr_fd(buf, 0);
//  write(1, "\n", 1);
//  free(pwd);
// } (editado)