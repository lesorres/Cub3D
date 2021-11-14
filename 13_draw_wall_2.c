/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_draw_wall_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 22:03:05 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 22:34:51 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void	calc_tex_param(t_all *all, t_data *curr_tex, int side)
{
	double	wall_x;

	if (side == 0)
		wall_x = all->plr.pos_y + all->plr.perp_wall_dist
			* all->plr.raydir_y;
	else
		wall_x = all->plr.pos_x + all->plr.perp_wall_dist
			* all->plr.raydir_x;
	wall_x -= floor(wall_x);
	all->plr.tex_x = (int)(wall_x * (double)curr_tex->img_width);
	if (side == 0 && all->plr.raydir_x > 0)
		all->plr.tex_x = curr_tex->img_width - all->plr.tex_x - 1;
	if (side == 1 && all->plr.raydir_y < 0)
		all->plr.tex_x = curr_tex->img_width - all->plr.tex_x - 1;
}

void	draw_textures(t_all *all, t_data *curr_tex, int x)
{
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	all->plr.step = 1.0 * curr_tex->img_height / all->plr.line_h;
	tex_pos = (all->plr.draw_str - all->flags.ry / 2
			+ all->plr.line_h / 2) * all->plr.step;
	y = all->plr.draw_str;
	while (y <= all->plr.draw_end)
	{
		tex_y = (int)tex_pos % (curr_tex->img_height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y > curr_tex->img_height)
			tex_y = curr_tex->img_height;
		tex_pos += all->plr.step;
		color = *(unsigned int *)(curr_tex->addr
				+ (tex_y * curr_tex->line_length
					+ all->plr.tex_x * (curr_tex->bits_per_pixel / 8)));
		if (color < 0)
			color = 0x000000;
		my_mlx_pixel_put(&all->img, x, y, color);
		y++;
	}
}
