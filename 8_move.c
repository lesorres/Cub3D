/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_move.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:32:42 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 01:20:44 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static void	go_back_n_forward(t_all *all, double mv_speed)
{
	if (all->key.w == 1)
	{
		if (all->flags.map[(int)(all->plr.pos_y + all->plr.dir_y * 1.1
				* mv_speed)][(int)(all->plr.pos_x)] != '1')
			all->plr.pos_y += all->plr.dir_y * mv_speed;
		if (all->flags.map[(int)(all->plr.pos_y)][(int)(all->plr.pos_x
				+ all->plr.dir_x * 1.1 * mv_speed)] != '1')
			all->plr.pos_x += all->plr.dir_x * mv_speed;
	}
	if (all->key.s == 1)
	{
		if (all->flags.map[(int)(all->plr.pos_y - all->plr.dir_y
				* 1.1 * mv_speed)][(int)(all->plr.pos_x)] != '1')
			all->plr.pos_y -= all->plr.dir_y * mv_speed;
		if (all->flags.map[(int)(all->plr.pos_y)][(int)(all->plr.pos_x
				- all->plr.dir_x * 1.1 * mv_speed)] != '1')
			all->plr.pos_x -= all->plr.dir_x * mv_speed;
	}
}

static void	go_sideways(t_all *all, double mv_speed)
{
	if (all->key.d == 1)
	{
		if (all->flags.map[(int)(all->plr.pos_y + all->plr.dir_x
				* 1.1 * mv_speed)][(int)(all->plr.pos_x)] != '1')
			all->plr.pos_y += all->plr.dir_x * mv_speed;
		if (all->flags.map[(int)(all->plr.pos_y)][(int)(all->plr.pos_x
				- all->plr.dir_y * 1.1 * mv_speed)] != '1')
			all->plr.pos_x -= all->plr.dir_y * mv_speed;
	}
	if (all->key.a == 1)
	{
		if (all->flags.map[(int)(all->plr.pos_y - all->plr.dir_x
				* 1.1 * mv_speed)][(int)(all->plr.pos_x)] != '1')
			all->plr.pos_y -= all->plr.dir_x * mv_speed;
		if (all->flags.map[(int)(all->plr.pos_y)][(int)(all->plr.pos_x
				+ all->plr.dir_y * 1.1 * mv_speed)] != '1')
			all->plr.pos_x += all->plr.dir_y * mv_speed;
	}
}

static void	rotate_counterclockwise(t_all *all, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	if (all->key.l == 1)
	{
		old_dir_x = all->plr.dir_x;
		all->plr.dir_x = all->plr.dir_x * cos(-rot_speed)
			- all->plr.dir_y * sin(-rot_speed);
		all->plr.dir_y = old_dir_x * sin(-rot_speed)
			+ all->plr.dir_y * cos(-rot_speed);
		old_plane_x = all->plr.plane_x;
		all->plr.plane_x = all->plr.plane_x * cos(-rot_speed)
			- all->plr.plane_y * sin(-rot_speed);
		all->plr.plane_y = old_plane_x * sin(-rot_speed)
			+ all->plr.plane_y * cos(-rot_speed);
	}
}

static void	rotate_clockwise(t_all *all, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	if (all->key.r == 1)
	{
		old_dir_x = all->plr.dir_x;
		all->plr.dir_x = all->plr.dir_x * cos(rot_speed)
			- all->plr.dir_y * sin(rot_speed);
		all->plr.dir_y = old_dir_x * sin(rot_speed)
			+ all->plr.dir_y * cos(rot_speed);
		old_plane_x = all->plr.plane_x;
		all->plr.plane_x = all->plr.plane_x * cos(rot_speed)
			- all->plr.plane_y * sin(rot_speed);
		all->plr.plane_y = old_plane_x * sin(rot_speed)
			+ all->plr.plane_y * cos(rot_speed);
	}
}

void	move(t_all *all)
{
	double	mv_speed;
	double	rot_speed;

	mv_speed = 0.05;
	rot_speed = 0.05;
	go_back_n_forward(all, mv_speed);
	go_sideways(all, mv_speed);
	rotate_counterclockwise(all, rot_speed);
	rotate_clockwise(all, rot_speed);
}
