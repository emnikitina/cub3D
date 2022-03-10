/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 19:11:20 by odomenic          #+#    #+#             */
/*   Updated: 2021/03/23 19:56:51 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fill_win(t_param *prms, t_draw *draw, int i, double tex_pos)
{
	int		j;

	j = 0;
	while (j < draw->start)
	{
		my_mlx_pixel_put(prms, i, j, prms->c_clr);
		j++;
	}
	while (j < draw->end)
	{
		tex_pos += (64.0 / draw->line_height);
		my_mlx_pixel_put(prms, i, j, ((int *)((ft_choose_tex(prms))->addr))[64 *
				((int)tex_pos & 63) + draw->tex_x]);
		j++;
	}
	while (j < prms->win->height)
	{
		my_mlx_pixel_put(prms, i, j, prms->f_clr);
		j++;
	}
}

void	ft_draw_start_end(t_param *prms, t_draw *draw, double dist_to_wall)
{
	draw->line_height = (int)(prms->win->height / (dist_to_wall *
				((double)(prms->win->height * 4) / (double)(prms->win->width
					* 3))));
	draw->start = (prms->win->height - draw->line_height) / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = (draw->line_height + prms->win->height) / 2;
	if (draw->end >= prms->win->height)
		draw->end = prms->win->height - 1;
	if (prms->plr->side == 0)
		draw->wall_x = prms->plr->y + dist_to_wall * prms->plr->ray_dir->y;
	else
		draw->wall_x = prms->plr->x + dist_to_wall * prms->plr->ray_dir->x;
	draw->wall_x -= (int)draw->wall_x;
	draw->tex_x = (int)(draw->wall_x * 64.0);
	if (((prms->plr->side == 0) && (prms->plr->ray_dir->x > 0)) ||
			((prms->plr->side == 1) && (prms->plr->ray_dir->y < 0)))
		draw->tex_x = 64 - draw->tex_x - 1;
}

double	ft_draw(t_param *prms, t_point_int point, int i)
{
	double	dist_to_wall;
	t_draw	*draw_params;
	double	tex_pos;

	draw_params = &(t_draw){0, 0, 0, 0.0, 0};
	if (!prms->plr->side)
		dist_to_wall = (point.x - prms->plr->x + (1 - prms->plr->step->x) / 2)
			/ prms->plr->ray_dir->x;
	else
		dist_to_wall = (point.y - prms->plr->y + (1 - prms->plr->step->y) / 2)
			/ prms->plr->ray_dir->y;
	ft_draw_start_end(prms, draw_params, dist_to_wall);
	tex_pos = (draw_params->start - prms->win->height / 2 +
			draw_params->line_height / 2) * (64.0 / draw_params->line_height);
	ft_fill_win(prms, draw_params, i, tex_pos);
	return (dist_to_wall);
}
