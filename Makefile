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
CFLAGS 	:= -Wall -Werror -Wextra
CC 		:= gcc

# Source and object direct
LIBFT	:= ./libft/libft.a
INC		:= ./includes/
LFT_DIR := ./libft/
OBJ_DIR	:= ./obj/
SRC_DIR	:= ./srcs/

# Source files
SRCS 	:= main.c lem_read.c lem_validate.c \
			lem_init.c get_ants.c get_rooms.c get_links.c \
			pth_getpaths_copy.c pth_newpath.c pth_queue.c pth_sort.c pth_utility.c \
			ch_choice_paths.c ch_utility.c lm_flow.c lm_play.c

# Object files
OBJF	:= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

YELLOW 	:= \033[33;1m
GREEN 	:= \033[32;1m
DBLUE 	:= \033[34m
WHITE	:= \033[39;1m
EOC		:= \033[00m

all: obj $(LIBFT) $(TARGET)

obj:
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make -C $(LFT_DIR)

$(TARGET): $(OBJF)
	@$(CC) $^ -o $@ $(LIBFT)
	@printf "\n$(WHITE)$(TARGET)$(EOC)    $(GREEN)compiling completed$(EOC)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@printf "$(DBLUE) - Compiling $< into $@\r$(EOC)"
	@$(CC) $(CFLAGS) -I $(INC) -I $(LFT_DIR)/includes -c $< -o $@

clean:
	@rm -rf *.o obj includes/lemin.h.gch
	@cd libft/ && make clean
	@echo "$(WHITE)obj files$(EOC) $(YELLOW)removed$(EOC)"

fclean: clean
	@rm -f $(TARGET)
	@cd libft/ && make fclean
	@echo "$(WHITE)$(TARGET)$(EOC)    $(YELLOW)removed$(EOC)"

re: fclean all

.PHONY: clean fclean re all
