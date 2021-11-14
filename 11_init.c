/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:55:34 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 01:31:50 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void	init_flags(t_all *all)
{
	all->flags.save = 0;
	all->flags.map_name = 0;
	all->flags.map_fd = 0;
	all->flags.rx = 0;
	all->flags.ry = 0;
	all->flags.no = 0;
	all->flags.so = 0;
	all->flags.we = 0;
	all->flags.ea = 0;
	all->flags.sprite = 0;
	all->flags.floor = -1;
	all->flags.ceil = -1;
	all->flags.map = 0;
	all->flags.all_lines = 0;
	all->flags.lines = 0;
	all->flags.map_hight = 0;
	all->flags.map_wdth = 0;
}

void	init_plr(t_all *all)
{
	all->plr.pos_x = 0;
	all->plr.pos_y = 0;
	all->plr.dir = 0;
	all->key.a = 0;
	all->key.w = 0;
	all->key.s = 0;
	all->key.d = 0;
	all->key.l = 0;
	all->key.r = 0;
}

void	init_sprites(t_all *all)
{
	all->spr.spr_num = 0;
}

void	init_structure_variables(t_all *all)
{
	init_flags(all);
	init_plr(all);
	init_sprites(all);
}
