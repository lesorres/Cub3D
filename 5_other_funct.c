/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_other_funct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:37:37 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/27 19:35:25 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

int	gnl_error(t_all *all)
{
	int	i;

	i = get_next_line(all->flags.map_fd, &all->flags.line);
	if (i == -1)
		error("read from file error");
	return (i);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	error(char *str)
{
	printf("Error\n%s\n", str);
	exit (1);
}

int	key_press(int keycode, t_all *all)
{
	if (keycode == 0)
		all->key.a = 1;
	if (keycode == 13)
		all->key.w = 1;
	if (keycode == 1)
		all->key.s = 1;
	if (keycode == 2)
		all->key.d = 1;
	if (keycode == 123)
		all->key.l = 1;
	if (keycode == 124)
		all->key.r = 1;
	if (keycode == 53)
		exit (1);
	return (1);
}

int	key_release(int keycode, t_all *all)
{
	if (keycode == 0)
		all->key.a = 0;
	if (keycode == 13)
		all->key.w = 0;
	if (keycode == 1)
		all->key.s = 0;
	if (keycode == 2)
		all->key.d = 0;
	if (keycode == 123)
		all->key.l = 0;
	if (keycode == 124)
		all->key.r = 0;
	if (keycode == 53)
		exit (1);
	return (1);
}
