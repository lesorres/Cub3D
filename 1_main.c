/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:48:32 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/29 21:23:25 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void	check_passed_arguments(t_all *all, int argc, char **argv)
{
	int	len;

	if (argc == 2 || argc == 3)
	{
		len = ft_strlen(argv[1]);
		if (!ft_strncmp(&argv[1][len - 4], ".cub", 5)
			&& !ft_strncmp(argv[0], "./cub3D", 8))
			all->flags.map_name = argv[1];
		else
			error("invalid arguments is given");
		if (argc == 3)
		{
			if (ft_strlen(argv[2]) == 6 && !ft_strncmp(argv[2], "--save", 6))
				all->flags.save = 1;
			else
				error("invalid arguments is given");
		}
	}
	else
		error("invalid number of arguments is given");
}

void	screenshot(t_all *all)
{
	all->bmp = (t_bmp *)malloc(sizeof(t_bmp));
	all->img.addr = (char *)malloc(all->flags.rx * all->flags.ry * sizeof(int));
	all->img.bits_per_pixel = 32;
	all->img.line_length = all->flags.rx * (all->img.bits_per_pixel / 8);
	write_tex_param(all);
	draw_ceiling(all);
	draw_floor(all);
	draw_wall(all);
	make_screenshot(all);
}

int	quit(void)
{
	exit (1);
}

void	rendering(t_all *all)
{
	all->mlx.win = mlx_new_window(all->mlx.mlx, all->flags.rx,
			all->flags.ry, "cub3D");
	all->img.img = mlx_new_image(all->mlx.mlx, all->flags.rx, all->flags.ry);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel,
			&all->img.line_length, &all->img.endian);
	mlx_hook(all->mlx.win, 2, 0, key_press, all);
	mlx_hook(all->mlx.win, 3, 0, key_release, all);
	mlx_hook(all->mlx.win, 17, 1L << 0, &quit, &all);
	write_tex_param(all);
	mlx_loop_hook(all->mlx.mlx, draw, all);
	mlx_loop(all->mlx.mlx);
}

int	main(int argc, char **argv)
{
	t_all	all;

	init_structure_variables(&all);
	check_passed_arguments(&all, argc, argv);
	process_map_file(&all);
	all.mlx.mlx = mlx_init();
	if (all.flags.save == 1)
		screenshot(&all);
	else
		rendering(&all);
	return (0);
}
