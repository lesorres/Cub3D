/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 22:52:27 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 16:22:10 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	write_line(char **line, char **rem, char **border, char **buf)
{
	char		*tmp;

	tmp = *border;
	*border = *border + 1;
	tmp[0] = '\0';
	*line = ft_strdup_gnl(*rem);
	tmp = *rem;
	*rem = ft_strdup_gnl(*border);
	free(tmp);
	free(*buf);
	return (1);
}

static int	write_last_line(char **line, char **rem, char **buf)
{
	*line = ft_strdup_gnl(*rem);
	free(*rem);
	*rem = NULL;
	free(*buf);
	buf = NULL;
	return (0);
}

static int	error_return(char **buf, char **rem)
{
	free(*buf);
	*buf = NULL;
	free(*rem);
	*rem = NULL;
	return (-1);
}

static int	new(char **line, char **rem, char **buf, int fd)
{
	int			rd;
	char		*border;

	border = ft_strchr_gnl(*rem, '\n');
	if (!border)
		rd = read(fd, *buf, BUFFER_SIZE);
	while (!border && rd)
	{
		if (rd == -1)
			return (error_return(buf, rem));
		(*buf)[rd] = '\0';
		*rem = ft_strjoin_gnl(*rem, *buf);
		border = ft_strchr_gnl(*rem, '\n');
		if (!border)
			rd = read(fd, *buf, BUFFER_SIZE);
	}
	if (rd == 0 && !border)
		return (write_last_line(line, rem, buf));
	else
		return (write_line(line, rem, &border, buf));
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*rem;

	if (fd < 0 || !line || BUFFER_SIZE <= 0
		|| !(buf = malloc(sizeof(*buf) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!rem)
	{
		rem = malloc(sizeof(*rem));
		if (!rem)
			return (error_return(&buf, &rem));
		rem[0] = '\0';
	}
	return (new(line, &rem, &buf, fd));
}
