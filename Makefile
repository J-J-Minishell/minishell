NAME =	minishell
CC =	gcc
FLAGS = -g -c
OBJS =	$(SRCS:.c=.o)
SRCS = redirections.c pipes.c history_cmds.c blt_unset.c blt_export.c blt_env.c blt_pwd.c blt_cd.c env_var.c blt_echo.c special_split.c minishell.c utils.c read_line.c process_line.c execute_command.c path.c
INC = -I. -I libft
LFT = -L libft -lft									# No entiendo que es -lft pero sin ello no funciona

minishell: $(SRCS)
	make -C libft
	$(CC) $(FLAGS) $(SRCS)
	mkdir -p obj
	mv *.o obj
	gcc -o $(NAME) obj/*.o $(INC) $(LFT)


.PHONY: all clean fclean re

all: $(NAME)

clean:
	make clean -C libft
	rm -f $(OBJS)
	rm -f obj/*.o
	rm -f *.o

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
