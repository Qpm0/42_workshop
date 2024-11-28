# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmoreanu <cmoreanu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 13:23:28 by cmoreanu          #+#    #+#              #
#    Updated: 2024/02/23 14:33:59 by cmoreanu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
CC	  		= cc
CFLAGS  	= -Wall -Wextra -Werror

MLX	 		= -lmlx -lXext -lX11 -lm
LIBFT		= libft/libft.a

DIR_SRC 	= src
DIR_OBJ 	= .obj

SRC	 		= 	utils.c utils2.c  positions.c main.c map_check2.c \
				render.c map_check.c  map_read.c map_parse.c put_img.c

OBJ			= $(SRC:%.c=$(DIR_OBJ)/%.o)
DEP	 		= $(SRC:%.c=$(DIR_OBJ)/%.d)

all: $(NAME)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c | $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(MLX) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C libft/

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)
	
clean:
	rm -rf $(DIR_OBJ)
	@make clean -C libft/

fclean: clean
	rm -rf $(NAME)
	@make fclean -C libft/

re: fclean all

test: all
	./cub3D maps/map1.cub

.PHONY: all clean fclean re

-include $(DEP)
