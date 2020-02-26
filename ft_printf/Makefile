# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 17:35:50 by malaoui           #+#    #+#              #
#    Updated: 2019/11/23 17:41:47 by malaoui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c\
	ft_base.c\
	ft_manage_c.c\
	ft_manage_s.c\
	ft_manage_s_extended.c\
	ft_manage_p.c\
	ft_manage_di.c\
	ft_manage_diutils.c\
	ft_manage_x.c\
	ft_manage_x_extended.c\
	ft_manage_xx.c\
	ft_manage_xxutils.c\
	ft_manage_u.c\
	ft_manage_uutils.c\
	ft_flag_minus.c\
	ft_flag_zero.c\
	ft_no_flag.c\
	ft_manage_simple.c\
	ft_manage_value.c\
	ft_manage_percent.c\
	ft_for_all.c

LIB = libft/libft.a

FLAGS =  -c

GC = gcc -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	$(GC) $(FLAGS) $(SRC)
	make -C libft/ re
	ar x $(LIB)
	ar rc $(NAME) *.o libft/*.o
	ranlib $(NAME)

clean:
	rm -f *.o libft/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
