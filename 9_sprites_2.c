/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_sprites_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 21:50:08 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 22:02:40 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void	find_sprites_num(t_all *all)
{
	int	x;
	int	y;

	y = 0;
	while (all->flags.map[y])
	{
		x = 0;
		while (all->flags.map[y][x])
		{
			if (all->flags.map[y][x] == '2')
				all->spr.spr_num++;
			x++;
		}
		y++;
	}
}

void	write_sprites_coord(t_all *all)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	if (all->spr.spr_num != 0)
	{
		all->spr.s = malloc(sizeof(t_sprt) * all->spr.spr_num);
		y = 0;
		while (all->flags.map[y])
		{
			x = 0;
			while (all->flags.map[y][x])
			{
				if (all->flags.map[y][x] == '2')
				{
					all->spr.s[i].x = (double)x + 0.5;
					all->spr.s[i].y = (double)y + 0.5;
					i++;
				}
				x++;
			}
			y++;
		}
	}
}

void	calc_spr_dist(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->spr.spr_num)
	{
		all->spr.s[i].dist = ((all->plr.pos_x - all->spr.s[i].x)
				* (all->plr.pos_x - all->spr.s[i].x)
				+ (all->plr.pos_y - all->spr.s[i].y)
				* (all->plr.pos_y - all->spr.s[i].y));
		i++;
	}
}

static int	swap_sprites(t_all *all, int j)
{
	t_sprt	tmp;

	tmp.dist = all->spr.s[j].dist;
	tmp.x = all->spr.s[j].x;
	tmp.y = all->spr.s[j].y;
	all->spr.s[j].dist = all->spr.s[j + 1].dist;
	all->spr.s[j].x = all->spr.s[j + 1].x;
	all->spr.s[j].y = all->spr.s[j + 1].y;
	all->spr.s[j + 1].dist = tmp.dist;
	all->spr.s[j + 1].x = tmp.x;
	all->spr.s[j + 1].y = tmp.y;
	return (j);
}

void	sort_sprites_order(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	while (i < all->spr.spr_num)
	{
		j = 0;
		while (j < all->spr.spr_num - 1)
		{
			if (all->spr.s[j].dist < all->spr.s[j + 1].dist)
				swap_sprites(all, j);
			j++;
		}
		i++;
	}
}
