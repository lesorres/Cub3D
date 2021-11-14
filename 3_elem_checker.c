/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_elem_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 19:13:48 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/29 22:07:31 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static void	check_screen_resolution(t_all *all, int	big_res_w, int big_res_h)
{
	int	width;
	int	height;

	if (all->flags.save == 1)
	{
		if (all->flags.rx > 7000 || all->flags.ry > 7000)
			error("resolution is too big");
	}
	else
	{
		mlx_get_screen_size(&width, &height);
		if (big_res_w == 1 || all->flags.rx > width)
			all->flags.rx = width;
		if (big_res_h == 1 || all->flags.ry > height)
			all->flags.ry = height;
		if (all->flags.rx < 1 || all->flags.ry < 1)
			error("invalid resolution is given");
		if ((all->flags.rx % 2) != 0)
			all->flags.rx = all->flags.rx - 1;
		if ((all->flags.ry % 2) != 0)
			all->flags.ry = all->flags.ry - 1;
	}
}

static int	write_resolution(t_all *all, int *r, int i)
{
	if (all->flags.line[i] >= 48 && all->flags.line[i] <= 57)
	{
		*r = ft_atoi((char *)&(all->flags.line[i]));
		while (all->flags.line[i] >= 48 && all->flags.line[i] <= 57)
			i++;
	}
	return (i);
}

static int	trim_spaces_n_zeros(t_all *all, int i, int p)
{
	if (p == 1)
	{
		while (all->flags.line[i] == ' ' && all->flags.line[i] != '\0')
			i++;
		while (all->flags.line[i] == '0' && all->flags.line[i] != '\0')
			i++;
	}
	if (p == 2)
	{
		while (all->flags.line[i] == ' ' && all->flags.line[i] != '\0')
			i++;
	}
	return (i);
}

void	check_resolution(t_all *all)
{
	int	i;
	int	tmp;
	int	big_res_w;
	int	big_res_h;

	big_res_w = 0;
	big_res_h = 0;
	i = 2;
	i = trim_spaces_n_zeros(all, i, 1);
	tmp = i;
	if (all->flags.rx || all->flags.ry)
		error("resolution string is duplicated");
	i = write_resolution(all, &all->flags.rx, i);
	if (i - tmp > 9)
		big_res_w = 1;
	i = trim_spaces_n_zeros(all, i, 1);
	tmp = i;
	i = write_resolution(all, &all->flags.ry, i);
	if (i - tmp > 9)
		big_res_h = 1;
	i = trim_spaces_n_zeros(all, i, 2);
	if (all->flags.line[i] != '\0' || all->flags.rx == 0 || all->flags.ry == 0)
		error("invalid resolution is given");
	check_screen_resolution(all, big_res_w, big_res_h);
}

void	skip_spaces(t_all *all)
{
	int		i;
	int		len;

	i = 0;
	while (all->flags.line[i] == ' ')
		i++;
	if (all->flags.line[i] != '\0' && ft_strchr("RNSWECF", all->flags.line[i]))
	{
		len = ft_strlen(&all->flags.line[i]);
		all->flags.line = ft_memcpy(all->flags.line, &all->flags.line[i], len);
		all->flags.line[len] = '\0';
	}
}
