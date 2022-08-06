# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/06 11:39:27 by wendelin          #+#    #+#              #
#    Updated: 2022/08/06 12:57:52 by wendelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf_input.a

CC 		= cc
LINKS 	= -g -lm -fsanitize=address 
FLAGS	= -Wall -Werror -Werror
LIBFT	= ../libft/libft.a

SRC 	= fdf_input_read.c fdf_input_mem.c

OBJ 	= fdf_input_read.o fdf_input_mem.o

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@ar r $(NAME) $(OBJ) $(LIBFT)
	
$(OBJ): $(RC)
	$(CC) $(FLAGS) $(LINKS) -c $(SRC)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
