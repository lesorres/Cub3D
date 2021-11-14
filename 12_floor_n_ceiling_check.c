/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_floor_n_ceiling_check.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 21:56:19 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 01:41:19 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static int	ft_strsrch(char *temp, char c)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (temp[i])
	{
		if (temp[i] == c)
			n++;
		i++;
	}
	return (n);
}

static void	check_valid_symbols_n_errors(t_all *all, char c)
{
	int		i;
	char	*temp;

	if ((c == 'C' && all->flags.ceil != -1)
		|| (c == 'F' && all->flags.floor != -1))
		error("floor or ceiling strings are duplicaded");
	if (all->flags.line[1] != ' ')
		error("floor or ceiling strings are invalid");
	i = 0;
	temp = ft_strtrim(&all->flags.line[1], " ");
	if (ft_strsrch(temp, ',') != 2 || ft_strsrch(temp, '-') > 0)
		error("invalid color(s) is given");
	while (temp[i])
	{
		if (!((temp[i] > 47 && temp[i] < 58)
				|| temp[i] == 32 || temp[i] == 44))
			error("invalid color(s) is given");
		i++;
	}
	free(all->flags.line);
	all->flags.line = temp;
}

void	check_splited_strings(char	**array)
{
	int		i;
	int		j;
	char	*tmp;

	i = 2;
	if (array[0] == 0 || array[1] == 0 || array[2] == 0)
		error("invalid color(s) is given");
	while (i >= 0)
	{
		tmp = ft_strtrim(array[i], " ");
		if (tmp[0] == '\0')
			error("invalid color(s) is given");
		free (array [i]);
		array[i] = tmp;
		if (ft_strchr(array[i], ' '))
			error("invalid color(s) is given");
		j = 0;
		while (array[i][j] == '0')
			j++;
		if (strlen(&array[i][j]) > 3)
			error("some color parameters are too big");
		i--;
	}
}

void	check_colors(t_all *all)
{
	char	**array;
	int		rgb[3];
	char	c;
	int		len;

	len = 3;
	c = all->flags.line[0];
	check_valid_symbols_n_errors(all, c);
	array = ft_split(all->flags.line, ',');
	check_splited_strings(array);
	rgb[0] = ft_atoi(array[0]);
	rgb[1] = ft_atoi(array[1]);
	rgb[2] = ft_atoi(array[2]);
	if (rgb[0] > 255 || rgb[0] < 0 || rgb[1] > 255 || rgb[1] < 0
		|| rgb[2] > 255 || rgb[2] < 0)
		error("some color parameters are too big");
	if (c == 'C')
		all->flags.ceil = create_trgb(0, rgb[0], rgb[1], rgb[2]);
	else if (c == 'F')
		all->flags.floor = create_trgb(0, rgb[0], rgb[1], rgb[2]);
	while (len--)
		free(array[len]);
	free(array);
}
