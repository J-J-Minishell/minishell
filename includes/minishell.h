#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>

# include <stdio.h>
# include <time.h>

#include <termios.h>    //termios, TCSANOW, ECHO, ICANON

# include "libft/libft.h"

char	*line;

typedef struct	s_minishell
{
	char	*env_address;
	char	**env;
	char	**commands;
	char	**tokens;
	char	*path;
	char	*command_path;
	char	**blt_cmds;
	int		exit_status;
	char	*home;
	int		fd;
	int		fdi;
	char	**history_cmds;
	int		n_cmds;
	char	*new_hist_cmd;
	char	**pipe_commands;

}				t_minishell;

int		skip_quotes(char *s);
void	ft_process_command(t_minishell *s, int i);
void	check_redirections(t_minishell *s);
void	ft_pipes(t_minishell *s);
void	ft_process_tokken(t_minishell *s);

char	**add_new_pos_matrix(char **matrix, char *new);
char	**cpy_matrix(char **matrix, int size);
void	add_history_cmd(t_minishell *s, int index);
int		choose_history_cmd(t_minishell *s, int len, int index);
int		ft_str_is_printable_ascii(char *s);

void	export_env_var(t_minishell *s, char *export_var, int len_name);
void	check_env_var(t_minishell *s);
void	cmd_echo(t_minishell *s);
char	**special_split(char const *s, char c);

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
void	ft_rel_back_path(t_minishell *s);
void	ft_abs_or_rel_path(t_minishell *s);
char	*ft_check_dir(t_minishell *s, char **paths);

void	blt_env(t_minishell *s);
void	blt_export(t_minishell *s);
void	blt_unset(t_minishell *s);
void	blt_pwd(t_minishell *s);
void	blt_cd(t_minishell *s);
void	ft_update_pwd(t_minishell *s);

void	child_sig_handler(int sig);

int		ft_counterbar_before_expansion(t_minishell *s, int i, int j);

# define TRUE 1
# define FALSE 0
# define INPUT_BUFFER_SIZE 5
# define TOKEN_BUFFER_SIZE 64
# define MAX_ARGS 64

#endif
