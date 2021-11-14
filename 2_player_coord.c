/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_player_coord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 20:32:38 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 21:07:47 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static void	write_dir_one(t_all *all, double dir_y,
	double plane_x)
{
	all->plr.dir_x = 0;
	all->plr.dir_y = dir_y;
	all->plr.plane_x = plane_x;
	all->plr.plane_y = 0;
}

static void	write_dir_two(t_all *all, double dir_x, double plane_y)
{
	all->plr.dir_x = dir_x;
	all->plr.dir_y = 0;
	all->plr.plane_x = 0;
	all->plr.plane_y = plane_y;
}

static void	write_player_dir_param(t_all *all)
{
	if (all->plr.dir == 'N')
		write_dir_one(all, -1, 0.66);
	if (all->plr.dir == 'S')
		write_dir_one(all, 1, -0.66);
	if (all->plr.dir == 'W')
		write_dir_two(all, -1, -0.66);
	if (all->plr.dir == 'E')
		write_dir_two(all, 1, 0.66);
}

static void	find_player(t_all *all, int x, int y)
{
	write_player_dir_param(all);
	if (all->plr.pos_x == 0 && all->plr.pos_y == 0)
	{
		all->plr.pos_x = (double)x + 0.5;
		all->plr.pos_y = (double)y + 0.5;
	}
	else
		error("invalid number of players");
}

void	find_player_coordinates(t_all *all)
{
	int		x;
	int		y;
	char	*s;

	y = 0;
	while (all->flags.map[y])
	{
		x = 0;
		while (all->flags.map[y][x])
		{
			s = ft_strchr("NSWE", all->flags.map[y][x]);
			if (s)
			{
				all->plr.dir = *s;
				find_player(all, x, y);
			}
			x++;
		}
		y++;
	}
	if (all->plr.pos_x == 0 && all->plr.pos_y == 0)
		error("invalid number of players");
}
