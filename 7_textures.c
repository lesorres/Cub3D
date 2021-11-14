/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 16:08:22 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/27 19:24:26 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static void	write_tex(t_all *all, t_data *tex, char *relative_path)
{
	tex->img = mlx_xpm_file_to_image(all->mlx.mlx, relative_path,
			&tex->img_width, &tex->img_height);
	if (tex->img == 0)
		error("texture name or content is invalid");
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
}

void	write_tex_param(t_all *all)
{
	write_tex(all, &all->tex.no, all->flags.no);
	write_tex(all, &all->tex.so, all->flags.so);
	write_tex(all, &all->tex.we, all->flags.we);
	write_tex(all, &all->tex.ea, all->flags.ea);
	write_tex(all, &all->tex.spr, all->flags.sprite);
}

t_data	choose_tex(t_all *all, int side, int step_x, int step_y)
{
	if (side == 0)
	{
		if (step_x == 1)
			return (all->tex.ea);
		else
			return (all->tex.we);
	}
	else
	{
		if (step_y == 1)
			return (all->tex.so);
		else
			return (all->tex.no);
	}
}
