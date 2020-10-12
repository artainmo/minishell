# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artainmo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/14 22:06:29 by artainmo          #+#    #+#              #
#    Updated: 2020/02/26 02:34:26 by sel-melc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =       minishell.c \
			parsing/parsing.c \
			parsing/parsing_utils.c \
			parsing/quote.c \
			parsing/dollar_question.c \
			parsing/no_tab.c \
			parsing/ft_split_cmd_utils.c \
			parsing/empty_cmds.c \
			parsing/ft_split_cmd.c \
			parsing/redirect_parse_utils.c \
			parsing/redirect_parse_utils2.c \
			parsing/double_left_redirect_only.c \
			commands/ft_echo.c \
			commands/cd/ft_cd.c \
			commands/cd/cd_utils.c \
			commands/ft_exit.c \
			commands/ft_pwd.c \
			commands/pipes/ft_pipe.c \
			commands/pipes/pipe_utils.c \
			commands/executables/cat.c \
			commands/executables/exec.c \
			commands/executables/exec_utils.c \
			commands/redirections/ft_right_redirections.c \
			commands/redirections/ft_left_redirection.c \
			commands/redirections/ft_double_left_redirection.c \
			commands/redirections/ft_left_right_redirec.c \
			commands/redirections/redirection_utils.c \
			commands/redirections/redirection_utils2.c \
			commands/redirections/redirection_utils3.c \
			commands/environment_variables/ft_env.c \
			commands/environment_variables/ft_export.c \
			commands/environment_variables/ft_unset.c \
			commands/environment_variables/env.c \
			commands/environment_variables/env_parse.c \
			commands/environment_variables/env_parse_utils.c \
			commands/environment_variables/env_utils.c \
			commands/environment_variables/env_utils2.c \
			commands/ctrl.c \
			utils/error_handle.c\
			utils/get_next_line/get_next_line.c\
			utils/get_next_line/get_next_line_utils.c
OBJ = $(SRC:.c=.o)
#s->transforming .c in .o to enable the creation of a library


LIBFLAGS = -I . -L . -I ./utils/libft -L ./utils/libft -I ./utils/get_next_line -I ./utils/ft_printf -L ./utils/ft_printf
# -I Add the directory dir to the list of directories to be searched for header files
# -L Searches the library when linking

GCC = gcc -Wall -Wextra -Werror #-fsanitize=address
RM = rm -rf

all: libft_all printf_all $(NAME)


$(NAME): $(OBJ)
	$(GCC) $(LIBFLAGS) -o $(NAME) $(OBJ) libft.a libftprintf.a && clear
# -c is used to form .o files from .c files
# !! Do not use -o before SRC it made files dissapear !!
# -o is normally used to create an executable into the filename that follows

# WALL WEXTRA WERROR ARE CURRENTLY NOT APPLIED UNCOMMENT THOSE 2 LINES TO APPLY FLAGSS
%.o: %.c
	$(GCC) -c -o $@ $?

bonus: all

clean: libft_fclean printf_fclean
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# In this last section we make other makefiles compile with the -C flag
# The -C flag makes you go to the appropriate path and do the asked command
libft_all:
	make -C ./utils/libft all
	cp ./utils/libft/libft.a libft.a
libft_clean:
	make -C ./utils/libft clean
libft_fclean:
	make -C ./utils/libft fclean
	$(RM) libft.a

printf_all:
	make -C ./utils/ft_printf all
	cp ./utils/ft_printf/libftprintf.a libftprintf.a
printf_fclean:
	make -C ./utils/ft_printf fclean
	$(RM) libftprintf.a

.PHONY: all test clean fclean re bonus
# Phony targets can exs->plicitly tell Make they're not associated with files but with make commands
