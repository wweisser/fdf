# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 15:31:57 by wendelin          #+#    #+#              #
#    Updated: 2022/06/14 14:37:49 by wendelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= fdfutils.a

LFLAGS = -Lmlx -lmlx -L$(INCLIB) -lXext -lX11 -lm

INPUT = fdf.c fdf_visual.c fdf_shape.c ft_bzero.c
SRC = fdf.o fdf_visual.o fdf_shape.o ft_bzero.o

#Linux and others...
CC	= gcc
LFLAGS += -lbsd

all:  $(NAME) clean

$(NAME): $(SRC)
	ar -rc $(NAME) $(OBJ) #$(LFLAGS) 

SRC: $(INPUT)
	$(CC) -c $(INPUT) 

clean: 
	rm -f $(SRC)

re: clean all
