# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/07 18:06:29 by gartanis          #+#    #+#              #
#    Updated: 2020/07/17 01:47:04 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	:= lem-in
LIBFT	:= libft.a
CFLAGS 	:= -Wall -Werror -Wextra
CC 		:= gcc

# Source and object direct
INC		:= ./includes/
LFT_DIR := ./libft/
OBJ_DIR	:= ./obj/

# Source files
SRC 	:= srcs/main.c srcs/lem_read.c srcs/lem_validate.c srcs/lem_init.c \
			srcs/get_ants.c srcs/get_rooms.c srcs/get_links.c srcs/queue.c \
			srcs/get_paths.c srcs/cmp_paths.c srcs/lem_play.c
# Object files

SRCF	:= $(notdir $(SRC))
OBJF	:= $(SRCF:%.c=$(OBJ_DIR)%.o)

YELLOW 	:= \033[33;1m
GREEN 	:= \033[32;1m
WHITE	:= \033[39;1m
EOC		:= \033[00m

all: obj $(LIBFT) $(TARGET)

obj:
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make -C $(LFT_DIR)

$(OBJ_DIR): $(SRC)%.c
	@printf "$(YELLOW) - Compiling $< into $@\r"
	@$(CC) $(CFLAGS) -I $(INC) -I $(LFT_DIR)/includes -c $< -o $@

$(TARGET): $(OBJF)
	@$(CC) $^ -o $@ $(LFT_DIR)$(LIBFT)

clean:
	@rm -rf *.o obj includes/lemin.h.gch
	@cd libft/ && make clean
	@echo "$(WHITE)obj files$(EOC) $(YELLOW)removed$(EOC)"

fclean: clean
	@rm -f $(TARGET)
	@cd libft/ && make fclean
	@echo "$(WHITE)$(TARGET)$(EOC)     $(YELLOW)removed$(EOC)"

re: fclean all

.PHONY: clean fclean re all
