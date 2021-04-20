NAME =	minishell
CC =	gcc
FLAGS = -g -c
OBJS =	$(SRCS:.c=.o)
SRCS = srcs/blts/blt_unset.c srcs/blts/blt_export.c srcs/blts/blt_env.c srcs/blts/blt_pwd.c srcs/blts/blt_cd.c srcs/blts/blt_echo.c \
		srcs/execute/execute_command.c srcs/execute/pipes.c srcs/execute/process_command.c \
		srcs/parsing_line/env_var.c srcs/parsing_line/history_cmds.c srcs/parsing_line/path.c srcs/parsing_line/process_line.c srcs/parsing_line/read_line.c srcs/parsing_line/redirections.c \
		srcs/utils/utils.c srcs/utils/special_split.c \
        minishell.c
INC = -I. -I libft
LFT = -L libft -lft									# No entiendo que es -lft pero sin ello no funciona

minishell: $(SRCS)
	make -C libft
	$(CC) $(FLAGS) $(SRCS)
	mkdir -p srcs/obj
	mv *.o srcs/obj
	gcc -o $(NAME) srcs/obj/*.o $(INC) $(LFT)


.PHONY: all clean fclean re

all: $(NAME)

clean:
	make clean -C libft
	rm -f $(OBJS)
	rm -f srcs/obj/*.o
	rm -f *.o

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
