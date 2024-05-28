CC = gcc

CFLAGS = -Wall -Wextra -g

NAME = minishell

SRCS =	srcs/main.c\
		srcs/flux.c\
		srcs/exec.c \
		srcs/utils.c \
		srcs/export.c \
		srcs/parsing.c \
		srcs/builtins.c \
		srcs/parsing_env.c \
		srcs/parsing_end.c \
		srcs/parsing_utils.c \
		srcs/builtins_exec.c \
		srcs/parsing_utils2.c \
		srcs/builtins_utils.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

objs/%.o : src/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<
	

$(NAME) :   $(OBJS)
	@echo "Make..."
	@rm -rf objs
	@mkdir objs
	@$(MAKE) -C libft
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L./libft/ -lft -I$(brew --prefix readline)/include -L$(brew --prefix readline)/lib -lreadline
	@mv srcs/*.o objs/
	@echo "Make Completed !"
clean   :
	@echo "Clean..."
	@make -C libft clean
	@rm -rf srcs/*.o
	@rm -rf objs/*.o
	@echo "Clear !"
fclean  :   clean
	@rm -f libft/libft.a
	@rm -rf objs
	@rm -f $(NAME)
	
re      :   fclean all