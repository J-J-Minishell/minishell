#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <wait.h>
# include <signal.h>
# include <dirent.h>

# include <stdio.h>
# include <time.h>

# include "libft/libft.h"

typedef struct	s_minishell
{
	char	*env_address;
	char	**env;
	char	*line;
	char	**commands;
	char	**tokens;
	char	*path;
	char	*command_path;
	char	**blt_cmds;
}				t_minishell;

void	check_env_var(t_minishell *s);
void	cmd_echo(t_minishell *s);
char	**special_split(char const *s, char c);
int		get_next_line(int fd, char **line);

void	ft_get_env_variables(t_minishell *s, char **envp);
void	ft_initialize_variables(t_minishell *s);

void	ft_clean_up(t_minishell *s);
void	ft_print_error(t_minishell *s);
void	*ft_free_matrix(char **matrix);
char	*ft_get_env_var_content(t_minishell *s, char *var);
int		ft_find_env_var(t_minishell *s, char *var);

void	ft_read_line(t_minishell *s);

void	ft_process_line(t_minishell *s);

char	*ft_get_current_command(t_minishell *s);

void	ft_execute_command(t_minishell *s);

void	ft_get_path(t_minishell *s);
void	ft_get_env_path(t_minishell *s);
char	*ft_check_dir(t_minishell *s, char **paths);

void	blt_env(t_minishell *s);
void	blt_export(t_minishell *s);
void	blt_unset(t_minishell *s);
void	blt_pwd(t_minishell *s);
void	blt_cd(t_minishell *s);
void	ft_update_pwd(t_minishell *s);

# define TRUE 1
# define FALSE 0
# define INPUT_BUFFER_SIZE 5
# define TOKEN_BUFFER_SIZE 64
# define MAX_ARGS 64

#endif
