/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_map_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 21:13:26 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 21:19:39 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

int	flood_fill(char **map, int x, int y, int map_hight)
{
	if (y < 0 || x < 0 || y >= map_hight)
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (0);
	if (map[y][x] == '1' || map[y][x] == '.'
			|| map[y][x] == 'X' || map[y][x] == 'P')
		return (1);
	if (map[y][x] == '0')
		map[y][x] = '.';
	else if (map[y][x] == '2')
		map[y][x] = 'X';
	else if (ft_strchr("NSWE", map[y][x]))
		map[y][x] = 'P';
	return (flood_fill(map, x - 1, y, map_hight)
		&& flood_fill(map, x + 1, y, map_hight)
		&& flood_fill(map, x, y - 1, map_hight)
		&& flood_fill(map, x, y + 1, map_hight)
		&& flood_fill(map, x - 1, y - 1, map_hight)
		&& flood_fill(map, x + 1, y + 1, map_hight)
		&& flood_fill(map, x + 1, y - 1, map_hight)
		&& flood_fill(map, x - 1, y + 1, map_hight));
}

int	check_all_flags(t_all *all)
{
	if (all->flags.rx == 0 || all->flags.ry == 0 || all->flags.no == 0
		|| all->flags.so == 0 || all->flags.we == 0 || all->flags.ea == 0
		|| all->flags.sprite == 0 || all->flags.floor == -1
		|| all->flags.ceil == -1)
		error("some flags or their values are missing");
	return (1);
}

void	sep_map(t_all *all)
{
	int		i;
	int		line_len;

	i = 0;
	while (all->flags.line[i])
	{
		if (!(ft_strchr("012 NSWE", all->flags.line[i])))
			error("wrong symbol(s) in map part");
		i++;
	}
	if (all->flags.map_hight == 0)
		all->flags.map = malloc(sizeof(char *)
				* (all->flags.all_lines - all->flags.lines + 2));
	all->flags.map[all->flags.map_hight] = malloc(all->flags.map_wdth + 1);
	line_len = ft_strlen(all->flags.line);
	all->flags.map[all->flags.map_hight] = ft_memcpy
		(all->flags.map[all->flags.map_hight], all->flags.line, (line_len));
	while (line_len < all->flags.map_wdth)
	{
		all->flags.map[all->flags.map_hight][line_len] = ' ';
		line_len++;
	}
	all->flags.map[all->flags.map_hight][all->flags.map_wdth] = '\0';
	all->flags.map_hight++;
}

void	check_map_isol(t_all *all)
{
	int	y;
	int	x;

	y = 0;
	while (all->flags.map[y])
	{
		x = 0;
		while (all->flags.map[y][x])
		{
			if (ft_strchr("0NSWE2", all->flags.map[y][x]))
			{
				if (flood_fill(all->flags.map, x, y, all->flags.map_hight) == 0)
					error("map is not isolated");
			}
			x++;
		}
		y++;
	}
}
