# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/29 20:16:09 by tjuzen            #+#    #+#              #
#    Updated: 2019/10/12 20:05:24 by tjuzen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRCDIR = ./src/
OBJDIR = ./obj/
INCL = ./includes/


FILES = $(shell find src -type f | grep -E "\.c$$" | sed 's/src//g')
SRC = $(addprefix $(SRCDIR), $(FILES))
OBJ = $(addprefix $(OBJDIR), $(FILES:.c=.o))
SRCSUBDIR = $(shell find ./src -type d)
OBJSUBDIR = $(SRCSUBDIR:./src%=./obj%)
LONGEST = $(shell echo $(notdir $(SRC)) | tr " " "\n" | \
	awk ' { if ( lenght > x ) { x = lenght; y = $$0 } }END{ print y }' | wc -c )


GGCOLORCYAN = \033[96m
GGCOLORGREEN = \033[32m
GGCOLORRED = \033[31m
GGMAG = \033[1;35m
GGRESET = \033[39m

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCL)
	@$(CC) $(FLAGS) -o $@ -c $<

$(OBJSUBDIR):
		@mkdir $@

$(NAME): $(OBJSUBDIR) $(OBJ)
		@ar rc $(NAME) $(OBJ)
clean:
		@/bin/rm -rf $(OBJ)

fclean: clean
		@/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
