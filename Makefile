# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 18:52:08 by vvaucoul          #+#    #+#              #
#    Updated: 2022/05/19 12:06:54 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#								 	 COLORS			  					 	   #
################################################################################

# This is a minimal set of ANSI/VT100 color codes
_END=$'\033[0m
_BOLD=$'\033[1m
_UNDER=$'\033[4m
_REV=$'\033[7m

# Colors
_GREY=$'\033[30m
_RED=$'\033[31m
_GREEN=$'\033[32m
_YELLOW=$'\033[33m
_BLUE=$'\033[34m
_PURPLE=$'\033[35m
_CYAN=$'\033[36m
_WHITE=$'\033[37m

# Inverted, i.e. colored backgrounds
_IGREY=$'\033[40m
_IRED=$'\033[41m
_IGREEN=$'\033[42m
_IYELLOW=$'\033[43m
_IBLUE=$'\033[44m
_IPURPLE=$'\033[45m
_ICYAN=$'\033[46m
_IWHITE=$'\033[47m

################################################################################
#								 	  PRINT		  					 	 	   #
################################################################################

### PRINT UTILS ###
PRINT_COMP		=	printf "\r$(_BOLD)$(_WHITE)- $(_BOLD)$(_CYAN)[%s]\r\t\t\t\t\t $(_BOLD)$(_WHITE)[✓]\n"


################################################################################
#								   COMPILATION		  					 	   #
################################################################################

NAME = 42_PCC_LIBFT.a
SRCS =	$(wildcard srcs/*.c) \
		$(wildcard srcs/print/*.c) \
		$(wildcard srcs/number/*.c) \
		$(wildcard srcs/printf/*.c) \
		$(wildcard srcs/string/*.c) \
		$(wildcard srcs/alloc/*.c) \
		$(wildcard srcs/memory/*.c) \
		$(wildcard srcs/char/*.c) \
		$(wildcard srcs/array/*.c) \
		$(wildcard srcs/convert/*.c) \
		$(wildcard srcs/linked_list/*.c) \
		$(wildcard srcs/auto-allocator/*.c) \
		$(wildcard srcs/binary-tree/*.c) \
		$(wildcard srcs/classes/*.c) \

CC = gcc
AR = ar -rc
CFLAGS = -Wall -Wextra -g3 # -Werror # -
OBJS = $(SRCS:.c=.o)

%.o:%.c
	@echo -n "\r                                                               "
	@$(PRINT_COMP) $@
	@$(CC) $(CFLAGS) -I./includes -c $< -o ${<:.c=.o}

################################################################################
#								   	  RULES			  					 	   #
################################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

clean:
		@rm -f $(OBJS)

fclean: clean
		@rm -f lft_test
		@rm -f $(NAME)

re: fclean all

test:
	make
	@$(PRINT_COMP) "lft_test"
	@$(CC) tests/main.c  -I./includes 42_PCC_LIBFT.a -o lft_test

.PHONY: all clean fclean re test