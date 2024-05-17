NAME        = minishell

CC          = cc

CFLAGS      = -g3 -Wextra -Werror

SRC         = $(EXEC_SRC)dislpay_err.c $(EXEC_SRC)check_access.c \
              $(EXEC_SRC)redirection.c $(EXEC_SRC)fork.c minishell.c \
              $(OTHER_SRC)other.c $(OTHER_SRC)builtins.c $(OTHER_SRC)lst_add.c \
              $(EXEC_SRC)heredoc.c $(OTHER_SRC)env.c \
              $(PARSING_SRC)syntaxe_errors.c $(PARSING_SRC)utilities.c \
              $(PARSING_SRC)utilities_nd.c $(PARSING_SRC)commands_stocker.c \
              $(PARSING_SRC)expander.c $(PARSING_SRC)heredoc.c \
              $(PARSING_SRC)redirection.c $(PARSING_SRC)main_functions.c \
              $(PARSING_SRC)main_functions_nd.c $(PARSING_SRC)syntaxe_errors_nd.c 

PARSING_SRC = parsing/

EXEC_SRC    = exec/

OTHER_SRC   = other/

OBJ         = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c includes/minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@
	printf "\033[1A\033[KCompiling $<\r"

$(NAME): $(OBJ)
	@make -sC libft && $(CC) $(OBJ) -L libft -l ft -lreadline -o $(NAME)
	printf "\033[38;5;220m\033[1A\033[KExecutable $(NAME) created\n\033[0m"

clean :
	@rm -rf  $(OBJ) 
	@make -sC libft clean
	printf "\033[38;5;220m\033[1A\033[KCleaning objects\n\033[0m"

fclean : clean
	@rm -f $(NAME)
	@make -sC libft fclean
	printf "\033[38;5;220m\033[1A\033[KRemoving $(NAME) and libraries\n\033[0m"

re : fclean all

.PHONY : all clean fclean re
