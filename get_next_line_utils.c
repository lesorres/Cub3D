/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 23:45:54 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 16:23:23 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	char	*ss;
	char	cc;
	int		i;

	ss = (char *)s;
	cc = (char)c;
	i = 0;
	while (*ss != '\0')
	{
		if (*ss == c)
			return (ss);
		ss++;
	}
	if (*ss == '\0' && cc == '\0')
		return (ss);
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	size_t	i;
	size_t	n;
	size_t	len1;
	size_t	len2;

	i = 0;
	n = 0;
	len1 = ft_strlen_gnl(s1);
	len2 = ft_strlen_gnl(s2);
	result = malloc((len1 + len2 + 1) * sizeof(*result));
	if (result == NULL)
		return (0);
	while (i != len1)
	{
		result[i] = s1[i];
		i++;
	}
	while (i != (len1 + len2))
		result[i++] = s2[n++];
	free(s1);
	s1 = NULL;
	result[i] = '\0';
	return (result);
}

char	*ft_strdup_gnl(char *s1)
{
	int		len;
	char	*cpy;
	size_t	i;

	i = 0;
	len = ft_strlen_gnl((char *)s1);
	cpy = malloc(sizeof(*cpy) * (len + 1));
	if (cpy == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
