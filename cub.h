/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:15:47 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/29 21:22:59 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdint.h>
# include "./libft/libft.h"
# include "./get_next_line.h"
# include "./minilibx_opengl/mlx.h"

typedef struct s_flags
{
	int			save;
	char		*map_name;
	int			map_fd;
	int			rx;
	int			ry;
	int			save_rx;
	int			save_ry;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*sprite;
	int			floor;
	int			ceil;
	char		**map;
	char		*line;
	int			all_lines;
	int			lines;
	int			map_hight;
	int			map_wdth;
}				t_flags;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			img_width;
	int			img_height;
}				t_data;

typedef struct s_plr
{
	double		pos_x;
	double		pos_y;
	char		dir;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		raydir_x;
	double		raydir_y;
	int			step_x;
	int			step_y;
	double		sidedist_x;
	double		sidedist_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	double		moveSpeed;
	double		rotSpeed;
	int			line_h;
	int			draw_str;
	int			draw_end;
	int			tex_x;
	double		step;
	double		*z_buf;
}				t_plr;

typedef struct s_key
{
	int			l;
	int			r;
	int			w;
	int			a;
	int			s;
	int			d;
}				t_key;

typedef struct s_tex
{
	t_data		no;
	t_data		so;
	t_data		we;
	t_data		ea;
	t_data		spr;
}				t_tex;

typedef struct s_sprt
{
	double		x;
	double		y;
	double		dist;
}				t_sprt;

typedef struct s_spr
{
	int			spr_num;
	t_sprt		*s;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_h;
	int			sprite_w;
	int			draw_str_y;
	int			draw_end_y;
	int			draw_str_x;
	int			draw_end_x;
	int			stripe;
	int			tex_x;
	int			tex_y;
	int			d;
	int			color;
}				t_spr;

typedef struct s_filehead
{
	char		file_type[2];
	int			file_size;
	int			reserved;
	int			file_offset_to_pxl_arr;
}				t_filehead;

typedef struct s_infohead
{
	int			header_size;
	int			img_width;
	int			img_height;
	short		planes;
	short		bpp;
	int			compression;
	int			img_size;
	int			ypixelpermeter;
	int			xpixelpermeter;
	int			color_palette;
	int			imp_color;
}				t_infohead;

typedef struct s_bmp
{
	t_filehead	fileheader;
	t_infohead	infoheader;
}				t_bmp;

typedef struct s_all
{
	t_flags		flags;
	t_mlx		mlx;
	t_data		img;
	t_tex		tex;
	t_plr		plr;
	t_key		key;
	t_spr		spr;
	t_bmp		*bmp;
}				t_all;

void		process_map_file(t_all *all);
void		check_resolution(t_all *all);
void		check_texture(t_all *all);
void		check_colors(t_all *all);
void		sep_map(t_all *all);
int			check_all_flags(t_all *all);
void		check_line(t_all *all);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			flood_fill(char **map, int x, int y, int map_hight);
int			key_press(int keycode, t_all *all);
int			key_release(int keycode, t_all *all);
int			draw(t_all *all);
void		move(t_all *all);
void		write_tex_param(t_all *all);
t_data		choose_tex(t_all *all, int side, int step_x, int step_y);
void		find_player_coordinates(t_all *all);
void		find_sprites_num(t_all *all);
void		draw_sprites(t_all *all);
void		write_sprites_coord(t_all *all);
void		mlx_get_screen_size(int *width, int *height);
void		draw_ceiling(t_all *all);
void		draw_floor(t_all *all);
void		draw_wall(t_all *all);
void		make_screenshot(t_all *all);
void		init_structure_variables(t_all *all);
void		check_splited_strings(char	**array);
void		check_valid_symbols(t_all *all);
void		draw_textures(t_all *all, t_data *curr_tex, int x);
void		calc_tex_param(t_all *all, t_data *curr_tex, int side);
void		error(char *str);
void		check_map_isol(t_all *all);
int			gnl_error(t_all *all);
void		calc_spr_dist(t_all *all);
void		sort_sprites_order(t_all *all);
void		skip_spaces(t_all *all);
#endif