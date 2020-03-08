NAME =	cub3D

SRC =	ft_gather_data.c\
		ft_hooks.c\
		ft_ray.c\
		main.c\
		ft_player.c\
		ft_draw.c\
		ft_intersection.c\
		ft_image.c\
		ft_sprites.c\
		ft_bmp.c\
		ft_draw_utils.c\
		ft_intersection_utils.c\
		ft_utils.c\
		ft_shadow.c


LIB = ft_printf/libftprintf.a

GNL = gnl/get_next_line.c gnl/get_next_line_utils.c

Flags = -Wall -Werror -Wextra

OPENGL =  -framework OpenGL -framework AppKit -Ofast
MLIB = minilibx/libmlx.a

SEV = -fsanitize=address

all : $(NAME)

$(NAME) : 
		make -C ft_printf/ re
		make -C minilibx/ re
		gcc  -o $(NAME) $(GNL) $(SRC) $(MLIB) $(LIB) $(SEV) $(OPENGL) -lm  -g
		make clean

clean:
	rm -f *.o ft_printf/*.o minilibx/*.o ft_printf/libft/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
