/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 23:54:56 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 16:23:31 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 10

size_t		ft_strlen_gnl(char *str);
char		*ft_strchr_gnl(char *s, int c);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*ft_strdup_gnl(char *s1);
int			get_next_line(int fd, char **line);

#endif
