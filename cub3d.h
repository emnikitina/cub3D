/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 21:42:34 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/23 22:03:17 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <math.h>
# include "get_next_line.h"
# include "libft/libft.h"
# include "minilibx_opengl_20191021/mlx.h"

typedef struct	s_config {
	int		rx;
	int		ry;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*sprite;
	int		fr;
	int		fg;
	int		fb;
	int		cr;
	int		cg;
	int		cb;
	int		sprite_count;
	int		screenshot;
}				t_config;

typedef struct	s_flags {
	int r;
	int no;
	int so;
	int we;
	int ea;
	int s;
	int c;
	int f;
	int map;
	int pers;
}				t_flags;

typedef struct	s_win {
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_l;
	int		endian;
}				t_win;

typedef struct	s_point {
	double x;
	double y;
}				t_point;

typedef struct	s_point_int {
	int x;
	int y;
}				t_point_int;

typedef struct	s_plr
{
	double		x;
	double		y;
	t_point		*dir;
	t_point		*plane;
	int			side;
	t_point		*ray_dir;
	t_point		*step;
}				t_plr;

typedef struct	s_map {
	char	**map_str;
	int		**map;
	int		width;
	int		height;
}				t_map;

typedef struct	s_tex {
	int		width;
	int		height;
	void	*img;
	void	*addr;
	int		bpp;
	int		line_l;
	int		endian;
}				t_tex;

typedef struct	s_textures {
	t_tex *tex_so;
	t_tex *tex_no;
	t_tex *tex_we;
	t_tex *tex_ea;
	t_tex *tex_sprite;
}				t_textures;

typedef struct	s_key {
	int w;
	int	s;
	int	a;
	int	d;
	int r;
	int l;
}				t_key;

typedef struct	s_param {
	t_win		*win;
	t_plr		*plr;
	t_map		*map;
	t_config	*config;
	t_textures	*texs;
	t_point		*sprites;
	double		*sprite_dist;
	int			c_clr;
	int			f_clr;
	t_key		*key;
}				t_param;

typedef struct	s_sprite {
	int		width;
	int		height;
	int		screen_x;
	t_point	*draw_start;
	t_point	*draw_end;
	t_point	*tform;
}				t_sprite;

typedef struct	s_draw {
	int		start;
	int		end;
	int		line_height;
	double	wall_x;
	int		tex_x;
}				t_draw;

int				get_next_line(int fd, char **line);
int				ft_read_file(int fd, t_flags *flags, t_param *prms);
void			ft_read_map(t_param *prms, char *line);
int				ft_convert(t_param *prms);
int				ft_map(t_param *prms);
int				ft_valid_map(int **map, int width, int lines);
int				ft_get_params(char **objs, char *line, t_config *config,
		t_flags *flags);
int				ft_valid_param(t_config *config, t_flags *flags);
void			ft_error(int error, t_param *prms);
void			ft_check_file(t_param *params, t_flags *flags);
char			*ft_check_config(t_config *conf);
char			*ft_check_tex_path(t_config *config);
int				ft_check_tex_type(char *str);
char			*ft_check_colors(const char *line);
char			*ft_flags_absent(t_flags *flags);
char			*ft_flags_double(t_flags *flags);
char			*ft_check_texs(t_param *prms);
int				ft_raycasting(t_param *params);
void			ft_dir_plane(t_param *prms);
void			ft_malloc_memory(t_param *prms);
int				ft_init_win(t_param *prms);
int				ft_write_win(t_param *prms);
int				ft_close(t_param *prms);
void			ft_sprite_init(t_param *prms);
void			ft_sprite_sort(int count, t_point *sprites,
		double *sprite_dist);
void			ft_sprite_draw(t_param *prms, t_point *sprites,
		double *sprite_normal);
void			ft_open_textures(t_param *prms);
int				ft_check_tex_type(char *str);
t_tex			*ft_choose_tex(t_param *prms);
void			ft_move(t_param *prms);
void			ft_go_forw(t_param *prms, double move);
void			ft_go_back(t_param *prms, double move);
void			ft_go_left(t_param *prms, double move);
void			ft_go_right(t_param *prms, double move);
void			ft_rot_right(t_param *prms, double rot);
void			ft_rot_left(t_param *prms, double rot);
void			ft_sprite(t_param *prms, double *sprite_normal);
void			ft_sprite_init(t_param *prms);
void			ft_sprite_sort(int count, t_point *sprites,
		double *sprite_dist);
void			ft_sprite_draw(t_param *prms, t_point *sprites,
		double *sprite_normal);
double			ft_draw(t_param *prms, t_point_int point, int i);
int				ft_key_press(int keycode, t_param *prms);
int				ft_key_unpress(int keycode, t_param *prms);
int				ft_screenshot(t_param *prms);
void			ft_free_objs(char **objs);
void			ft_clean(t_param *prms);
int				ft_numobjs(char **arr);
size_t			ft_width_arr(char **map);
int				ft_get_nbr(const char *s, int *num);
int				ft_isnum(const char *str);
void			my_mlx_pixel_put(t_param *prms, int width, int height,
		int color);
int				create_trgb(int t, int r, int g, int b);
#endif
