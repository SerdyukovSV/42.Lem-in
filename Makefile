# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/07 18:06:29 by gartanis          #+#    #+#              #
#    Updated: 2020/06/22 13:35:49 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	:= lemin
CFLAGS 	:= -Wall -Werror -Wextra
CC 		:= gcc
LIBF	:= libft/*.c libft/includes/*.h
SRCF 	:= srcs/main.c srcs/lem_read.c srcs/lem_validate.c srcs/lem_init.c srcs/get_ants.c srcs/get_rooms.c srcs/get_links.c \
			srcs/bfs.c srcs/queue.c srcs/get_path.c
OBJF 	:= $(addprefix obj/, $(notdir $(SRCF:.c=.o)))
INC		:= includes/lemin.h
OBJDIR	:= obj

YELLOW 	:= \033[33;1m
GREEN 	:= \033[32;1m
WHITE	:= \033[39;1m
EOC		:= \033[00m

all: $(TARGET)

$(TARGET): $(OBJF) 
	@$(CC) $^ -o $@ libft/libft.a
	@echo "$(WHITE)$(TARGET)$(EOC)     $(GREEN)compiling completed$(EOC)"

$(OBJF): $(SRCF) $(INC) $(LIBF)
	@printf " Compiling [.:]\r"
	@cd libft/ && make
	@$(CC) -c -I $(INC) $(SRCF)
	@mkdir -p obj && mv *.o obj/
	@printf " Compiling [:.]\r"

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
