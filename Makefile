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
			pth_getpaths.c pth_search_path.c pth_utility.c \
			lem_play.c lem_errors.c lem_free.c options.c

HEADER	:= includes/*.h

vpath %.c srcs/
vpath %.h includes/

# Object files
OBJF	:= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

RED 	:= \033[31;1m
GREEN 	:= \033[32;1m
DBLUE 	:= \033[34m
WHITE	:= \033[39;1m
EOC		:= \033[00m

all: obj $(TARGET)

obj:
	@mkdir -p $(OBJ_DIR)

$(TARGET): $(LIBFT) $(OBJF)
	@$(CC) $^ -o $@ $(LIBFT)
	@printf "\n$(GREEN)compiled: $(WHITE)$(TARGET)$(EOC)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) Makefile
	@printf "$(DBLUE) - Compiling $< into $@\r$(EOC)"
	@$(CC) $(CFLAGS) -I $(INC) -I $(LFT_DIR)/includes -c $< -o $@

$(LIBFT): FORCE
	@make -C $(LFT_DIR)

clean:
	@rm -rf *.o obj includes/lemin.h.gch
	@cd libft/ && make clean
	@echo "$(RED)deleted: $(WHITE)obj files$(EOC)"

fclean: clean
	@rm -f $(TARGET)
	@cd libft/ && make fclean
	@echo "$(RED)deleted: $(WHITE)$(TARGET)$(EOC)"

re: fclean all

FORCE:

.PHONY: clean fclean re all
