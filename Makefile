# Compiler and flags
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -fsanitize=address
# Sources
SRC_PATH	=	src/
SRC			=	\
main.c main_loop.c signal.c signal_tools.c init.c \
tokenizer.c token_tools.c token_tools1.c token_tools2.c token_tools3.c token_tools4.c token_tools5.c\
env.c env_tools.c parser.c parser_tools.c parser_cmd.c parser_redir.c \
exe.c exe_cmd.c exe_tools.c exe_heredoc.c exe_cmd_tools.c exe_cmd_tools2.c exe_cmd_tools3.c exe_cmd_tools4.c exe_cmd_tools5.c exe_cmd_tools6.c exe_cmd_tools7.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))
SRCS		= $(addprefix $(SRC_PATH), $(SRC))
# Objects
OBJ_PATH	= 	src/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))
# Target
NAME 		= minishell

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Includes
INC			=	-I ./src \
				-I ./libft/ \
				-I /usr/local/opt/readline/include
RLPATH		=	/usr/local/opt/readline/lib/

HEADER		=	$(SRC_PATH)minishell.h \
				$(SRC_PATH)env.h \
				$(SRC_PATH)parser.h \
				$(SRC_PATH)tokenizer.h \
				$(SRC_PATH)exe.h 
# Default rule: make all
all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)
# Rule to build the library
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(INC) -L$(RLPATH) -lreadline
# Rule to compile object files
$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC) 

# Clean up object files
clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_PATH)
# Clean up object files and the library
fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)
# Rebuild everything
re: fclean all

# By default, just run 'make all'
.DEFAULT_GOAL := all