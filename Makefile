# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 18:52:08 by vvaucoul          #+#    #+#              #
#    Updated: 2024/01/09 00:54:54 by vvaucoul         ###   ########.fr        #
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

SRCS = $(shell find srcs -name '*.c')

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