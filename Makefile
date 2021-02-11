# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 20:05:16 by mvan-eyn          #+#    #+#              #
#    Updated: 2021/01/31 19:38:38 by hbuisser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	src/main.c \
			src/parser/parser.c \
			src/parser/parser2.c \
			src/parser/parser3.c \
			src/parser/quotes.c \
			src/builtins/cmd_dispatch.c \
			src/traduction/ft_traduction.c \
			src/errors/ft_errors.c \
			src/errors/ft_errors2.c \
			src/errors/ft_errors3.c \
			src/errors/ft_errors4.c \
			src/free/ft_free.c \
			src/free/ft_free2.c \
			src/builtins/ft_echo.c \
			src/builtins/ft_env.c \
			src/builtins/ft_export.c \
			src/builtins/ft_export2.c \
			src/builtins/ft_unset.c \
			src/builtins/ft_exit.c \
			src/builtins/ft_cd.c \
			src/builtins/ft_pwd.c \
			src/traduction/handle_dollar.c \
			src/traduction/handle_dollar2.c \
			src/traduction/handle_quotes.c \
			src/traduction/check_quotes.c \
			src/traduction/handle_backslash.c \
			src/traduction/handle_tilde.c \
			src/bin/ft_bin.c \
			src/bin/ft_bin2.c \
			src/bin/ft_bin3.c \
			src/bin/ft_path.c \
			src/tools/save_data.c \
			src/tools/tools_int.c \
			src/tools/tools_int2.c \
			src/tools/tools_str.c \
			src/tools/tools_str2.c \
			src/pipe/pipe.c \
			src/redir/ft_redir.c \
			src/redir/ft_redir2.c \
			src/redir/ft_redir3.c \
			src/signal/signal.c \
			\
			src/test.c \
			\
			

OBJS	=	$(SRCS:%.c=%.o)

LIBFT	=	utils/libft/libft.a

NAME	=	minishell

CFLAGS	=	-Wall -Wextra -Werror -g

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
			gcc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

clean:		
			rm -rf $(OBJS)
			cd utils/libft/ && make $@

fclean:		clean
			rm -rf $(NAME)
			rm -rf $(LIBFT)

re:			fclean all

$(LIBFT):
			make bonus -C ./utils/libft