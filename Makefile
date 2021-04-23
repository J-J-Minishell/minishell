NAME =	minishell
CC =	gcc
FLAGS = -c -Wall -Wextra -Werror
OBJS =	$(SRCS:.c=.o)
SRCS =	srcs/blts/blt_unset.c srcs/blts/blt_export.c srcs/blts/blt_env.c \
		srcs/blts/blt_pwd.c srcs/blts/blt_cd.c srcs/blts/blt_echo.c \
		srcs/execute/execute_command.c srcs/execute/pipes.c \
		srcs/execute/process_command.c srcs/parsing_line/env_var.c \
		srcs/parsing_line/history_cmds.c srcs/parsing_line/path.c \
		srcs/parsing_line/process_line.c srcs/parsing_line/read_line.c \
		srcs/parsing_line/redirections.c srcs/utils/utils.c \
		srcs/utils/utils2.c srcs/utils/utils3.c srcs/utils/special_split.c \
        srcs/minishell.c
INC = -I. -I srcs/libft
LFT = -L srcs/libft -lft

minishell: $(SRCS)
	make -C srcs/libft
	$(CC) $(FLAGS) $(SRCS)
	mkdir -p srcs/obj
	mv *.o srcs/obj
	gcc -o $(NAME) srcs/obj/*.o $(INC) $(LFT)


.PHONY: all clean fclean re

all: $(NAME)

clean:
	make clean -C srcs/libft
	rm -f $(OBJS)
	rm -f srcs/obj/*.o
	rm -f *.o

fclean: clean
	make fclean -C srcs/libft
	rm -f $(NAME)

re: fclean all
