/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:39:22 by malaoui           #+#    #+#             */
/*   Updated: 2019/12/26 18:32:36 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# define BUFFER_SIZE 1

int		get_next_line(int fd, char **line);
int		ft_checkerror(int fd, char **line, char **buff);
size_t	ft_strlen(const char *s);
char	*ft_add(char *s1, char *s2, int len);
int		ft_checkin(char *s, char **line, int rd);
char	*ft_store(char *s);
#endif
