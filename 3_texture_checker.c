/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_texture_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 21:17:58 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 21:47:50 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void	check_texture_nswe(char **flag_name, char *line)
{
	int		i;

	i = 3;
	if (*flag_name != NULL)
		error("texture string is duplicated");
	if (line[2] != ' ')
		error("texture file name is not separated by space");
	*flag_name = ft_strtrim(&line[i], " ");
	if (ft_strchr(*flag_name, ' ') || *flag_name == 0)
		error("invalid texture is given");
}

static void	check_sprite_tex(t_all *all, int i)
{
	int		s;

	if (all->flags.sprite)
		error("texture string is duplicated");
	if (all->flags.line[1] != ' ')
		error("texture file name is not separated by space");
	i = 2;
	while (all->flags.line[i] == ' ' && all->flags.line[i] != '\0')
		i++;
	s = i;
	while (all->flags.line[i] != ' ' && all->flags.line[i] != '\0')
		i++;
	all->flags.sprite = ft_substr(all->flags.line, s, (size_t)(i - s));
	while (all->flags.line[i] == ' ' && all->flags.line[i] != '\0')
		i++;
	if (all->flags.line[i] != '\0' || all->flags.sprite == 0)
		error("invalid SO texture is given");
}

void	check_texture(t_all *all)
{
	int		i;

	i = 3;
	if (all->flags.line[0] == 'N' && all->flags.line[1] == 'O')
		check_texture_nswe(&all->flags.no, all->flags.line);
	else if (all->flags.line[0] == 'S' && all->flags.line[1] == 'O')
		check_texture_nswe(&all->flags.so, all->flags.line);
	else if (all->flags.line[0] == 'W' && all->flags.line[1] == 'E')
		check_texture_nswe(&all->flags.we, all->flags.line);
	else if (all->flags.line[0] == 'E' && all->flags.line[1] == 'A')
		check_texture_nswe(&all->flags.ea, all->flags.line);
	else if (all->flags.line[0] == 'S')
		check_sprite_tex(all, i);
}
