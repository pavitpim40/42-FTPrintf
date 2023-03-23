# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 20:29:49 by ppimchan          #+#    #+#              #
#    Updated: 2023/03/23 20:51:09 by ppimchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a 
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIB	 = ar -rcs
RM = /bin/rm -f
BUILD_DIR = ./build
SRC_DIRS = ./
INCS_DIR = ./

SRCS =	ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_strlen.c \

OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(NAME)

$(BUILD_DIR)/$(NAME): $(OBJS) $(INCS)
	ar -rcs	$(NAME) $(OBJS)

$(BUILD_DIR)/%.c.o: %.c	
	mkdir -p $(dir $@)	
	$(CC) $(CFLAGS) -I $(INCS_DIR) -c $< -o $@

clean:		
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
