# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 14:25:53 by yongmipa          #+#    #+#              #
#    Updated: 2023/03/02 14:44:15 by yongmipa         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
FLAGS		= -Wall -Wextra -Wextra
AR			= ar rcs
RM			= rm -f

INCS_DIR	= ./includes/
SRCS_DIR	= ./src/
BONUS_DIR	= ./bonus/

LIB_DIR		= ./libft

LIB_NAME	= ./libft/libft.a

INCS		= -I includes

SRC			=	tree_utils.c main.c path_utils.c heredoc.c

SRC_BN		=	

SRCS		=	$(addprefix $(SRCS_DIR), $(SRC))
SRCS_BONUS	=	$(addprefix $(BONUS_DIR), $(SRC_BN))
LIBS		=	$(addprefix $(LIB_DIR), $(LIB_NAME))
OBJS		=	$(SRCS:.c=.o)
OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)

ifdef MINISHELL_WITH_BONUS
    INC_DIR = ./includes/
    OBJ_FILES = $(OBJS_BONUS)
else
    INC_DIR = ./includes/
    OBJ_FILES = $(OBJS)
endif

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

bonus :
	make MINISHELL_WITH_BONUS=1 all

$(NAME) : $(OBJ_FILES)
	make -C $(LIB_DIR)
	$(CC) -o $(NAME) $(OBJ_FILES) $(LIB_NAME)

clean :
	make -C $(LIB_DIR) clean
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean : clean
	make -C $(LIB_DIR) fclean
	$(RM) $(NAME)

re : 
	make fclean 
	make all

bonus_re:
	make fclean
	make bonus

PHONY	: all bonus clean fclean re