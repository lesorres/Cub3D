# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/03 19:31:08 by kmeeseek          #+#    #+#              #
#    Updated: 2021/04/28 22:56:49 by kmeeseek         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# INPUT = ./*.c
# LIB = ./*.a
# HEAD = ./*.h
# FLAGS = -framework AppKit -framework OpenGL minilibx_opengl_20191021/libmlx.a

# all: $(INPUT) $(LIB) $(HEAD)
# 	gcc -Wall -Wextra -Werror $(INPUT) $(LIB) $(HEAD) $(FLAGS) -g 
#-fsanitize=address

NAME	= cub3D
LIB		= libft/libft.a minilibx_opengl/libmlx.a
LIBFILE = libft/libft.a
MLXLIB  = minilibx_opengl/libmlx.a
HEAD	= *.h
INPUT	= $(wildcard *.c)
FLAGS	= -framework AppKit -framework OpenGL 
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
OFILES	= $(INPUT:.c=.o)

all: mlxlib libfile $(NAME)
$(NAME): $(OFILES) $(LIBFILE) $(MLXLIB)
	gcc -g $(OFILES) $(LIB) ${FLAGS} -o $(NAME)
libfile:
	@$(MAKE) -C ./libft
mlxlib:
	@$(MAKE) -C ./minilibx_opengl
%.o : %.c cub.h
	gcc -g $(CFLAGS) -c $< -o $(<:.c=.o)
clean:  
	@$(MAKE) clean -C ./libft
	@$(MAKE) clean -C ./minilibx_opengl
	$(RM) $(OFILES)
fclean:     clean
	@$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re libfile mlxlib
