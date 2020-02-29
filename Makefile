NAME =	cub3D

SRC =	ft_gather_data.c\
		ft_hooks.c\
		ray.c\
		main.c\
		ft_draw.c\
		ft_intersection.c\
		ft_image.c


LIB = ft_printf/libftprintf.a

GNL = gnl/get_next_line.c gnl/get_next_line_utils.c

Flags = -Wall -Werror -Wextra

OPENGL =  -framework OpenGL -framework AppKit  -Ofast

MLIB = minilibx/libmlx.a

all : $(NAME)

$(NAME) : 
		make -C ft_printf/ re
		make -C minilibx/ re
		gcc  -o $(NAME) $(GNL) $(SRC) $(MLIB) $(LIB) $(OPENGL)  -g

clean:
	rm -f *.o ft_printf/*.o minilibx/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
