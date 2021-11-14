/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 20:49:04 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 19:24:38 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void	init_headers(t_all *all)
{
	all->bmp->fileheader.file_type[0] = 'B';
	all->bmp->fileheader.file_type[1] = 'M';
	all->bmp->fileheader.file_size = all->flags.rx * all->flags.ry
		* all->img.bits_per_pixel / 8 + 54;
	all->bmp->fileheader.reserved = 0;
	all->bmp->fileheader.file_offset_to_pxl_arr = 54;
	all->bmp->infoheader.header_size = sizeof(t_infohead);
	all->bmp->infoheader.img_width = all->flags.rx;
	all->bmp->infoheader.img_height = -all->flags.ry;
	all->bmp->infoheader.planes = 1;
	all->bmp->infoheader.bpp = all->img.bits_per_pixel;
	all->bmp->infoheader.compression = 0;
	all->bmp->infoheader.img_size = all->flags.rx * all->flags.ry
		* all->img.bits_per_pixel / 8;
	all->bmp->infoheader.ypixelpermeter = 0;
	all->bmp->infoheader.xpixelpermeter = 0;
	all->bmp->infoheader.color_palette = 0;
	all->bmp->infoheader.imp_color = 0;
}

void	write_to_file(t_all *all, int fd)
{
	write(fd, &all->bmp->fileheader.file_type, sizeof(char) * 2);
	write(fd, &all->bmp->fileheader.file_size, sizeof(int));
	write(fd, &all->bmp->fileheader.reserved, sizeof(int));
	write(fd, &all->bmp->fileheader.file_offset_to_pxl_arr, sizeof(int));
	if (write(fd, &all->bmp->infoheader, sizeof(t_infohead)) == -1)
		error("read from file error");
	write (fd, all->img.addr, all->bmp->infoheader.img_size);
}

void	make_screenshot(t_all *all)
{
	int	fd;

	fd = open("./screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (fd < 0)
		error("could not create bmp file");
	init_headers(all);
	write_to_file(all, fd);
}
