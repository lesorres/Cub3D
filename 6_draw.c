/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_draw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 20:25:02 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 22:35:56 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void	draw_ceiling(t_all *all)
{
	int	y;
	int	x;

	y = 0;
	while (y < all->flags.ry / 2)
	{
		x = 0;
		while (x < all->flags.rx)
		{
			my_mlx_pixel_put(&all->img, x, y, all->flags.ceil);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_all *all)
{
	int	y;
	int	x;

	y = all->flags.ry / 2;
	while (y < all->flags.ry)
	{
		x = 0;
		while (x < all->flags.rx)
		{
			my_mlx_pixel_put(&all->img, x, y, all->flags.floor);
			x++;
		}
		y++;
	}
}

int	draw(t_all *all)
{
	all->flags.line = 0;
	draw_ceiling(all);
	draw_floor(all);
	draw_wall(all);
	move(all);
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.win, all->img.img, 0, 0);
	return (1);
}
