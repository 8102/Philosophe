##
## Makefile for philo in /home/patoche/rendu/Unix/PSU_2014_philo
## 
## Made by Hugo Prenat
## Login   <prenat_h@epitech.eu>
## 
## Started on  Wed Feb 25 10:17:02 2015 Hugo Prenat
## Last update Fri Feb 27 19:39:00 2015 Jean-Baptiste Grégoire
##

SRC		=	src/main.c	\
			src/philo.c	\
			bonus/window_init.c

OBJ		=	$(SRC:.c=.o)

NAME		=	philo

CC		=	gcc

RM		=	rm -f

DEBUG		=	yes

INCLUDE 	=	includes/

CFLAGS		=	-W -Wall -Wextra -I $(INCLUDE)

ifeq ($(DEBUG),yes)
	CFLAGS 	+= -g3
else
	CFLAGS	+= -O3
endif

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) -lpthread -lncurses `sdl-config --cflags --libs` -lSDL_image

all:		$(NAME)

clean:
	$(RM) $(OBJ)

fclean: 	clean
	$(RM) $(NAME)

re: 		fclean all

.PHONY: all clean fclean re
