# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/17 15:39:34 by lfabbro           #+#    #+#              #
#    Updated: 2016/11/13 20:34:51 by lfabbro          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC_NAME = main.c wolf3d_map.c wolf3d_draw.c wolf3d_draw2.c wolf3d_hook.c \
		   wolf3d_event.c wolf3d_texture.c 

OBJ_NAME = $(SRC_NAME:.c=.o)

LIB_NAME = -lftprintf -lmlx -lm

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
LIB_PATH = ./libft/ ./minilibx_macos/
INC_PATH = ./includes ./libft/includes  ./minilibx_macos

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
LIB = $(addprefix -L, $(LIB_PATH))
INC = $(addprefix -I ,$(INC_PATH))

FRAMEWORK = -framework OpenGL -framework Appkit

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ofast

all: lib
	@echo "\033[32;44m Make $(NAME) \033[0m"
	@make $(NAME)

$(NAME): $(OBJ)
	$(CC) $(INC) $^ -o $@ $(LIB) $(LIB_NAME) $(FRAMEWORK)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

.PHONY: all lib clean fclean re

lib:
	@make -C ./libft
	@echo "\033[32;44m Make minilibx \033[0m"
	@make -C ./minilibx_macos

clean:
	@echo "\033[31;44m Removing Wolf3D objects \033[0m"
	@rm -rf $(OBJ) $(OBJ_PATH)

fclean: clean
	@echo "\033[31;44m Removing Wolf3D executables \033[0m"
	rm -f $(NAME)
	make -C ./libft fclean
	@echo "\033[31;44m Removing minilibx executables \033[0m"
	make -C ./minilibx_macos clean

re: fclean
	@make all
