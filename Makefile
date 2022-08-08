# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 15:31:57 by wendelin          #+#    #+#              #
#    Updated: 2022/08/08 14:03:26 by wweisser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME= fdf

CC 		= gcc
LIBFT 	= libft/libft.a
MINILIB	= -Lmlx -lmlx -framework OpenGL -framework AppKit
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

$(NAME): $(OBJ) 
	@$(CC) $(OBJ) $(MANDATORY) $(LIBFT) $(MINILIB) $(FLAGS) $(LINKS) -lm -o $(NAME)
	
bonus: $(OBJ) 
	@$(CC) $(OBJ) $(BONUS) $(LIBFT) $(MINILIB) $(FLAGS) $(LINKS) -lm -o fdf_bonus

$(OBJ): $(INPUT)
	@$(CC) -Wall -Wextra -Werror -c $(SRC) 

clean: 
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME) fdf_bonus

re: fclean all
