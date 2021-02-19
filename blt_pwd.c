#include "minishell.h"

void    blt_pwd(t_minishell *s)
{
    char    *buf;
    size_t  size;
    size = 4096;
    if (!(buf = malloc(size)))
        ft_print_error(s);
    while ((getcwd(buf, size) == NULL) && errno == ERANGE)
    {
        size = size + 4096;
        if (!(buf = realloc(buf, size)))
            ft_print_error(s);
    }
    ft_putstr_fd(buf, 0);
    write(1, "\n", 1);
    ft_free_ptr(buf);
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