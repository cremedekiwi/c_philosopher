# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/18 15:01:43 by jarumuga          #+#    #+#              #
#    Updated: 2024/09/11 15:42:44 by jarumuga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread -g
INCLUDES = -I./includes
SRCS_DIR = srcs
OBJS_DIR = objs
SRCS =	$(SRCS_DIR)/dinner.c \
		$(SRCS_DIR)/getters_setters.c \
		$(SRCS_DIR)/init.c \
		$(SRCS_DIR)/main.c \
		$(SRCS_DIR)/monitor.c \
		$(SRCS_DIR)/parsing.c \
		$(SRCS_DIR)/safe_functions.c \
		$(SRCS_DIR)/synchro_utils.c \
		$(SRCS_DIR)/utils.c \
		$(SRCS_DIR)/write.c

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
