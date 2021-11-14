/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_draw_wall_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 21:54:36 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 22:36:02 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static void	calculate_params(t_all *all, int x)
{
	double	cameraX;

	cameraX = 2 * x / (double)all->flags.rx - 1;
	all->plr.raydir_x = all->plr.dir_x + all->plr.plane_x * cameraX;
	all->plr.raydir_y = all->plr.dir_y + all->plr.plane_y * cameraX;
	all->plr.map_x = (int)all->plr.pos_x;
	all->plr.map_y = (int)all->plr.pos_y;
	all->plr.delta_dist_x = fabs(1 / all->plr.raydir_x);
	all->plr.delta_dist_y = fabs(1 / all->plr.raydir_y);
}

static void	find_step_n_sidedist(t_all *all)
{
	if (all->plr.raydir_x < 0)
	{
		all->plr.step_x = -1;
		all->plr.sidedist_x = (all->plr.pos_x - all->plr.map_x)
			* all->plr.delta_dist_x;
	}
	else
	{
		all->plr.step_x = 1;
		all->plr.sidedist_x = (all->plr.map_x + 1.0 - all->plr.pos_x)
			* all->plr.delta_dist_x;
	}
	if (all->plr.raydir_y < 0)
	{
		all->plr.step_y = -1;
		all->plr.sidedist_y = (all->plr.pos_y - all->plr.map_y)
			* all->plr.delta_dist_y;
	}
	else
	{
		all->plr.step_y = 1;
		all->plr.sidedist_y = (all->plr.map_y + 1.0 - all->plr.pos_y)
			* all->plr.delta_dist_y;
	}
}

static int	perform_dda(t_all *all)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (all->plr.sidedist_x < all->plr.sidedist_y)
		{
			all->plr.sidedist_x += all->plr.delta_dist_x;
			all->plr.map_x += all->plr.step_x;
			side = 0;
		}
		else
		{
			all->plr.sidedist_y += all->plr.delta_dist_y;
			all->plr.map_y += all->plr.step_y;
			side = 1;
		}
		if (all->flags.map[all->plr.map_y][all->plr.map_x] == '1')
			hit = 1;
	}
	return (side);
}

static void	calculate_dist_n_size_params(t_all *all, int side)
{
	if (side == 0)
		all->plr.perp_wall_dist = (all->plr.map_x - all->plr.pos_x
				+ (1 - all->plr.step_x) / 2) / all->plr.raydir_x;
	else
		all->plr.perp_wall_dist = (all->plr.map_y - all->plr.pos_y
				+ (1 - all->plr.step_y) / 2) / all->plr.raydir_y;
	all->plr.line_h = (int)(all->flags.rx / all->plr.perp_wall_dist * 0.75);
	all->plr.draw_str = (all->flags.ry - all->plr.line_h) / 2;
	if (all->plr.draw_str < 0)
		all->plr.draw_str = 0;
	all->plr.draw_end = all->flags.ry / 2 + all->plr.line_h / 2;
	if (all->plr.draw_end >= all->flags.ry)
		all->plr.draw_end = all->flags.ry - 1;
}

void	draw_wall(t_all *all)
{
	int		side;
	t_data	curr_tex;
	int		x;

	x = 0;
	while (x < all->flags.rx)
	{
		calculate_params(all, x);
		find_step_n_sidedist(all);
		side = perform_dda(all);
		calculate_dist_n_size_params(all, side);
		curr_tex = choose_tex(all, side, all->plr.step_x, all->plr.step_y);
		calc_tex_param(all, &curr_tex, side);
		draw_textures(all, &curr_tex, x);
		all->plr.z_buf[x] = all->plr.perp_wall_dist;
		x++;
	}
	draw_sprites(all);
}
