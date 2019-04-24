# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchevass <rchevass@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/04 00:09:45 by rchevass          #+#    #+#              #
#    Updated: 2018/09/16 07:23:28 by jlemahie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = wolf3d

CC = gcc
FLAGS = -Wall -Werror -Wextra

MLX = minilibx_macos/libmlx.a
MFLAGS = -framework OpenGL -framework AppKit

SRC_PATH = src
OBJ_PATH = obj
LIB_PATH = lib/libft.a

SOURCES =	main.c \
			ray.c \
			texture.c \
			draw.c \
			move.c \
			parsing.c \
			menu.c \
			init.c \
			sky.c \
			ft_quit.c \
			event.c \
			map.c \
			wall.c

SRCS = $(addprefix $(SRC_PATH)/, $(SOURCES))

OBJS = $(addprefix $(OBJ_PATH)/, $(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C lib
	@make -C minilibx_macos
	@$(CC) $(OBJS) $(LIB_PATH) $(MLX) -o $(NAME) $(MFLAGS)
	@echo "Compilation $(NAME) OK"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c include/incwol.h
	@mkdir -p obj
	@$(CC) $(FLAGS) -o $@ -c $<

clean:
	@make clean -C minilibx_macos
	@make clean -C lib
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIB_PATH)

re: fclean all
