# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 18:52:08 by vvaucoul          #+#    #+#              #
#    Updated: 2022/09/10 10:12:51 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include depends/Colors.mk

################################################################################
#								 	  PRINT		  					 	 	   #
################################################################################

### PRINT UTILS ###
PRINT_COMP		=	printf "$(_CLEAR_LINE)$(_BOLD)$(_WHITE)- $(_BOLD)$(_LGREEN)[%s] $(_BOLD)$(_WHITE)[$(_LGREEN)✓$(_LWHITE)]\n$(_MOVE_LINE_UP)"

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
		$(wildcard srcs/dlinked_list/*.c) \
		$(wildcard srcs/parser/*.c) \

CC = gcc
AR = ar -rc
CFLAGS = -Wall -Wextra -g3 # -Werror # -
OBJS = $(SRCS:.c=.o)

DEPENDS = $(OBJS:.o=.d)

%.o:%.c
	@$(PRINT_COMP) $@
	@$(CC) $(CFLAGS) -I./includes -c -MD $< -o ${<:.c=.o}

################################################################################
#								   	  RULES			  					 	   #
################################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@printf "$(_CLEAR_LINE)$(_BOLD)$(_WHITE)- $(_BOLD)$(_LCYAN)[%s] $(_WHITE)Compiled ! $(_BOLD)$(_WHITE)[$(_LGREEN)✓$(_LWHITE)]\n" $(NAME)

clean:
	@rm -f $(OBJS) $(DEPENDS)

fclean: clean
	@rm -f lft_test
	@rm -f $(NAME) 

re: fclean all

test: $(NAME)
	@$(CC) tests/main.c  -I./includes 42_PCC_LIBFT.a -o lft_test
	@printf "$(_CLEAR_LINE)$(_BOLD)$(_WHITE)- $(_BOLD)$(_LCYAN)[%s] $(_WHITE)Compiled ! $(_BOLD)$(_WHITE)[$(_LGREEN)✓$(_LWHITE)]\n" "lft_test"

-include $(DEPENDS)

.PHONY: all clean fclean re test