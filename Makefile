CC = gcc

CFLAGS = -Wall -Wextra -g

NAME = minishell

DIR_SRCS	=	srcs
DIR_OBJS	=	.objs

LST_SRCS =	main.c\
			flux.c\
			exec.c \
			exit.c \
			utils.c \
			export.c \
			parsing.c \
			builtins.c \
			parsing_env.c \
			parsing_end.c \
			last_parsing.c \
			parsing_utils.c \
			builtins_exec.c \
			parsing_utils2.c \
			builtins_utils.c

LST_OBJS = $(LST_SRCS:.c=.o)

SRCS		=	$(addprefix $(DIR_SRCS)/, $(LST_SRCS))
OBJS		=	$(addprefix $(DIR_OBJS)/, $(LST_OBJS))

ERASE		=	\033[2K\r
BLUE		=	\033[34m
YELLOW		=	\033[33m
GREEN		=	\033[32m
END			=	\033[0m

all : $(NAME)

$(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	@mkdir -p .objs
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(BLUE) > Compilation :$(END) $<\n"
	

$(NAME) :   $(OBJS)
	@printf "$(GREEN).c are compiled\n$(END)"
	@printf "$(BLUE) > Libft Compilation ...\n$(END)"
	@$(MAKE) -C libft
	@printf "$(ERASE)$(GREEN)Libft made !\n$(END)"
	@$(CC) $(OBJS) $(CFLAGS)  -L./libft/ -lft -I$(brew --prefix readline)/include -L$(brew --prefix readline)/lib -lreadline -o $(NAME)
	@printf "$(ERASE)$(GREEN)Minishell made !\n$(END)"

clean   :
	@printf "$(YELLOW)$(DIR_OBJS) removed$(END)\n"
	@make clean -C libft
	@rm -rdf $(DIR_OBJS)

fclean  :   clean
	@printf "$(YELLOW)Minishell removed$(END)\n"
	@make fclean -C libft
	@rm -f $(NAME)
	
re      :   fclean all