# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 15:31:57 by wendelin          #+#    #+#              #
#    Updated: 2022/08/06 15:22:24 by wendelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME= fdf

CC 		= gcc
LIBFT 	= libft/libft.a
INPUT	= fdf_input/fdf_input.a
MINILIB	= -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm mlx/libmlx.a
LINKS 	= -g -lm -fsanitize=address 
FLAGS	= -Wall -Werror -Werror

SRC 	= fdf.c 		\
fdf_calc_mtx.c			\
fdf_calc_point.c		\
fdf_calc_round.c		\
fdf_calc_trigon.c		\
fdf_calc_vector.c		\
fdf_control_keyboard.c	\
fdf_control_mouse.c		\
fdf_input_main.c		\
fdf_input_mem.c			\
fdf_input_read.c		\
fdf_mainstate.c			\
fdf_perspective.c		\
fdf_structure_mem.c		\
fdf_structure.c			\
fdf_visualisation.c			

MANDATORY = fdf_mandatory.c
BONUS = fdf_bonus.c

OBJ 	= fdf.o 		\
fdf_calc_mtx.o			\
fdf_calc_point.o		\
fdf_calc_round.o		\
fdf_calc_trigon.o		\
fdf_calc_vector.o		\
fdf_control_keyboard.o	\
fdf_control_mouse.o		\
fdf_input_main.o		\
fdf_input_mem.o			\
fdf_input_read.o		\
fdf_mainstate.o			\
fdf_perspective.o		\
fdf_structure_mem.o		\
fdf_structure.o			\
fdf_visualisation.o			

all: $(NAME)

$(NAME): $(SRC) 
	@$(CC) $(SRC) $(MANDATORY) $(LIBFT) $(MINILIB) $(INPUT) $(FLAGS) $(LINKS) -lm -o $(NAME)
	
bonus: $(SRC) 
	@$(CC) $(SRC) $(BONUS) $(LIBFT) $(MINILIB) $(INPUT) $(FLAGS) $(LINKS) -lm -o fdf_bonus

$(OBJ): $(INPUT)
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx -O3 -c $(INPUT)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) fdf_bonus

re: fclean all
