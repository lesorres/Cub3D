/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:57:18 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/29 21:22:29 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void	check_line_functions(t_all *all)
{
	if (all->flags.line[0] == 'R' && all->flags.line[1] == ' ')
	{
		check_resolution(all);
		all->flags.lines++;
	}
	if (ft_strchr("NSWE", all->flags.line[0]))
	{
		check_texture(all);
		all->flags.lines++;
	}
	if (ft_strchr("FC", all->flags.line[0]))
	{
		check_colors(all);
		all->flags.lines++;
	}
}

void	check_line(t_all *all)
{
	skip_spaces(all);
	if (all->flags.line[0] == '\0')
	{
		if (all->flags.map != NULL)
			error("map is separated or followed by empty line(s)");
		all->flags.lines++;
	}
	else if ((all->flags.line[0] == 'R' && all->flags.line[1] == ' ')
		|| ft_strchr("NSWE", all->flags.line[0])
		|| ft_strchr("FC", all->flags.line[0]))
		check_line_functions(all);
	else if (ft_strchr("10 ", all->flags.line[0]))
	{
		if (check_all_flags(all))
			sep_map(all);
	}
	else
		error("invalid map file");
	free (all->flags.line);
	all->flags.line = 0;
}

void	count_all_lines_and_map_width_with_gnl(t_all *all)
{
	int		close_return;
	int		wdth;

	all->flags.map_fd = open(all->flags.map_name, O_RDONLY);
	while (gnl_error(all) == 1)
	{
		if (ft_strchr(" 1", all->flags.line[0])
			&& (wdth = ft_strlen(all->flags.line)) > all->flags.map_wdth)
			all->flags.map_wdth = wdth;
		all->flags.all_lines++;
		free (all->flags.line);
	}
	free (all->flags.line);
	close_return = close(all->flags.map_fd);
}

void	parse_map(t_all *all)
{
	all->flags.map_fd = open(all->flags.map_name, O_RDONLY);
	while (gnl_error(all) == 1)
		check_line(all);
	check_line(all);
	if (all->flags.map == NULL)
		error("digit map is missing");
	all->flags.map[all->flags.map_hight] = NULL;
}

void	process_map_file(t_all *all)
{
	count_all_lines_and_map_width_with_gnl(all);
	parse_map(all);
	find_player_coordinates(all);
	find_sprites_num(all);
	write_sprites_coord(all);
	check_map_isol(all);
	all->plr.z_buf = malloc(sizeof(double) * all->flags.rx);
}
