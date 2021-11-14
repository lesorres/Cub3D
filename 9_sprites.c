/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_sprites.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:40:17 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 22:22:06 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

int	find_new_spr_position(t_all *all, int i)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = all->spr.s[i].x - all->plr.pos_x;
	sprite_y = all->spr.s[i].y - all->plr.pos_y;
	inv_det = 1.0 / (all->plr.plane_x * all->plr.dir_y
			- all->plr.dir_x * all->plr.plane_y);
	all->spr.transform_x = inv_det * (all->plr.dir_y * sprite_x
			- all->plr.dir_x * sprite_y);
	all->spr.transform_y = inv_det * (-all->plr.plane_y * sprite_x
			+ all->plr.plane_x * sprite_y);
	all->spr.sprite_screen_x = (int)((all->flags.rx / 2)
			* (1 + all->spr.transform_x / all->spr.transform_y));
	return (i);
}

void	find_spr_draw_params(t_all *all)
{
	all->spr.sprite_h = (int)fabs((all->flags.rx / all->spr.transform_y)
			* 0.75);
	all->spr.draw_str_y = all->flags.ry / 2 - all->spr.sprite_h / 2;
	if (all->spr.draw_str_y < 0)
		all->spr.draw_str_y = 0;
	all->spr.draw_end_y = all->flags.ry / 2 + all->spr.sprite_h / 2;
	if (all->spr.draw_end_y >= all->flags.ry)
		all->spr.draw_end_y = all->flags.ry;
	all->spr.sprite_w = (int)fabs((all->flags.rx / all->spr.transform_y)
			* 0.75);
	all->spr.draw_str_x = all->spr.sprite_screen_x - all->spr.sprite_w / 2;
	if (all->spr.draw_str_x < 0)
		all->spr.draw_str_x = 0;
	all->spr.draw_end_x = all->spr.sprite_screen_x + all->spr.sprite_w / 2;
	if (all->spr.draw_end_x >= all->flags.rx)
		all->spr.draw_end_x = all->flags.rx;
	all->spr.stripe = all->spr.draw_str_x;
}

static void	draw_sprite_by_stripe(t_all *all, int y)
{
	all->spr.d = y * 256 - all->flags.ry * 128
		+ all->spr.sprite_h * 128;
	all->spr.tex_y = ((all->spr.d * all->tex.spr.img_height)
			/ all->spr.sprite_h) / 256;
	all->spr.color = *(unsigned int *)(all->tex.spr.addr
			+ (all->spr.tex_y * all->tex.spr.line_length
				+ all->spr.tex_x * (all->tex.spr.bits_per_pixel
					/ 8)));
	if ((all->spr.color & 0x00FFFFFF) != 0)
		my_mlx_pixel_put(&all->img, all->spr.stripe, y,
			all->spr.color);
}

void	put_sprites_to_img(t_all *all)
{
	int	y;

	while (all->spr.stripe < all->spr.draw_end_x)
	{
		all->spr.tex_x = (int)((256 * (all->spr.stripe - (-all->spr.sprite_w
							/ 2 + all->spr.sprite_screen_x))
					* all->tex.spr.img_width / all->spr.sprite_w)
				/ 256);
		if (all->spr.transform_y > 0.3 && all->spr.stripe >= 0
			&& all->spr.stripe < all->flags.rx
			&& all->spr.transform_y < all->plr.z_buf[all->spr.stripe])
		{
			y = all->spr.draw_str_y;
			while (y < all->spr.draw_end_y)
			{
				draw_sprite_by_stripe(all, y);
				y++;
			}
		}
		all->spr.stripe++;
	}
}

void	draw_sprites(t_all *all)
{
	int		i;

	i = 0;
	calc_spr_dist(all);
	sort_sprites_order(all);
	while (i < all->spr.spr_num)
	{
		i = find_new_spr_position(all, i);
		find_spr_draw_params(all);
		put_sprites_to_img(all);
		i++;
	}
}
